#pragma once
#include <string>
#include <ostream>

#include "Date.hpp"

enum class ExpenseCategory { Housing = 1, Transportation, Food, Utilities, Insurance, Medical, Savings, PersonalSpending, Entertainment, Miscellaneous, SettingTheBill};


class Transaction{
public:
    Transaction(const size_t& ID,
                const std::string& description, 
                const double& money, 
                const ExpenseCategory& expenseCategory, 
                const Date& date) :                       ID_(ID),
                                                          description_(description),
                                                          money_(money),
                                                          expenseCategory_(expenseCategory),
                                                          date_(date) {};
    Transaction(const std::string& description, 
                const double& money, 
                const ExpenseCategory& expenseCategory, 
                const Date& date) :  
                                                          description_(description),
                                                          money_(money),
                                                          expenseCategory_(expenseCategory),
                                                          date_(date) {};
    Transaction(const std::string& description, 
                const double& money, 
                const ExpenseCategory& expenseCategory) :  
                                                          description_(description),
                                                          money_(money),
                                                          expenseCategory_(expenseCategory)
                                                          {
                                                            
                                                            date_ = Date::currentData();
                                                            };
    Transaction(){};
    ~Transaction(){};

    //Getters
        size_t getID() const {return ID_;};
        std::string getDescription() const {return description_;};
        double getMoney() const {return money_;};
        ExpenseCategory getExpenseCategory() const {return expenseCategory_;};
        Date getDate() const {return date_;};


    //Setters
        void setExpenseCategory(const ExpenseCategory& expenseCategory) { expenseCategory_ = expenseCategory; }
        void setDescription(const std::string& description)             { description_ = description;}
        void setMoney(const double& money)                              { money_ = money;}
        void setID(const size_t& ID)                                    { ID_ = ID;}
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


