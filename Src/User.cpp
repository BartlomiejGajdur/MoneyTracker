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
#include "../Include/Bills.hpp"
#include "../Include/Loan.hpp"
#include "../Include/MenuFunctions.hpp"

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

    for(auto Transaction : transactions_){
        ++unMap[*Transaction];
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

    }else{
        return false;
    }

    std::fstream plik2;

    plik2.open("../"+configName_+"O", plik2.out | plik2.trunc);

    if (plik2.is_open())
    {
         for(auto it: obligations_){
                if (auto derived_ptr = std::dynamic_pointer_cast<Bills>(it)) 
                    {
                         plik2<<static_cast<int>(derived_ptr->getType())<<";"
                        <<derived_ptr->getMoneyToPay()<<";"
                        <<derived_ptr->getPaymentDate()<<";\n";
                    } 
                    else if (auto derived_ptr = std::dynamic_pointer_cast<Loan>(it)) 
                    {   
                       plik2<<derived_ptr->getDescription()<<";"
                        <<derived_ptr->getMoneyToPay()<<";"
                        <<derived_ptr->getPaymentDate()<<";"
                        <<derived_ptr->getNumberOfInstallments_()<<";\n";
                    } 
        }
            plik2.close();

    }else{
        return false;
    }

    return true;
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
        }else{
            return false;
        }

    std::vector<std::string> vec2;
    char znak2;
    std::string linia2;
    std::fstream plik2;
    plik2.open("../"+configName_+"O",plik2.in);

        if(plik2.is_open()){
           
            while (!plik2.eof())
             {
                znak2 = plik2.get();

                if (znak2 == '\n')
                {
                    
                }
                else if(znak2 != ';')
                {
                    linia2 += znak2;
                }
                else
                {
                    vec2.push_back(linia2);
                    linia2.clear();
                }
             }

             plik2.close();

        
             for(int i = 0; i<vec2.size();){
                if(vec2[i] == "0" || vec2[i] == "1" || vec2[i] == "2" || vec2[i] == "3")
                {
                    obligations_.push_back(std::make_shared<Bills>
                    (static_cast<BillType>(std::stoi(vec2[i])),std::stod(vec2[i+1]),Date::DateFromString(vec2[i+2])));
                    i += 3;
                }else{
                    obligations_.push_back(std::make_shared<Loan>
                    (vec2[i],std::stod(vec2[i+1]),Date::DateFromString(vec2[i+2]), std::stoi(vec2[i+3])));
                    i += 4;
                }
                
             }
        return true;
    }else{
        return false;
    }
}


void User::addObligation(const std::shared_ptr<Obligations> obligation){
    this->obligations_.push_back(obligation);
    this->sortByDaysToPayment(SortOrder::Ascending);
}

std::string User::printIncomingObligations(int DaysNumberToPayment) const{
    std::string ObligationsPartInString{};
    
    std::stringstream is;
    is<<"+--------------+--------------INCOMING PAYMENTS------------+--------------------+\n"
    <<"| "<<std::setw(12)<< std::left<< "Description" <<" | "
    <<std::setw(11) << std::left<<"Money To Pay"<<" | "
    <<std::setw(10) << std::left<<"Payment Date" <<" | "
    <<std::setw(10) << std::left<<"Days To Pay"<<" | "
    <<std::setw(18) << std::left<<"Loan installment" <<" |\n"
    <<"+--------------+--------------+--------------+-------------+--------------------+\n";

    ObligationsPartInString += is.str();

    std::for_each(obligations_.begin(), obligations_.end(),[&ObligationsPartInString, DaysNumberToPayment](std::shared_ptr<Obligations> Obligation)
                                                               {
                                                                    if(Obligation->distanceToPayDate() <= DaysNumberToPayment)
                                                                    {
                                                                        ObligationsPartInString += Obligation->printObligation();
                                                                    }
                                                               });
    ObligationsPartInString += "+-------------------------------------------------------------------------------+\n";

    auto it = std::find_if(obligations_.begin(), obligations_.end(),[DaysNumberToPayment](std::shared_ptr<Obligations> Obligation)
                                                               {
                                                                    return Obligation->distanceToPayDate() <= DaysNumberToPayment;
                                                                   
                                                               });

    if(it == obligations_.end())
    {   
        std::stringstream is2;
        ObligationsPartInString.clear();
            is2<<"+-------------------------------------------------------------------------------+\n"
            <<"| "<<std::setw(94)<< std::left<< MenuFunctions::SetBoldText(MenuFunctions::SetTextColor(Color::Green, "                     No incomming fees within 7 days!")) <<" | \n"
            <<"+-------------------------------------------------------------------------------+\n";
            ObligationsPartInString+=is2.str();
    }

    return ObligationsPartInString;
}
                  

std::string User::printIncomingObligations(){
    return printIncomingObligations(INT_MAX);
}

std::string User::printOverdueObligations(){
    std::string ObligationsPartInString{};
    
    std::stringstream is;

    is<<"+--------------+--------------+--------------+-------------+--------------------+\n"
    <<"| "<<std::setw(12)<< std::left<< "Description" <<" | "
    <<std::setw(11) << std::left<<"Money To Pay"<<" | "
    <<std::setw(10) << std::left<<"Payment Date" <<" | "
    <<std::setw(10) << std::left<<"Days To Pay"<<" | "
    <<std::setw(18) << std::left<<"Loan installment" <<" |\n"
    <<"+--------------+--------------+--------------+-------------+--------------------+\n";

    ObligationsPartInString += is.str();

    std::for_each(obligations_.begin(), obligations_.end(),[&ObligationsPartInString](std::shared_ptr<Obligations> Obligation)
                                                               {
                                                                    if(Obligation->distanceToPayDate() <= 0)
                                                                    {
                                                                        ObligationsPartInString += Obligation->printObligation();
                                                                    }
                                                               });
    ObligationsPartInString += "+-------------------------------------------------------------------------------+\n";

    

    return ObligationsPartInString;
}

std::string User::printAllObligations() const{
    std::string ObligationsPartInString{};
    
    std::stringstream is;

    is<<"+--------------+--------------+--------------+-------------+--------------------+\n"
    <<"| "<<std::setw(12)<< std::left<< "Description" <<" | "
    <<std::setw(11) << std::left<<"Money To Pay"<<" | "
    <<std::setw(10) << std::left<<"Payment Date" <<" | "
    <<std::setw(10) << std::left<<"Days To Pay"<<" | "
    <<std::setw(18) << std::left<<"Loan installment" <<" |\n"
    <<"+--------------+--------------+--------------+-------------+--------------------+\n";

    ObligationsPartInString += is.str();

    std::for_each(obligations_.begin(), obligations_.end(),[&ObligationsPartInString](std::shared_ptr<Obligations> Obligation)
                                                               {
                                                                    ObligationsPartInString += Obligation->printObligation();
                                                               });
    ObligationsPartInString += "+-------------------------------------------------------------------------------+\n";

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

void User::payBills(){
        do{
            std::for_each(obligations_.begin(), obligations_.end(),[&](std::shared_ptr<Obligations> obligation)
            {
                if(obligation->distanceToPayDate() <= 0)
                {
                    if (auto derived_ptr = std::dynamic_pointer_cast<Bills>(obligation)) 
                    {
                        this->addTransaction(std::make_shared<Transaction>(derived_ptr->getBillType(),-derived_ptr->getMoneyToPay(),ExpenseCategory::Bills));
                        derived_ptr->nextMonth();    
                    } 
                    else if (auto derived_ptr = std::dynamic_pointer_cast<Loan>(obligation)) 
                    {   
                        if(derived_ptr->getNumberOfInstallments_() > 0){
                            this->addTransaction(std::make_shared<Transaction>(derived_ptr->getDescription(),-derived_ptr->getMoneyToPay(),ExpenseCategory::Loan));
                            derived_ptr->InstallmentsPaid();
                            derived_ptr->nextMonth(); 
                        }else{
                            do{
                                derived_ptr->nextMonth();
                            }while(obligation->distanceToPayDate() <= 0); 
                        }
                        
                    } 
                    else 
                    {
                        std::cout<<"ERROR";
                    }
                }
            });
        }while(std::find_if(obligations_.begin(),obligations_.end(),[](std::shared_ptr<Obligations> ptr){ return ptr->distanceToPayDate()<=0;}) != obligations_.end());

    auto it = std::remove_if(obligations_.begin(),obligations_.end(),[](std::shared_ptr<Obligations> ptr){ return ptr->getNumberOfInstallments_() <= 0;});
    obligations_.erase(it,obligations_.end());

  
  this->sortByDaysToPayment(SortOrder::Ascending);
}
