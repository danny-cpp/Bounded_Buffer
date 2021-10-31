#include "Scheduler.h"


ProdCon::Scheduler::Scheduler(ProdCon::BufferedChannel *queue, int thread_num) {
    task_queue = queue;
    num_thread = thread_num;
    done = false;

    start(thread_num);
}

ProdCon::Scheduler::~Scheduler() {
    stop();
}

void ProdCon::Scheduler::start(int n) {

    // Thread pooling. We create std::thread that are workers, and store their reference in a vector
    // for synchronization.
    for (int i = 0; i < num_thread; ++i) {
        thread_array.emplace_back([=] {
            // Each worker is an infinite loop of its own. Their job is to work. When they are finish,
            // they should signify that they are ready to work again and enter blocking state. Break happen
            // when the program is finished. Which happens when the destructor is called.
            while (true) {

                ProdCon::InstructionToken t(-1, -1);

                {
                    std::unique_lock<std::mutex> lock{m};

                    // Entering blocking state until there is some task is ready on the queue or the
                    // program is finished
                    cv.wait(lock, [=] {
                        return done || !task_queue->isEmpty();
                    });

                    // Exit infinite loop when everything is done
                    if (done && task_queue->isEmpty()) {
                        break;
                    }

                    t = task_queue->pop_front();
                }

                Task task = [=] {
                    ProdCon::Utilities::Trans(t.getCommandValue());
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
    }

    // The mutex is unlocked at this point. Now the condition variable signify all
    // the threads that are listening on this, so they can stop asking for works.
    cv.notify_all();

    for (auto &item : thread_array) {
        item.join();
    }
}


void ProdCon::Scheduler::schedule(ProdCon::InstructionToken const &instruction) {
    if (instruction.getCommandType() == 1) {
        int n = instruction.getCommandValue();
        #if DEBUG_MODE
            std::cout << "Entering sleep for " << n << std::endl;
        #endif
        ProdCon::Utilities::Sleep(n);
    }
    else if (instruction.getCommandType() == 0) {
        int n = instruction.getCommandValue();
        #if DEBUG_MODE
            std::cout << "Entering trans for " << n << std::endl;
        #endif

        std::unique_lock<std::mutex> lock{m};
        while (!task_queue->try_push(instruction)) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}



