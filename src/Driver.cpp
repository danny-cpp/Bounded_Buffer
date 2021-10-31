// Precompile header includes utilities required for most projects
#include <PCH.h>

#include "ArgumentCheck.h"
#include "CommandParser.h"
#include "InstructionToken.h"
#include "BufferedChannel.h"


int main(int argc, char const *argv[]) {

    int thread_num;                         // User defined thread spawn
    std::string log_ID;                     // Log file name with format prodcon.XX.log
    std::condition_variable exit_status;    // status of input complete. Result from an EOF signal

    // Check arg as per specification.
    ProdCon::ArgumentCheck::checkArg(argc, argv, thread_num, log_ID);

    // Task queue capacity is 2x the issued thread number.
    ProdCon::BufferedChannel task_queue(thread_num * 2);

    std::thread input_handler([&] {
    #if DEBUG_MODE
        std::cout << "Queue capacity is " << task_queue.getCapacity() << std::endl;
    #endif
        // Parse the input. Should be on a different thread
        Shell379::CommandParser::parse(exit_status, task_queue);

        std::this_thread::sleep_for(std::chrono::seconds(2));
    });


    input_handler.join();
    #if DEBUG_MODE
        std::cout << "Main thread has come to completion" << std::endl;
    #endif

    // ProdCon::BufferedChannel channel(3);
    //
    //
    // auto task = [&] {
    //     std::string s;
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    //     for (int i = 0; i < 6; ++i) {
    //         std::this_thread::sleep_for(std::chrono::seconds(2));
    //         std::cout << "Trying to pop, current queue is: ";
    //         channel.printAll();
    //         std::cout << std::endl;
    //
    //         channel.pop_front();
    //     }
    // };
    // std::thread t1(task);
    //
    // for (int i = 0; i < 4; ++i) {
    //     ProdCon::InstructionToken t(1, 2);
    //     std::cout << "Trying to push, current queue is: ";
    //     channel.printAll();
    //     std::cout << std::endl;
    //
    //     channel.add(t);
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    //
    // }
    //
    // std::cout << "Main thread has come to completion" << std::endl;

	return 0;
}