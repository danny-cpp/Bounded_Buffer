// Copyright Danh Nguyen 2021
//
// https://github.com/danny-cpp
//
#pragma once

#include  <PCH.h>

#include "InstructionToken.h"
#include "BufferedChannel.h"
#include "Scheduler.h"


namespace Shell379 {
    class CommandParser {
    public:
        /**
         * Handle all input parsing and calling the corresponding function call. System calls are NOT
         * implemented here.
         *
         * @return
         */
        static int parse(bool &return_eof, ProdCon::BufferedChannel &work_queue,
                         ProdCon::Scheduler &scheduler);

    private:

    };
}
