#include "../include/Loan.hpp"
#include <sstream>

void Loan::printObligation(std::ostream& os) const{
    os<<description_<<" - "<<moneyToPay_<<" - "<<paymentDate_<<" Pozostalo RAT "<<numberOfInstallments_;
}

std::ostream& operator<<(std::ostream &os, const Loan& Loan){
    Loan.printObligation(os);
    return os;
}

