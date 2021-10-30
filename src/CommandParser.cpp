#include <CommandParser.h>


namespace Shell379 {
    int CommandParser::parse(bool internal_call) {


        std::string raw_in;
        std::vector<std::string> inputs;

        std::string s;

        while(!std::cin.eof()) {
            getline(std::cin, s);
            std::cout << s << std::endl;
        }

        // while (!inFile.eof())) {
        //     std::cin.getline(&s);
        //     inputs.push_back(s);
        //     std::cout << s << std::endl;
        // }



        int length = (int)inputs.size();

        return 0;
    }

    void readData(std::istream& in)
    {
        // Do the necessary work to read the data.
    }
}
