// Copyright Danh Nguyen 2021
//
// https://github.com/danny-cpp
//
// Precompile header includes utilities required for most projects
#include <PCH.h>

#include "ArgumentCheck.h"
#include "CommandParser.h"
#include "BufferedChannel.h"
#include "IOManagement.h"
#include "Scheduler.h"


// Time stamp. Sharing global variable should be limited
std::chrono::time_point<std::chrono::system_clock> begin_stamp;
int main(int argc, char const *argv[]) {

    int thread_num;                         // User defined thread spawn
    std::string log_ID;                     // Log file name with format prodcon.XX.log
    bool exit_status;                       // status of input complete. Result from an EOF signal
    std::vector<int> summary;               // Vector stores summary data to be reported


    // Check arg as per specification.
    ProdCon::ArgumentCheck::checkArg(argc, argv, thread_num, log_ID);


    // Initiate output target. From this point (unless reset), std::cout is piped to file.
    ProdCon::IOManagement io_manager(log_ID);
    io_manager.release();


    // Task queue capacity is 2x the issued thread number.
    auto *task_queue = new ProdCon::BufferedChannel(thread_num * 2);    // Deprecated class. Scheduler can work independently


    // Initiate the scheduler. Algorithm used here is thread-pooling. More in README
    ProdCon::Scheduler scheduler(task_queue, thread_num, io_manager, &summary);


    // Parsing and accepting input is on a different thread.
    std::thread input_handler([&] {
    #if 0
        std::cout << "Queue capacity is " << task_queue->getCapacity() << std::endl;
    #endif
        // Parse the input. Call the scheduler in its implementation
        Shell379::CommandParser::parse(exit_status, *task_queue, scheduler);
    });


    input_handler.join();

	return 0;
}