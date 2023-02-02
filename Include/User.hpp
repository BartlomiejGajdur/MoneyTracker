#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Transaction.hpp"

using vecTransactionPtr = std::vector<std::shared_ptr<Transaction>>;

enum class UserErrorCode {Ok, NoTransactionFound, IncorrectData};



class User{

public:
    User() = default;
    User(const std::tuple<std::string,std::string,std::string> userData): configName_(std::get<0>(userData)),
                                                                            login_(std::get<1>(userData)),
                                                                            password_(std::get<2>(userData))
                                                                                                         {
                                                                                                            loadPersonalConfigFromFile();
                                                                                                         };

    ~User(){savePersonalConfigToFile();};
    //Setters
    void setCurrentMoney(const double& currentMoney);
    //Getters
    double getCurrentMoney() const;


    inline void clearTransactions() {transactions_.clear();};

    UserErrorCode addTransaction(const std::shared_ptr<Transaction> transaction);
    UserErrorCode removeTransactionById(size_t ID);
    UserErrorCode modifyDateTransactionById(size_t ID,int,int,int);
    std::string printAllTransations();
    void sortByNumberOfEnums();
    const double countWholeSpendings();
    std::map<ExpenseCategory,double> countIndividualSpending();
    std::map<ExpenseCategory,double> percentageOfIndividualSpending();

    void savePersonalConfigToFile();
    void loadPersonalConfigFromFile();


private:
    vecTransactionPtr transactions_;
    double currentMoney_{0};
    std::string login_{};
    std::string password_{};
    std::string configName_{};

    size_t TransactionCounter{0}; // przypisz do odczytanego ID ostatniego 
};