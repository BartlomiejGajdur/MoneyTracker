#include <iostream>
#include <algorithm>
#include <map>

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

std::string User::printAllTransations(){
    std::string allTransations{};

    std::for_each(transactions_.begin(), transactions_.end(),[&allTransations](std::shared_ptr<Transaction> transaction)
                                                               {
                                                                   allTransations += transaction->transactionInString();
                                                               });

    return allTransations;
}

void User::sortByNumberOfEnums(){

    struct CompareKeyForTransaction {
    bool operator()(const Transaction& l, const Transaction& r) const {return l.getExpenseCategory() < r.getExpenseCategory();};
};

    std::map<Transaction,int,CompareKeyForTransaction> unMap;
    std::vector<std::pair<Transaction,int>> vecPairs{};

    for(auto tranzaction : transactions_){
        ++unMap[*tranzaction];
    }

    for(auto [key,value] : unMap){
        vecPairs.push_back(std::make_pair(key,value));
    }
    
    auto lambda = [](std::pair<Transaction,int> lhs,std::pair<Transaction,int> rhs){return lhs.second > rhs.second; };
    std::sort(vecPairs.begin(),vecPairs.end(),lambda);

        int i = 0;
        for(auto [pair1,pair2] : vecPairs){
            ExpenseCategory fromPair = pair1.getExpenseCategory();
            pair2+=i;

            for(i; i<pair2 ; i++){

            auto it = std::find_if(transactions_.begin()+i,transactions_.end(),[&fromPair](std::shared_ptr<Transaction> transaction)
                                                                        {
                                                                            return transaction->getExpenseCategory() == fromPair;
                                                                        });
                std::rotate(transactions_.begin()+i,it,transactions_.end());
        }
    }       
}

const double User::countSpendings(){
    double spendings{};

    std::for_each(transactions_.begin(),transactions_.end(),[&spendings](std::shared_ptr<Transaction> transaction)
                                                        {
                                                            if(transaction->getMoney()<0)
                                                                spendings+=transaction->getMoney();
                                                        });

    return spendings;
 }