#include "Obligations.hpp"

enum class BillType {Electricity = 0, Water, Gas, Internet };

class Bills : public Obligations{
public:
    Bills(const std::string& description, int moneyToPay, Date paymentDate,const BillType& billType) : Obligations(description,moneyToPay,paymentDate), billType_(billType) {};
    ~Bills(){};
    std::string getBillType() const;

    friend std::ostream& operator<<(std::ostream &os, const Bills& Bills);
    void printObligation(std::ostream& os) const override;

private:
    BillType billType_;
};

