#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <fstream>

#include "../Include/User.hpp"
#include "../Include/Transaction.hpp"

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

UserErrorCode User::modifyDateTransactionById(size_t ID,int day,int month,int year){

    DateErrorCode dateErrorCode = DateErrorCode::ERROR404;

    std::for_each(transactions_.begin(),transactions_.end(),[&](const std::shared_ptr<Transaction>& transaction)
                                                                        {
                                                                            if(transaction->getID() == ID)
                                                                            {
                                                                                dateErrorCode = transaction->setDate(day,month,year);
                                                                            }
                                                                      });
    if(dateErrorCode == DateErrorCode::InvalidDay ||
        dateErrorCode == DateErrorCode::InvalidMonth ||
        dateErrorCode == DateErrorCode::InvalidYear)
    {
        return UserErrorCode::IncorrectData;
    } 
    else if (dateErrorCode == DateErrorCode::Ok)
    {
        return UserErrorCode::Ok;
    }
    return UserErrorCode::NoTransactionFound;
                                                                 
    
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

const double User::countWholeSpendings(){
    double spendings{};

    std::for_each(transactions_.begin(),transactions_.end(),[&spendings](std::shared_ptr<Transaction> transaction)
                                                        {
                                                            if(transaction->getMoney()<0)
                                                                spendings+=transaction->getMoney();
                                                        });

    return spendings;
 }

std::map<ExpenseCategory,double> User::countIndividualSpending(){
    std::map<ExpenseCategory,double> map;

     std::for_each(transactions_.begin(),transactions_.end(),[&map](std::shared_ptr<Transaction> transaction)
                                                        {
                                                            if(transaction->getMoney()<0)
                                                                {
                                                                    map[transaction->getExpenseCategory()] += transaction->getMoney();
                                                                }
                                                        });

    return map;
}

std::map<ExpenseCategory,double> User::percentageOfIndividualSpending(){
    
    std::map<ExpenseCategory,double> map = this->countIndividualSpending();
    double wholeSpendigs = this->countWholeSpendings();

    for(auto& [Key,Value] : map){
        Value = (Value/wholeSpendigs) * 100;
    }

    return map;
}

double User::getCurrentMoney() const {
    
    double currentMoney = currentMoney_;

    std::for_each(transactions_.begin(),transactions_.end(),[&](std::shared_ptr<Transaction> transaction)
                                                                                                        {
                                                                                                            currentMoney+= transaction->getMoney();
                                                                                                        });
    currentMoney = std::round(currentMoney*1000.0)/1000.0;
    return currentMoney;
}

void User::setCurrentMoney(const double& currentMoney){
  
    double bilance = this->getCurrentMoney();

    this->addTransaction(std::make_shared<Transaction>("Alignment by user",currentMoney - bilance,ExpenseCategory::SettingTheBill));

}

void User::savePersonalConfigToFile(){

    std::fstream plik;

    plik.open("../"+configName_, plik.out | plik.trunc);

    if (plik.is_open())
    {
         for(auto it: transactions_){
                plik<<it->getID()<<";"
                    <<it->getDescription()<<";"
                    <<it->getMoney()<<";"
                    <<it->returnExpenseCategoryInString(it->getExpenseCategory())<<";"
                    <<it->getDate()<<";\n";
             }
            plik.close();

    }else{
        std::cout<<"Problem with FILE;/\n";
    }

}