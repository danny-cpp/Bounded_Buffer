#include <CommandParser.h>


namespace Shell379 {
    int CommandParser::parse(bool internal_call) {

        std::string s;

        while(!std::cin.eof()) {
            getline(std::cin, s);
            std::cout << s << std::endl;
        }

        return 0;
    }

}
