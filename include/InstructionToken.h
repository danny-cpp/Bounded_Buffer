#pragma once

#include <PCH.h>


namespace ProdCon {

    /**
     * A token is object holding a Trans or a Sleep instruction. It also holds an integer value determine
     * the time should takes. 0 is for Trans, 1 is for sleep
     *
     */
    class InstructionToken {
    public:
        InstructionToken(int command_type, int command_value);
        int getCommandType() const;
        int getCommandValue() const;

    private:
        int command_type;
        int command_value;
    };

}

