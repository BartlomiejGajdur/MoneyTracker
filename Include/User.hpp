#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Transaction.hpp"
#include "Obligations.hpp"

using vecTransactionPtr = std::vector<std::shared_ptr<Transaction>>;
using vecObligationsPtr = std::vector<std::shared_ptr<Obligations>>;

enum class UserErrorCode {Ok, NoTransactionFound, IncorrectData};
enum class SortOrder {Ascending, Descending};

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
    void setTransactionCounter(const size_t& Transactioncounter) {TransactionCounter = Transactioncounter;};

    //Getters
    double getCurrentMoney()            const;
    std::string getLogin()              const {return login_;};
    vecTransactionPtr getTransactions() const {return transactions_;};
    vecObligationsPtr getObligations()  const  {return obligations_;};


    //Functions Transactions
    UserErrorCode addTransaction(const std::shared_ptr<Transaction> transaction);
    UserErrorCode removeTransactionById(size_t ID);
    UserErrorCode modifyDateTransactionById(size_t ID,int,int,int);
    std::string printAllTransations();
    inline void clearTransactions() {transactions_.clear();};
    void sortByNumberOfEnums();
    void sortByDate(const SortOrder& SortOrder);
    const double countWholeSpendings();
    const double countWholeEarnings();
    std::map<ExpenseCategory,double> countIndividualSpending();
    std::map<ExpenseCategory,double> percentageOfIndividualSpending();
    std::map<ExpenseCategory,double> countIndividualEarning();

    //Functions Obligations
    void addObligation(const std::shared_ptr<Obligations> obligation);
    std::string printIncomingObligations(int DaysNumberToPayment);

    //Functions Saving/retrieving data
    bool savePersonalConfigToFile();
    bool loadPersonalConfigFromFile();

private:
    vecTransactionPtr transactions_;
    vecObligationsPtr obligations_;
    double currentMoney_{0};
    std::string login_{};
    std::string password_{};
    std::string configName_{};
    size_t TransactionCounter{0};

};