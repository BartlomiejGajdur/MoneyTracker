#include <string>

enum class ExpenseCategory { Housing = 1, Transportation, Food, Utilities, Insurance, Medical, Savings, PersonalSpending, Entertainment, Miscellaneous};

class Tranzaction{
public:


private:
    static size_t ID_;
    ExpenseCategory expenseCategory_;
    std::string description;
    double money_;

};