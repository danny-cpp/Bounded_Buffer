// Precompile header includes utilities required for most projects
#include <PCH.h>

#include "ArgumentCheck.h"
#include "CommandParser.h"
#include "InstructionToken.h"
#include "BufferedChannel.h"
#include "IOManagement.h"


int main(int argc, char const *argv[]) {

    int thread_num;                         // User defined thread spawn
    std::string log_ID;                     // Log file name with format prodcon.XX.log
    std::condition_variable exit_status;    // status of input complete. Result from an EOF signal

    // Check arg as per specification.
    ProdCon::ArgumentCheck::checkArg(argc, argv, thread_num, log_ID);

    // Initiate output target. From this point (unless reset), std::cout is piped to file
    ProdCon::IOManagement io_manager(log_ID);
    std::string s1 = "Receive";
    std::string s2 = "Ask";
    ProdCon::IOManagement::write_list(0.001, 2, 3, s1, 4);
    ProdCon::IOManagement::write_list(0.001, 13, 22, s2, 99);
    io_manager.release();

    // Task queue capacity is 2x the issued thread number.
    ProdCon::BufferedChannel task_queue(thread_num * 2);

    std::thread input_handler([&] {
    #if DEBUG_MODE
        std::cout << "Queue capacity is " << task_queue.getCapacity() << std::endl;
    #endif
        // Parse the input. Should be on a different thread
        Shell379::CommandParser::parse(exit_status, task_queue);
    });


    input_handler.join();
    #if DEBUG_MODE
        std::cout << "Main thread has come to completion" << std::endl;
    #endif


	return 0;
}