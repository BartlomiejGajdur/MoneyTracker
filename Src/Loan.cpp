#include "../include/Loan.hpp"
#include "../include/MenuFunctions.hpp"
#include <iomanip>
#include <sstream>

void Loan::printObligation(std::ostream& os) const{
    os<<description_<<" - "<<moneyToPay_<<" - "<<paymentDate_<<" Pozostalo RAT "<<numberOfInstallments_;
}

std::string Loan::printObligation() const{

    std::stringstream is;
    std::string day;

    is<<"| "<<std::setw(12)<< std::left<< description_<<" | "
    <<std::setw(12) << std::left<<std::to_string(moneyToPay_)+ " PLN"<<" | "
    <<std::setw(12) << std::left<<paymentDate_.dateInString() <<" | ";
    this->distanceToPayDate() == 1 || this->distanceToPayDate() == -1 ? day = " day" : day = " days";

    if(this->distanceToPayDate() > 0 && this->distanceToPayDate() <=7)
    {
        is<<std::setw(20) << std::left<<MenuFunctions::SetTextColor(Color::Yellow, std::to_string(this->distanceToPayDate()) + day)<<" | ";
    }else if(this->distanceToPayDate() > 7){
        is<<std::setw(20) << std::left<<MenuFunctions::SetTextColor(Color::Green, std::to_string(this->distanceToPayDate()) + day)<<" | ";
    }else{
        is<<std::setw(20) << std::left<<MenuFunctions::SetTextColor(Color::Red, std::to_string(this->distanceToPayDate()) + day)<<" | ";
    }

    is<<std::setw(16) << std::left<<std::to_string(numberOfInstallments_) +  " left" <<" |\n";

    return is.str();
}

std::ostream& operator<<(std::ostream &os, const Loan& Loan){
    Loan.printObligation(os);
    return os;
}

