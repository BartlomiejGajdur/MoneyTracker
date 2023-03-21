#pragma once
#include "Date.hpp"

class Obligations {
public:
    Obligations(double moneyToPay, Date paymentDate)
        : moneyToPay_(moneyToPay), paymentDate_(paymentDate) {}
    ~Obligations(){};
    //Getters
    Date getPaymentDate() const { return paymentDate_; };
    double getMoneyToPay() const { return moneyToPay_; };

    //Setters
    void setPaymentDate(const Date& date) { paymentDate_ = date; };
    void setMoneyToPay(const double& moneyToPay) { moneyToPay_ = moneyToPay; };

    //Functions
    friend std::ostream& operator<<(std::ostream& os, const Obligations& obligations);
    virtual void printObligation(std::ostream& os) const = 0;
    virtual std::string printObligation() const = 0;
    int distanceToPayDate() const;
    virtual int getNumberOfInstallments_() const = 0;
    void nextMonth();

protected:
    Date paymentDate_;
    double moneyToPay_;
};
