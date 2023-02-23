#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <ostream>

#include "../Include/User.hpp"
#include "../Include/Transaction.hpp"

UserErrorCode User::addTransaction(const std::shared_ptr<Transaction> transaction){
    transaction->setID(TransactionCounter++);
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
    
    std::stringstream is;

    is<<"+-----+------------------------------------------+------------------+----------------------+------------+\n"
    <<"| "<<std::setw(3)<< std::left<< "ID" <<" | "
    <<std::setw(40) << std::left<<"Description"<<" | "
    <<std::setw(16) << std::left<<"Money" <<" | "
    <<std::setw(20) << std::left<<"Expense Category"<<" | "
    <<std::setw(10) << std::left<<"Date" <<" |\n"
    <<"+-----+------------------------------------------+------------------+----------------------+------------+\n";

    allTransations += is.str();

    std::for_each(transactions_.begin(), transactions_.end(),[&allTransations](std::shared_ptr<Transaction> transaction)
                                                               {
                                                                   allTransations += transaction->transactionInString();
                                                               });
    allTransations += "+-------------------------------------------------------------------------------------------------------+\n";

    return allTransations;
}

void User::sortByDate(const SortOrder& SortOrder){
    if(SortOrder == SortOrder::Ascending)
    {   
        auto lambda = [](std::shared_ptr<Transaction> lhs, std::shared_ptr<Transaction> rhs)
        {
            return lhs->getDate() == rhs->getDate() ? lhs->getID() < rhs->getID() : lhs->getDate() < rhs->getDate() ;
        };
        std::sort(transactions_.begin(), transactions_.end(),lambda);
    }

    if(SortOrder == SortOrder::Descending)
    {
        auto lambda = [](std::shared_ptr<Transaction> lhs, std::shared_ptr<Transaction> rhs)
        {
            return lhs->getDate() == rhs->getDate() ? lhs->getID() > rhs->getID() : lhs->getDate() > rhs->getDate() ;
        };
        std::sort(transactions_.begin(), transactions_.end(),lambda);
    }
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

const double User::countWholeEarnings(){
    double earnings{};

    std::for_each(transactions_.begin(),transactions_.end(),[&earnings](std::shared_ptr<Transaction> transaction)
                                                        {
                                                            if(transaction->getMoney()>0)
                                                                earnings+=transaction->getMoney();
                                                        });

    return earnings;
 }


std::map<ExpenseCategory,double> User::countIndividualEarning(){
     std::map<ExpenseCategory,double> map;

     std::for_each(transactions_.begin(),transactions_.end(),[&map](std::shared_ptr<Transaction> transaction)
                                                        {
                                                            if(transaction->getMoney()>0)
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

bool User::savePersonalConfigToFile(){

    std::fstream plik;

    plik.open("../"+configName_, plik.out | plik.trunc);

    if (plik.is_open())
    {
         for(auto it: transactions_){
                plik<<it->getID()<<";"
                    <<it->getDescription()<<";"
                    <<it->getMoney()<<";"
                    <<static_cast<int>(it->getExpenseCategory())<<";"
                    <<it->getDate()<<";\n";
             }
            plik.close();
            return true;

    }else{
        return false;
    }
}
bool User::loadPersonalConfigFromFile(){

     std::vector<std::string> vec;
        char znak;
        std::string linia;
        std::fstream plik;
        plik.open("../"+configName_,plik.in);

        if(plik.is_open()){
           
            while (!plik.eof())
             {
                znak = plik.get();

                if (znak == '\n')
                {
                    
                }
                else if(znak != ';')
                {
                    linia += znak;
                }
                else
                {
                    vec.push_back(linia);
                    linia.clear();
                }
             }
             plik.close();

             for(int i = 0; i<vec.size(); i+=5){
                transactions_.push_back(std::make_shared<Transaction>
                (std::stoi(vec[i]),vec[i+1],std::stod(vec[i+2]),static_cast<ExpenseCategory>(std::stoi(vec[i+3])),Date::DateFromString(vec[i+4]))
                );
             }

             auto it = std::max_element(transactions_.begin(), transactions_.end(), [](std::shared_ptr<Transaction> a, std::shared_ptr<Transaction>  b) {
         return a->getID() < b->getID();
    });
            TransactionCounter = it[0]->getID() + 1;
             return true;

        }else{
            return false;
        }
    
}

void User::addObligation(const std::shared_ptr<Obligations> obligation){
    this->obligations_.push_back(obligation);
    this->sortByDaysToPayment(SortOrder::Ascending);
}

std::string User::printIncomingObligations(int DaysNumberToPayment){
    std::string ObligationsPartInString{};
    
    std::stringstream is;

    is<<"+--------------+--------------+--------------+-------------+------------------+\n"
    <<"| "<<std::setw(12)<< std::left<< "Description" <<" | "
    <<std::setw(11) << std::left<<"Money To Pay"<<" | "
    <<std::setw(10) << std::left<<"Payment Date" <<" | "
    <<std::setw(10) << std::left<<"Days To Pay"<<" | "
    <<std::setw(15) << std::left<<"Loan installment" <<" |\n"
    <<"+--------------+--------------+--------------+-------------+------------------+\n";

    ObligationsPartInString += is.str();

    std::for_each(obligations_.begin(), obligations_.end(),[&ObligationsPartInString, DaysNumberToPayment](std::shared_ptr<Obligations> Obligation)
                                                               {
                                                                    if(Obligation->distanceToPayDate() <= DaysNumberToPayment && Obligation->distanceToPayDate()>=1)
                                                                    {
                                                                        ObligationsPartInString += Obligation->printObligation();
                                                                    }
                                                               });
    ObligationsPartInString += "+-----------------------------------------------------------------------------+\n";

    return ObligationsPartInString;
}

std::string User::printIncomingObligations(){
    return printIncomingObligations(INT_MAX);
}

std::string User::printOverdueObligations(){
    std::string ObligationsPartInString{};
    
    std::stringstream is;

    is<<"+--------------+--------------+--------------+-------------+------------------+\n"
    <<"| "<<std::setw(12)<< std::left<< "Description" <<" | "
    <<std::setw(11) << std::left<<"Money To Pay"<<" | "
    <<std::setw(10) << std::left<<"Payment Date" <<" | "
    <<std::setw(10) << std::left<<"Days To Pay"<<" | "
    <<std::setw(15) << std::left<<"Loan installment" <<" |\n"
    <<"+--------------+--------------+--------------+-------------+------------------+\n";

    ObligationsPartInString += is.str();

    std::for_each(obligations_.begin(), obligations_.end(),[&ObligationsPartInString](std::shared_ptr<Obligations> Obligation)
                                                               {
                                                                    if(Obligation->distanceToPayDate() <= 0)
                                                                    {
                                                                        ObligationsPartInString += Obligation->printObligation();
                                                                    }
                                                               });
    ObligationsPartInString += "+-----------------------------------------------------------------------------+\n";

    return ObligationsPartInString;
}

std::string User::printAllObligations(){
    std::string ObligationsPartInString{};
    
    std::stringstream is;

    is<<"+--------------+--------------+--------------+-------------+------------------+\n"
    <<"| "<<std::setw(12)<< std::left<< "Description" <<" | "
    <<std::setw(11) << std::left<<"Money To Pay"<<" | "
    <<std::setw(10) << std::left<<"Payment Date" <<" | "
    <<std::setw(10) << std::left<<"Days To Pay"<<" | "
    <<std::setw(15) << std::left<<"Loan installment" <<" |\n"
    <<"+--------------+--------------+--------------+-------------+------------------+\n";

    ObligationsPartInString += is.str();

    std::for_each(obligations_.begin(), obligations_.end(),[&ObligationsPartInString](std::shared_ptr<Obligations> Obligation)
                                                               {
                                                                    ObligationsPartInString += Obligation->printObligation();
                                                               });
    ObligationsPartInString += "+-----------------------------------------------------------------------------+\n";

    return ObligationsPartInString;
}

void User::sortByDaysToPayment(const SortOrder& SortOrder){
    if(SortOrder == SortOrder::Ascending)
    {   
        auto lambda = [](std::shared_ptr<Obligations> lhs, std::shared_ptr<Obligations> rhs)
        {
            return lhs->distanceToPayDate() < rhs->distanceToPayDate() ;
        };
        std::sort(obligations_.begin(), obligations_.end(),lambda);
    }

    if(SortOrder == SortOrder::Descending)
    {
        auto lambda = [](std::shared_ptr<Obligations> lhs, std::shared_ptr<Obligations> rhs)
        {
            return lhs->distanceToPayDate() > rhs->distanceToPayDate() ;
        };
        std::sort(obligations_.begin(), obligations_.end(),lambda);
    }
}