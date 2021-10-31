#pragma once

#include <PCH.h>
#include "BufferedChannel.h"
#include "InstructionToken.h"
#include "Utilities.h"


namespace ProdCon {
    class Scheduler {
    public:

        using Task = std::function<void()>;

        Scheduler(ProdCon::BufferedChannel *queue, int thread_num);

        ~Scheduler();

        void schedule(ProdCon::InstructionToken const &instruction);

    private:
        ProdCon::BufferedChannel *task_queue;
        int num_thread;

        std::vector<std::thread> thread_array;

        void start(int n);

        void stop();


        std::condition_variable cv;
        std::mutex m;
        bool done;
    };
}
