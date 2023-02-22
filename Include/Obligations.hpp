#pragma once
#include "Date.hpp"

class Obligations{
public:

    Obligations(const std::string& description, int moneyToPay, Date paymentDate): description_(description), moneyToPay_(moneyToPay) {}

    //Getters
    Date getPaymentDate()        const {return paymentDate_;};
    int getMoneyToPay()          const {return moneyToPay_;};
    std::string getDescription() const {return description_;};

    //Setters
    void setPaymentDate(const Date& date)               {paymentDate_ = date;};
    void setMoneyToPay(const int& moneyToPay)           {moneyToPay_ = moneyToPay;};
    void setDescription(const std::string& description) {description_ = description;};

protected:
    Date paymentDate_;
    int moneyToPay_;
    std::string description_;
    
    Date startPaymentDate_ = Date::currentData();

};