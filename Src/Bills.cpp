#include "../include/Bills.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>
#include "../include/MenuFunctions.hpp"


std::string Bills::getBillType() const {
    switch (billType_) {
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

void Bills::printObligation(std::ostream& os) const {
    os << this->getBillType() << " - " << moneyToPay_ << " - " << paymentDate_;
}

std::string Bills::printObligation() const {
    std::stringstream is;
    std::string day;
    std::ostringstream stream;
    stream.precision(2);
    stream << std::fixed << moneyToPay_;
    std::string moneyToPayString = stream.str();

    is << "| " << std::setw(12) << std::left << this->getBillType() << " | "
       << std::setw(12) << std::left << moneyToPayString + " PLN"
       << " | "
       << std::setw(12) << std::left << paymentDate_.dateInString() << " | ";
    this->distanceToPayDate() == 1 || this->distanceToPayDate() == -1 ? day = " day" : day = " days";

    if (this->distanceToPayDate() > 0 && this->distanceToPayDate() <= 7) {
        is << std::setw(20) << std::left << MenuFunctions::SetTextColor(Color::Yellow, std::to_string(this->distanceToPayDate()) + day) << " | ";
    } else if (this->distanceToPayDate() > 7) {
        is << std::setw(20) << std::left << MenuFunctions::SetTextColor(Color::Green, std::to_string(this->distanceToPayDate()) + day) << " | ";
    } else {
        is << std::setw(20) << std::left << MenuFunctions::SetTextColor(Color::Red, std::to_string(this->distanceToPayDate()) + day) << " | ";
    }

    is << std::setw(16) << std::left << "Recurring payments"
       << " |\n";

    return is.str();
}

std::ostream& operator<<(std::ostream& os, const Bills& Bills) {
    Bills.printObligation(os);
    return os;
}
