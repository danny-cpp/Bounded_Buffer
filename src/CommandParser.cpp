#include <CommandParser.h>


int Shell379::CommandParser::parse(bool &return_eof, ProdCon::BufferedChannel &work_queue,
                                   ProdCon::Scheduler &scheduler) {

    std::string s;
    while(!std::cin.eof()) {
        getline(std::cin, s);
        // std::cout << s << std::endl;
        if (s == "" || s.at(0) == '\r') break;
        ProdCon::InstructionToken i(s);
        scheduler.schedule(i);
    }
    return_eof = true;

    return 0;
}


