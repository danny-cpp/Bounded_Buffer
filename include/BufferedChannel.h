#pragma once

#include <PCH.h>


namespace ProdCon {

    template <typename T>
    class BufferedChannel {
    public:
        BufferedChannel(int cap) :
        internal_queue(),
        cv(),
        m(),
        capacity(cap)
        {}

    private:
        std::queue<T> internal_queue;
        mutable std::condition_variable cv;
        std::mutex m;

        std::atomic<int> capacity{};
    };

}

