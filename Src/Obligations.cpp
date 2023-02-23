#include "../Include/Obligations.hpp"

std::ostream& operator<<(std::ostream &os, const Obligations& obligations){
    obligations.printObligation(os);
    return os;
}

int Obligations::distanceToPayDate(){
    return Date::distance(Date::currentData(), paymentDate_);
}