#include <CommandParser.h>


namespace Shell379 {
    int CommandParser::parse(bool internal_call) {

        std::cout << "\nSHELL379: ";

        std::string raw_in;
        std::vector<std::string> inputs;
        std::getline(std::cin, raw_in);
        std::istringstream stream(raw_in);

        std::string s;
        while (stream >> s) {
            inputs.push_back(s);
        }

        int length = (int)inputs.size();

        return 0;
    }
}
