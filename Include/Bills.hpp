#include "Obligations.hpp"

enum class BillType {Electricity = 0, Water, Gas, Internet };

class Bills : public Obligations{
public:
    Bills(const std::string& description, int moneyToPay, Date paymentDate,const BillType& billType) : Obligations(description,moneyToPay,paymentDate), billType_(billType) {};

    std::string getBillType();
private:
    BillType billType_;
};