#pragma once

#include <PCH.h>
#include "BufferedChannel.h"
#include "InstructionToken.h"
#include "Utilities.h"
#include "IOManagement.h"
#include "Timing.h"


extern std::chrono::time_point<std::chrono::system_clock> begin_stamp;
namespace ProdCon {
    class Scheduler {
    public:

        using Task = std::function<void()>;

        Scheduler(ProdCon::BufferedChannel *queue, int thread_num, ProdCon::IOManagement &io_obj,
                  std::vector<int> *summary_obj);

        ~Scheduler();

        void schedule(ProdCon::InstructionToken const &instruction);

    private:

        void start(int n);
        void stop();

        ProdCon::BufferedChannel *task_queue;
        int num_thread;
        std::vector<std::thread> thread_array;
        std::condition_variable cv;
        std::mutex m;
        std::mutex t;
        bool done;
        ProdCon::IOManagement *io_obj;
        std::vector<int>* summary_ptr;
    };
}
