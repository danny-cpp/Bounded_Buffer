#pragma once

#include <PCH.h>
#include "BufferedChannel.h"
#include "InstructionToken.h"
#include "Utilities.h"


namespace ProdCon {
    class Scheduler {
    public:

        Scheduler(ProdCon::BufferedChannel *queue, int thread_num);

        void schedule(ProdCon::InstructionToken const &instruction);

    private:
        ProdCon::BufferedChannel *task_queue;
        int num_thread;

        // std::condition_variable cv;
        // std::mutex m;
        // bool stopping;
    };
}
