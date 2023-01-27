#pragma once
#include <string>
#include <ostream>

enum class ExpenseCategory { Housing = 1, Transportation, Food, Utilities, Insurance, Medical, Savings, PersonalSpending, Entertainment, Miscellaneous};


class Tranzaction{
public:
    Tranzaction(const std::string& description, 
                const double& money, 
                const ExpenseCategory& expenseCategory) :  
                                                          description_(description),
                                                          money_(money),
                                                          expenseCategory_(expenseCategory) {ID_ = counter++;};
    ~Tranzaction(){ ID_--;};

    //Getters
        size_t getID() const {return ID_;};


    //Setters
        void setExpenseCategory(const ExpenseCategory& expenseCategory) { expenseCategory_ = expenseCategory; }
        void setDescription(const std::string& description)             { description_ = description;}
        void setMoney(const double& money)                              { money_ = money;}

    //Functions
        std::string printExpenseCategory(const ExpenseCategory& ExpenseCategory);
        friend std::ostream& operator<<(std::ostream& os, Tranzaction& tranzaction);
    
private:

    size_t ID_;
    ExpenseCategory expenseCategory_{ExpenseCategory::Miscellaneous};
    std::string description_;
    double money_;

    static size_t counter;

};


