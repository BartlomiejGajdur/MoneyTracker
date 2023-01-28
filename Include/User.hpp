#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Transaction.hpp"

enum class UserErrorCode {Ok, NoTransactionFound};

class User{

public:
    UserErrorCode addTransaction(const std::shared_ptr<Transaction> transaction);
    UserErrorCode removeTransactionById(size_t ID);
    std::string printAllTransations();
    void sortByNumberOfEnums();
private:
    std::vector<std::shared_ptr<Transaction>> transactions_;
    
};