#pragma once
#include "Date.hpp"

class Obligations{
public:

    Obligations(int moneyToPay, Date paymentDate):moneyToPay_(moneyToPay), paymentDate_(paymentDate){}
    ~Obligations(){};
    //Getters
    Date getPaymentDate()        const {return paymentDate_;};
    int getMoneyToPay()          const {return moneyToPay_;};

    //Setters
    void setPaymentDate(const Date& date)               {paymentDate_ = date;};
    void setMoneyToPay(const int& moneyToPay)           {moneyToPay_ = moneyToPay;};

    //Functions
    friend std::ostream& operator<<(std::ostream &os, const Obligations& obligations);
    virtual void printObligation(std::ostream& os) const = 0;
    virtual std::string printObligation() const = 0;
    int distanceToPayDate();
    void nextMonth();

protected:
    Date paymentDate_;
    int moneyToPay_;

    Date startPaymentDate_ = Date::currentData();

};

