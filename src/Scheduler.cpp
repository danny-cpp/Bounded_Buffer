#include "Scheduler.h"


ProdCon::Scheduler::Scheduler(ProdCon::BufferedChannel *queue, int thread_num) {
    task_queue = queue;
    num_thread = thread_num;
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

        std::thread t([&] {
            ProdCon::Utilities::Trans(n);
        });
        t.join();
    }
}
