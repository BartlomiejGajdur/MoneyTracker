#include "../include/Bills.hpp"
#include <sstream>

std::string Bills::getBillType() const {
    switch (billType_)
    {
    case BillType::Electricity:
        return "Electricity";
        break;

    case BillType::Water:
        return "Water";
        break;

    case BillType::Gas:
        return "Gas";
        break;

    case BillType::Internet:
        return "Internet";
        break;
    
    default:
        return "ERROR";
        break;
    }
}


void Bills::printObligation(std::ostream& os) const{
    os<<this->getBillType()<<" - "<<moneyToPay_<<" - "<<paymentDate_;
}

std::string Bills::printObligation() const{
    return this->getBillType() + " - " + std::to_string(moneyToPay_)+ " - "+ paymentDate_.dateInString();
}

std::ostream& operator<<(std::ostream &os, const Bills& Bills){
    Bills.printObligation(os);
    return os;
}

