#include <algorithm>

#include "../Include/User.hpp"

UserErrorCode User::addTransaction(const std::shared_ptr<Transaction> transaction){
    transactions_.push_back(transaction);
    return UserErrorCode::Ok;
}

UserErrorCode User::removeTransactionById(size_t ID){
    auto temp = transactions_.size();
    transactions_.erase(std::remove_if(transactions_.begin(), transactions_.end(),[&ID](std::shared_ptr<Transaction> transaction)
                                                                                                                            {
                                                                                                                               return transaction->getID() == ID;
                                                                                                                            }), transactions_.end());
    return temp>transactions_.size() ? UserErrorCode::Ok : UserErrorCode::NoTransactionFound;
}