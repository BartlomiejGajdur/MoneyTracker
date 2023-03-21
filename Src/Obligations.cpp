#include "../Include/Obligations.hpp"

std::ostream& operator<<(std::ostream& os, const Obligations& obligations) {
    obligations.printObligation(os);
    return os;
}

int Obligations::distanceToPayDate() const {
    return Date::distance(Date::currentData(), paymentDate_);
}

void Obligations::nextMonth() {
    int month = paymentDate_.getMonth(), year = paymentDate_.getYear();
    if (paymentDate_.setDate(paymentDate_.getDay(), ++month, year) == DateErrorCode::InvalidMonth) {
        paymentDate_.setDate(paymentDate_.getDay(), 1, ++year);
    }
}