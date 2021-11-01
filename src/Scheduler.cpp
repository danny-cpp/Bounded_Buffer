#include "Scheduler.h"


static int ID = 1;
ProdCon::Scheduler::Scheduler(ProdCon::BufferedChannel *queue, int thread_num, ProdCon::IOManagement &io_obj,
                              std::vector<int> *summary_obj) {
    task_queue = new std::deque<ProdCon::InstructionToken>();
    num_thread = thread_num;
    done = false;
    this->io_obj = &io_obj;
    *summary_obj = std::vector<int>({0, 0, 0, 0, 0});

    // Populate placeholder for thread statistics
    for (int i = 0; i < num_thread; ++i) {
        summary_obj->push_back(0);
    }

    summary_ptr = summary_obj;
    begin_stamp = std::chrono::high_resolution_clock::now();

    start(thread_num);
}

ProdCon::Scheduler::~Scheduler() {
    stop();
}

void ProdCon::Scheduler::start(int n) {

    std::cout << std::fixed;
    std::cout << std::setprecision(3);

    // Thread pooling. We create std::thread that are workers, and store their reference in a vector
    // for synchronization.
    for (int i = 0; i < num_thread; ++i) {
        thread_array.emplace_back([&] {
            // Each worker is an infinite loop of its own. Their job is to work. When they are finish,
            // they should signify that they are ready to work again and enter blocking state. Break happen
            // when the program is finished. Which happens when the destructor is called.
            const int tID = ID;
            ID++;
            while (true) {
                ProdCon::InstructionToken token(-1, -1);

                {
                    std::unique_lock<std::mutex> lock{m};

                    // Log block. At this point, the thread is asking for work
                    io_obj->record(t, tID, -1, "Ask", -1);

                    {
                        std::unique_lock<std::mutex> lck{s};
                        summary_ptr->at(1) += 1;
                    }


                    // Entering blocking state until there is some task is ready on the queue or the
                    // program is finished
                    not_empty.wait(lock, [&] {
                        return done || !task_queue->empty();
                    });

                    // Exit infinite loop when everything is done
                    if (done && task_queue->empty()) {
                        break;
                    }

                    token = task_queue->front();

                    // This is when the thread received the work
                    int q_number = task_queue->size();
                    int n_number = token.getCommandValue();
                    io_obj->record(t, tID, q_number, "Receive", n_number);
                    {
                        std::unique_lock<std::mutex> lck{s};
                        summary_ptr->at(2) += 1;
                        summary_ptr->at(4 + tID) += 1;
                    }


                    task_queue->pop_front();

                    not_full.notify_all();
                }

                Task task = [&] {
                    ProdCon::Utilities::Trans(token.getCommandValue());

                    // Completed log
                    int n_number = token.getCommandValue();
                    io_obj->record(t, tID, -1, "Complete", n_number);
                    {
                        std::unique_lock<std::mutex> lck{s};
                        summary_ptr->at(3) += 1;
                    }
                };

                task();
            }
        });
    }
}

void ProdCon::Scheduler::stop() {

    {
        // Lock the mutex and change the done flag
        std::unique_lock<std::mutex> lock{m};
        done = true;

        // End of input
        io_obj->record(t, 0, -1, "End", -1);
    }

    // The mutex is unlocked at this point. Now the condition variable signify all
    // the threads that are listening on this, so they can stop asking for works.
    not_empty.notify_all();

    for (auto &item : thread_array) {
        item.join();
    }

    auto stamp = Shell379::Utilities::totalTiming::stamp(begin_stamp);
    io_obj->printSummary(t, *summary_ptr, stamp);
}


void ProdCon::Scheduler::schedule(ProdCon::InstructionToken const &instruction) {
    if (instruction.getCommandType() == 1) {
        int n = instruction.getCommandValue();
        #if 0
            std::cout << "Entering sleep for " << n << std::endl;
        #endif
        ProdCon::Utilities::Sleep(n);

        // Log sleep
        int n_number = instruction.getCommandValue();
        io_obj->record(t, 0, -1, "Sleep", n_number);
        {
            std::unique_lock<std::mutex> lck{s};
            summary_ptr->at(4) += 1;
        }
    }
    else if (instruction.getCommandType() == 0) {
        #if 0
            std::cout << "Entering trans for " << n << std::endl;
        #endif

        {
            std::unique_lock<std::mutex> lock{m};

            while ((int)task_queue->size() >= num_thread*2) {
                not_full.wait(lock, [=] {
                    return ((int)task_queue->size()) < num_thread*2;
                });
            }

            task_queue->push_back(instruction);

            // Notify the threads waiting for resources
            not_empty.notify_one();

            // A task will be counted toward the summary
            {
                std::unique_lock<std::mutex> lck{s};
                summary_ptr->at(0) += 1;
            }
        }

        // Log task enqueue
        int q_number = task_queue->size();
        int n_number = instruction.getCommandValue();
        io_obj->record(t, 0, q_number, "Work", n_number);
    }
}



