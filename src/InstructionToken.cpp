#include "InstructionToken.h"


ProdCon::InstructionToken::InstructionToken(int command_type, int command_value) {
    this->command_type = command_type;
    this->command_value = command_value;
}

int ProdCon::InstructionToken::getCommandType() const {
    return command_type;
}

int ProdCon::InstructionToken::getCommandValue() const {
    return command_value;
}

namespace ProdCon {
    std::ostream &operator<<(std::ostream &os, const ProdCon::InstructionToken &instruction) {
        if (instruction.getCommandType() == 0) {
            os << "Trans" << instruction.getCommandValue();
        } else {
            os << "Sleep" << instruction.getCommandValue();
        }
        return os;
    }
}