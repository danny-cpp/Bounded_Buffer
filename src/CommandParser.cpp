#include <CommandParser.h>


int Shell379::CommandParser::parse(std::condition_variable &return_eof, ProdCon::BufferedChannel &work_queue,
                                   ProdCon::Scheduler &scheduler) {

    std::string s;
    while(!std::cin.eof()) {
        getline(std::cin, s);
        // std::cout << s << std::endl;

        ProdCon::InstructionToken i(s);
        scheduler.schedule(i);
    }
    return_eof.notify_all();

    return 0;
}


