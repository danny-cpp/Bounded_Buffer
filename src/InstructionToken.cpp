#include "InstructionToken.h"


ProdCon::InstructionToken::InstructionToken(int command_type, int command_value) {
    this->command_type = command_type;
    this->command_value = command_value;
}

ProdCon::InstructionToken::InstructionToken(std::string inp_string) {
    std::string value = inp_string.substr(1);
    int n_value = std::stoi(value);

        if (inp_string.at(0) == 'T') {
            #if 0
                std::cout << "Trans for " << n_value << std::endl;
            #endif
            this->command_type = 0;
            this->command_value = n_value;
        }
        else {
            #if 0
                std::cout << "Sleep for " << n_value << std::endl;
            #endif
            this->command_type = 1;
            this->command_value = n_value;
        }

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