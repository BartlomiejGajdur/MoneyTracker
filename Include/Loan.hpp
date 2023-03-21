#include <memory>
#include "Obligations.hpp"


class Loan : public Obligations {
public:
    Loan(const std::string& description, double moneyToPay, Date paymentDate, const int numberOfInstallments)
        : Obligations(moneyToPay, paymentDate), description_(description), numberOfInstallments_(numberOfInstallments){};
    ~Loan(){};

    friend std::ostream& operator<<(std::ostream& os, const Loan& Bills);
    void printObligation(std::ostream& os) const override;
    std::string printObligation() const override;
    int getNumberOfInstallments_() const override { return numberOfInstallments_; };
    std::string getDescription() const { return description_; };
    void InstallmentsPaid() { numberOfInstallments_--; };

private:
    std::string description_;
    int numberOfInstallments_;
};
