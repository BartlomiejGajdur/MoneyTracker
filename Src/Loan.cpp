#include "../include/Loan.hpp"
#include <sstream>

void Loan::printObligation(std::ostream& os) const{
    os<<description_<<" - "<<moneyToPay_<<" - "<<paymentDate_<<" Pozostalo RAT "<<numberOfInstallments_;
}

std::string Loan::printObligation() const{
    return description_ + " - " + std::to_string(moneyToPay_)+ " - "+ paymentDate_.dateInString() + " Pozostalo RAT "+ std::to_string(numberOfInstallments_);
}

std::ostream& operator<<(std::ostream &os, const Loan& Loan){
    Loan.printObligation(os);
    return os;
}

