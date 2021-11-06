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

        std::deque<ProdCon::InstructionToken> task_queue;
        int num_thread;
        std::vector<std::thread> thread_array;
        std::condition_variable not_full;
        std::condition_variable not_empty;
        std::mutex m;       // Mutex between threads (modify task queue)
        std::mutex t;       // Mutex between record log (write file)
        std::mutex s;       // Mutex between summary record (write vector)
        bool done;
        ProdCon::IOManagement *io_obj;
        std::vector<int>* summary_ptr;
        std::atomic<int> current_count{0};
    };
}
