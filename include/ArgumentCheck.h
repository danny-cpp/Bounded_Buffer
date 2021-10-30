#pragma once

#include <PCH.h>


namespace ProdCon {
    /**
     * Checking input argument at the call for the program. Specifically argc and argv
     */
    class ArgumentCheck {
    public:
        /**
         * Handle arguments. Return number of threads user issued. Return the designated log file.
         *
         * @param argc
         * @param argv
         * @param return_thread_num
         * @param return_log_ID
         */
        static void checkArg(int &argc, char const *argv[], int &return_thread_num, std::string &return_log_ID);
    };
}