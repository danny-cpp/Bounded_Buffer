#include "BufferedChannel.h"


void ProdCon::BufferedChannel::add(ProdCon::InstructionToken item) {
    // Lock before entering
    std::unique_lock<std::mutex> lock{m};

    // If it is full then blocking occurs
    while (count == capacity) {
#if DEBUG_MODE
        std::cout << "Write is blocked, buffer is full" << std::endl;
#endif
        not_empty_cvar.wait(lock);
    }

    // When it is not full, writing may resume
    internal_queue.emplace_back(item);
    count++;
    lock.unlock();

    // Notify all that are waiting on an empty channel. This will
    // resume the read blocking
    not_empty_cvar.notify_all();
}

ProdCon::InstructionToken ProdCon::BufferedChannel::pop_front() {
    std::unique_lock<std::mutex> lock{m};

    // If the queue is empty, wait.
    while (internal_queue.empty()) {
#if DEBUG_MODE
        std::cout << "Read is blocked, buffer is empty" << std::endl;
#endif
        not_empty_cvar.wait(lock);
    }

    auto pop_value = internal_queue.front();
    internal_queue.pop_front();
    count--;

    m.unlock();
    not_full_cvar.notify_all();

    return pop_value;
}

void ProdCon::BufferedChannel::printAll() {
    std::unique_lock<std::mutex> lock{m};

    if (internal_queue.empty()) {
        std::cout << "empty" << std::endl;
        return;
    }

    for (auto const &item : internal_queue) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int ProdCon::BufferedChannel::getCount() {
    std::unique_lock<std::mutex> lock{m};
    return count;
}

int ProdCon::BufferedChannel::getCapacity() {
    std::unique_lock<std::mutex> lock{m};
    return capacity;
}

bool ProdCon::BufferedChannel::isEmpty() {
    std::unique_lock<std::mutex> lock{m};
    if (count == 0) {
        return true;
    }
    return false;
}

bool ProdCon::BufferedChannel::isFull() {
    std::unique_lock<std::mutex> lock{m};
    if (count == capacity) {
        return true;
    }
    return false;
}

