#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Transaction.hpp"

enum class UserErrorCode {Ok, NoTransactionFound};

class User{

public:
    UserErrorCode addTransaction(const std::shared_ptr<Transaction> transaction);
    UserErrorCode removeTransactionById(size_t ID);
    DateErrorCode modifyDateTransactionById(size_t ID,int,int,int);
    std::string printAllTransations();
    void sortByNumberOfEnums();
    const double countWholeSpendings();
    std::map<ExpenseCategory,double> countIndividualSpending();
    std::map<ExpenseCategory,double> percentageOfIndividualSpending();
private:
    std::vector<std::shared_ptr<Transaction>> transactions_;
    
};