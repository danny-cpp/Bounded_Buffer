#pragma once

namespace ProdCon {

    static void checkArg(int &argc, char const *argv[], int &return_thread_num, std::string &return_log_ID) {

        std::string ID = "0";

        if (argc == 1) {
            std::cout << "Error: No number of threads specified" << std::endl;
            exit(-1);
        }

        if (argc > 3) {
            std::cout << "Unspecified inputs" << std::endl;
            exit(-1);
        }

        if (argc == 3) {
            ID = argv[2];
        }

        return_log_ID = "prodcon." + ID + ".log";
        std::cout << "Id is: " << return_log_ID << std::endl;
    }
}