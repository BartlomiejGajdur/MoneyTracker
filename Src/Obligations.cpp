#include "../Include/Obligations.hpp"

std::ostream& operator<<(std::ostream &os, const Obligations& obligations){
    obligations.printObligation(os);
    return os;
}