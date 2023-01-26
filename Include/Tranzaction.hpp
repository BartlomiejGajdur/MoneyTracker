#pragma once
#include <string>

enum class ExpenseCategory { Housing = 1, Transportation, Food, Utilities, Insurance, Medical, Savings, PersonalSpending, Entertainment, Miscellaneous};

class Tranzaction{
public:
    Tranzaction(const std::string& description, 
                const double& money, 
                const ExpenseCategory& expenseCategory) :  
                                                          description_(description),
                                                          money_(money),
                                                          expenseCategory_(expenseCategory) {ID_++;};

    static size_t ID_;
    
private:
    
    ExpenseCategory expenseCategory_;
    std::string description_;
    double money_;

    
    //static size_t counter;

};