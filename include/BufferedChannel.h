#pragma once

#include <PCH.h>

#include "InstructionToken.h"


namespace ProdCon {

    /**
     * Bounded Buffered, a.k.a Finite multithreading queue. Queue and deque can be done concurrently with mutex
     * protection. Write blocking occur when queue is full. Read blocking occur when queue is empty.
     *
     * WARNING: POSSIBLE DEADLOCK!!!
     */
    class BufferedChannel {
    public:
        explicit BufferedChannel(int cap) :
                internal_queue(),
                not_full_cvar(),
                not_empty_cvar(),
                m(),
                capacity(cap),
                count(0)
        {}


        /**
         * Add an item to the channel. If channel is full, the thread is blocked.
         *
         * WARNING: POSSIBLE DEADLOCK!!! If there are no actions to release
         * the channel, deadlock will occur!
         *
         * @param item
         */
        void add(ProdCon::InstructionToken item);


        /**
         * Remove the item that wait the longest. If channel is empty, the thread is blocked.
         *
         * WARNING: POSSIBLE DEADLOCK!!! If there are no actions to release
         * the channel, deadlock will occur!
         *
         * @return item at the front of the queue
         */
        ProdCon::InstructionToken pop_front();


        /**
         * Print all of its content as a list to stdout
         */
        void printAll();

        /**
         * Current item count in the channel
         *
         * @return
         */
        int getCount();

        /**
         * Capacity of the channel
         *
         * @return
         */
        int getCapacity();

        /**
         * Return true if it is empty
         *
         * @return
         */
        bool isEmpty();

        /**
         * Return true if it is full
         *
         * @return
         */
        bool isFull();

    private:
        std::deque<ProdCon::InstructionToken> internal_queue;
        std::condition_variable not_full_cvar;
        std::condition_variable not_empty_cvar;
        std::mutex m;
        const std::atomic<int> capacity{};
        std::atomic<int> count{};
    };

}

