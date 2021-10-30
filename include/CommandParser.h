// Copyright Danh Nguyen 2021
//
// https://github.com/danny-cpp
//
#pragma once

#include  <PCH.h>


namespace Shell379 {
    class CommandParser {
    public:
        /**
         * Handle all input parsing and calling the corresponding function call. System calls are NOT
         * implemented here.
         *
         * @param internal_call if a call is internal, extra information will not be printed
         * @return
         */
        static int parse(bool internal_call=false);

    private:

    };
}
