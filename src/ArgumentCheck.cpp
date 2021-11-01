#include "ArgumentCheck.h"


void ProdCon::ArgumentCheck::checkArg(int &argc, char const *argv[], int &return_thread_num, std::string &return_log_ID) {

    std::string ID = "0";

    if (argc == 1) {
        std::cout << "Error: No number of threads specified" << std::endl;
        exit(-1);
    }

    if (argc > 3) {
        std::cout << "Error: Unspecified inputs" << std::endl;
        exit(-1);
    }

    if (argc == 3) {
        ID = argv[2];
    }

    if (ID != "0") {
        return_log_ID = "prodcon." + ID + ".log";
    }
    else {
        return_log_ID = "prodcon.log";
    }
    return_thread_num = std::stoi(argv[1]);

    if (return_thread_num < 1) {
        std::cout << "Can't have less than 1 thread" << std::endl;
        exit(-1);
    }

#if DEBUG_MODE
    std::cout << "Log file is: " << return_log_ID << std::endl;
#endif

}