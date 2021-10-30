// Precompile header includes utilities required for most projects
#include <PCH.h>

#include "ArgumentCheck.h"
#include "CommandParser.h"

int main(int argc, char const *argv[]) {

    int thread_num;
    std::string log_ID;

    // Check arg
    ProdCon::checkArg(argc, argv, thread_num, log_ID);

    Shell379::CommandParser::parse(false);


    std::cout << "helloWorld" << std::endl;

	return 0;
}