#include "Obligations.hpp"

enum class BillType {Electricity = 0, Water, Gas, Internet };

class Bills : public Obligations{
public:
    Bills(const BillType& billType, int moneyToPay, Date paymentDate) : Obligations(moneyToPay,paymentDate), billType_(billType) {};
    ~Bills(){};
    std::string getBillType() const;
    

    friend std::ostream& operator<<(std::ostream &os, const Bills& Bills);
    void printObligation(std::ostream& os) const override;
    std::string printObligation() const override;

private:
    BillType billType_;
};

