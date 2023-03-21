#include <limits>
#include "Obligations.hpp"


enum class BillType { Electricity = 0,
                      Water,
                      Gas,
                      Internet };

class Bills : public Obligations {
public:
    Bills(const BillType& billType, double moneyToPay, Date paymentDate)
        : Obligations(moneyToPay, paymentDate), billType_(billType){};
    ~Bills(){};
    std::string getBillType() const;
    BillType getType() const { return billType_; };

    friend std::ostream& operator<<(std::ostream& os, const Bills& Bills);
    void printObligation(std::ostream& os) const override;
    std::string printObligation() const override;
    int getNumberOfInstallments_() const override { return std::numeric_limits<int>::max(); };

private:
    BillType billType_;
};
