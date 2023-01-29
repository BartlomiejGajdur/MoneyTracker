#pragma once
#include <string>
#include <ostream>

#include "Date.hpp"

enum class ExpenseCategory { Housing = 1, Transportation, Food, Utilities, Insurance, Medical, Savings, PersonalSpending, Entertainment, Miscellaneous};


class Transaction{
public:
    Transaction(const std::string& description, 
                const double& money, 
                const ExpenseCategory& expenseCategory, const Date& date) :  
                                                          description_(description),
                                                          money_(money),
                                                          expenseCategory_(expenseCategory),
                                                          date_(date) {ID_ = counter++;};
    Transaction(){};
    ~Transaction(){};

    //Getters
        size_t getID() const {return ID_;};
        double getMoney() const {return money_;};
        Date getDate() const {return date_;};
        ExpenseCategory getExpenseCategory() const {return expenseCategory_;};


    //Setters
        void setExpenseCategory(const ExpenseCategory& expenseCategory) { expenseCategory_ = expenseCategory; }
        void setDescription(const std::string& description)             { description_ = description;}
        void setMoney(const double& money)                              { money_ = money;}
        DateErrorCode setDate(int,int,int);

    //Functions
        std::string returnExpenseCategoryInString(const ExpenseCategory& ExpenseCategory);
        std::string transactionInString();
        friend std::ostream& operator<<(std::ostream& os, Transaction& transaction);
    
private:

    size_t ID_;
    ExpenseCategory expenseCategory_{ExpenseCategory::Miscellaneous};
    std::string description_;
    double money_;
    Date date_;

    static size_t counter;

};


