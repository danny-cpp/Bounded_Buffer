// Precompile header includes utilities required for most projects
#include <PCH.h>

#include "ArgumentCheck.h"
#include "CommandParser.h"
#include "InstructionToken.h"
#include "BufferedChannel.h"


std::atomic<long long> counter(0);

std::condition_variable cv;
std::mutex m;

int main(int argc, char const *argv[]) {

    // int thread_num;                 // User defined thread spawn
    // std::string log_ID;             // Log file name with format prodcon.XX.log
    // bool exit_status = false;       // status of input complete. Result from an EOF signal
    // std::queue<int> work_queue;
    //
    // // Check arg
    // ProdCon::ArgumentCheck::checkArg(argc, argv, thread_num, log_ID);
    //
    // // Parse the input. Should be ona different thread
    // Shell379::CommandParser::parse(exit_status, work_queue);
    //
    // std::cout << "helloWorld" << std::endl;


    ProdCon::BufferedChannel channel(3);


    auto task = [&] {
        std::string s;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for (int i = 0; i < 6; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Trying to pop, current queue is: ";
            channel.printAll();
            std::cout << std::endl;

            channel.pop_front();
        }
    };
    std::thread t1(task);

    for (int i = 0; i < 4; ++i) {
        ProdCon::InstructionToken t(1, 2);
        std::cout << "Trying to push, current queue is: ";
        channel.printAll();
        std::cout << std::endl;

        channel.add(t);
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    std::cout << "Main thread has come to completion" << std::endl;
    t1.join();

	return 0;
}