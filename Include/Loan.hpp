#include "Obligations.hpp"

class Loan : public Obligations{
public:
    Loan(const std::string& description, int moneyToPay, Date paymentDate, const int numberOfInstallments) : Obligations(description,moneyToPay,paymentDate), numberOfInstallments_(numberOfInstallments) {};
    ~Loan(){};  

    friend std::ostream& operator<<(std::ostream &os, const Loan& Bills);
    void printObligation(std::ostream& os) const override;

private:
    int numberOfInstallments_;
};

