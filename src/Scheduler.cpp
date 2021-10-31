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
}
