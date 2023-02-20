#include "Obligations.hpp"

enum class BillType {Electricity = 0, Water, Gas, Internet };

class Bills : public Obligations{
public:
    

private:
    BillType billType_;
};