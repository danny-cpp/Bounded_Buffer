#include <CommandParser.h>


int Shell379::CommandParser::parse(bool &return_eof, std::queue<int> &work_queue) {

    std::string s;

    while(!std::cin.eof()) {
        getline(std::cin, s);
        std::cout << s << std::endl;
    }

    return 0;
}


