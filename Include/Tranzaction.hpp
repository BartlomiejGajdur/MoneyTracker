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

    //Setters
        void setExpenseCategory(const ExpenseCategory& expenseCategory) { expenseCategory_ = expenseCategory; }
        void setDescription(const std::string& description)             { description_ = description;}
        void setMoney(const double& money)                              { money_ = money;}

    
private:

    static size_t ID_;
    ExpenseCategory expenseCategory_{ExpenseCategory::Miscellaneous};
    std::string description_;
    double money_;

};