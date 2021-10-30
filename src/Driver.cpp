// Precompile header includes utilities required for most projects
#include <PCH.h>

#include "ArgumentCheck.h"
#include "CommandParser.h"


std::atomic<long long> counter(0);

std::condition_variable cv;
std::mutex m;

int main(int argc, char const *argv[]) {

    int thread_num;                 // User defined thread spawn
    std::string log_ID;             // Log file name with format prodcon.XX.log
    bool exit_status = false;       // status of input complete. Result from an EOF signal
    std::queue<int> work_queue;

    // Check arg
    ProdCon::ArgumentCheck::checkArg(argc, argv, thread_num, log_ID);

    // Parse the input. Should be ona different thread
    Shell379::CommandParser::parse(exit_status, work_queue);

    std::cout << "helloWorld" << std::endl;


	return 0;
}