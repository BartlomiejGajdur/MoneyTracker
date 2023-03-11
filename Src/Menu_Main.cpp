#include <cmath>
#include <fstream>
#include <iostream>

#include "../Include/MenuFunctions.hpp"
#include "../Include/Menu_Main.hpp"
#include "../Include/User.hpp"
#include "../Include/Transaction.hpp"
#include "../Include/Date.hpp"
#include "../Include/ExcelGenerator.hpp"
#include "../Include/Bills.hpp"
#include "../Include/Loan.hpp"

void Menu_Main::AddNewObligation_Menu(User& User){
    MenuFunctions::ClearTerminal();


    int BillChoice, choice = MenuFunctions::arrowMenu({{"Loan"},{"Bill"},{"EXIT"}});
    std::string desc,dateInString;
    double moneyToPay;
    int NumberOfLoans;
    Date PaymentDate;

            switch (choice)
            {
            case 1:
    MenuFunctions::ClearTerminal();
                std::cout<<"Insert loan Description\n>";
                std::getline(std::cin,desc);
                std::getline(std::cin,desc);
    MenuFunctions::ClearTerminal();
                std::cout<<"Insert Money to pay\n>";
                moneyToPay = MenuFunctions::insertNumber(0.0,99999.0);
    MenuFunctions::ClearTerminal();
                std::cout<<"Insert payment date in format DD.MM.YYYY\n>";
                std::getline(std::cin,dateInString);
                std::getline(std::cin,dateInString);
                PaymentDate = Date::DateFromString(dateInString);
    MenuFunctions::ClearTerminal();
                std::cout<<"Insert number of payments:\n";
                NumberOfLoans = MenuFunctions::insertNumber(1,99);

                User.addObligation(std::make_shared<Loan>(desc, moneyToPay,PaymentDate, NumberOfLoans));
                
                break;
            case 2:
                
 
    BillChoice = MenuFunctions::arrowMenu({{"Water"},{"Gas"},{"Internet"},{"Electricity"}});
    MenuFunctions::ClearTerminal();
                std::cout<<"Insert Money to pay\n>";
                moneyToPay = MenuFunctions::insertNumber(0.0,99999.0);
    MenuFunctions::ClearTerminal();
                std::cout<<"Insert payment date in format DD.MM.YYYY\n>";
                std::getline(std::cin,dateInString);
                std::getline(std::cin,dateInString);
                PaymentDate = Date::DateFromString(dateInString);

        User.addObligation(std::make_shared<Bills>(static_cast<BillType>(BillChoice), moneyToPay,PaymentDate));
            
                break;
            default:
                break;
            }
    if(choice != 0)
    {
        MenuFunctions::ClearTerminal();
        std::cout<<MenuFunctions::SetTextColor(Color::Green, "Obligation added correctly! :)\n");
    }
    MenuFunctions::WaitForAction();
}

void Menu_Main::ObligationsMenuRun(User& User){
    MenuFunctions::ClearTerminal();
    int choice = MenuFunctions::arrowMenu({{"Show all obligations"},{"Add new obligation"},{"Pay all obligations"},{"EXIT"}});
    int choice2;
    double temp;
    MenuFunctions::ClearTerminal();
    switch (choice)
    {
    case 1:
        MenuFunctions::ClearTerminal();
        std::cout<<User.printAllObligations();
        MenuFunctions::WaitForAction();
        break;
    case 2:
        AddNewObligation_Menu(User);
        break;
    case 3:
                MenuFunctions::ClearTerminal();
                temp = User.getCurrentMoney();
                User.payBills();
                temp > User.getCurrentMoney() ?
                std::cout<<MenuFunctions::SetTextColor(Color::Green,"All obligations have been paid!\n") :
                std::cout<<MenuFunctions::SetTextColor(Color::Red,"No obligations to paid found!\n");
                MenuFunctions::WaitForAction();
        break;
    
    default:
        break;
    }

}

bool Menu_Main::fileExists(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}

std::string Menu_Main::findFreeFileName(){
    std::string fileName = "MoneyTracker_Summary_" + Date::currentDataInString() + ".xlsx";
    int counter{1};
    while (fileExists(fileName))
    {   
        if(counter > 1 && counter != 10 ){
            fileName.erase(fileName.begin() + fileName.size() - 8 - std::to_string(counter).size(), fileName.begin() + fileName.size() - 5);
        }else if ( counter == 10)
        {
            fileName.erase(fileName.begin() + fileName.size() - 9, fileName.begin() + fileName.size() - 5);
        }

        fileName.insert(fileName.size() - 5, "_(" + std::to_string(counter++) + ")" );
    }

    return fileName;
}

void Menu_Main::excelMenuRun(const User& User, ExcelGenerator& ExcelGenerator){
    
    std::string FileName = findFreeFileName();
    ExcelGenerator.updateTransactions(User);
    ExcelGenerator.open_Excel(FileName,"Summary");
    
    std::vector<std::pair<std::string,bool>> vec{
        std::make_pair<std::string,bool>("GreetUser            | ",false),
        std::make_pair<std::string,bool>("CurrentMoney         | ",false),
        std::make_pair<std::string,bool>("Transactions         | ",false),
        std::make_pair<std::string,bool>("PieChartSpendings    | ",false),
        std::make_pair<std::string,bool>("PieChartEarnigns     | ",false),
        std::make_pair<std::string,bool>("SummaryTable         | ",false),
        std::make_pair<std::string,bool>("Generate Excel File",false),
        };
        MenuFunctions::arrowMenu(vec);

        if(vec[0].second)
            ExcelGenerator.greetUser_Excel();
        
        if(vec[1].second)
            ExcelGenerator.CurrentMoney_Excel();

        if(vec[2].second)
            ExcelGenerator.Transactions_Excel();

        if(vec[3].second)
            ExcelGenerator.PieChart_Excel(ExcelGenerator.getUser().percentageOfIndividualSpending(), "Percentage Of Individual Spendings");

        if(vec[4].second)
            ExcelGenerator.PieChart_Excel(ExcelGenerator.getUser().countIndividualEarning(), "Percentage Of Individual Earnings");

        if(vec[5].second)
            ExcelGenerator.SummaryTable_Excel();

    MenuFunctions::ClearTerminal();
    std::cout<<MenuFunctions::SetTextColor(Color::Green, "Excel File Generated Correctly!\n> FileName: " + FileName + " \n");
    MenuFunctions::WaitForAction();
}



void Menu_Main::greetUser(const User& User){
    MenuFunctions::ClearTerminal();
    std::string moneyToDisplay = std::to_string(User.getCurrentMoney());
    moneyToDisplay.erase(moneyToDisplay.length()-4,moneyToDisplay.length());
    moneyToDisplay+=" PLN\n";
    std::cout <<"                                  Hello "+std::get<1>(ValidatePassword::getCurrentUser()) +"!                      "<<Date::currentData()<<"\n";
    std::cout <<"                        Current balance: ";
    User.getCurrentMoney() >= 0 ? std::cout<<MenuFunctions::SetTextColor(Color::Green,"+"+moneyToDisplay) :
                                  std::cout<<MenuFunctions::SetTextColor(Color::Red, moneyToDisplay);
    std::cout<<std::endl;
    std::cout<< User.printIncomingObligations(7);
}

void Menu_Main::printOptions(){

    std::cout <<"+----------------------------------OPTIONS--------------------------------------+\n";
    std::cout <<"| > 1.   Add new transaction                                                    |\n";
    std::cout <<"| > 2.   Set current money                                                      |\n";
    std::cout <<"| > 3.   Print all transactions                                                 |\n";
    std::cout <<"| > 4.   Sort transaction by date                                               |\n";
    std::cout <<"| > 5.   Sort transaction by number of expense category                         |\n";
    std::cout <<"| > 6.   Show earnings on individual expense category                           |\n";
    std::cout <<"| > 7.   Show spendings on individual expense category                          |\n";
    std::cout <<"| > 8.   Modify date transaction by ID                                          |\n";
    std::cout <<"| > 9.   Remove transaction by ID                                               |\n";
    std::cout <<"| > 10.  Delete all transactions                                                |\n";
    std::cout <<"| > 11.  "<<MenuFunctions::SetTextColor(Color::Yellow,"Generate Summary in Excel file")<<"                                         |\n";
    std::cout <<"| > 12.  "<<MenuFunctions::SetTextColor(Color::Yellow,"Obligations Menu")<<"                                                       |\n";
    std::cout <<"| > 0.   SAVE & EXIT                                                            |\n";
    std::cout <<"+-------------------------------------------------------------------------------+\n";
}

void Menu_Main::AddNewTransaction_Menu(User& user){
    MenuFunctions::ClearTerminal();
    int choice{};
    double money;
    std::string description;
    int expenseCatInINt;

    

    choice = MenuFunctions::arrowMenu({"Earning","Expense","EXIT"});
    switch (choice)
    {
    case 1:
        MenuFunctions::ClearTerminal();
        std::cout<<"Insert description\n:";
        std::getline( std::cin, description );
        std::getline( std::cin, description );
        std::cout<<"\nInsert earned money\n:";
        money = MenuFunctions::insertNumber(0.0,99999.99);
        std::cout<<"\nInsert earn category\n:";
        expenseCatInINt = MenuFunctions::arrowMenu({"Savings","Work","Other"});
        if(expenseCatInINt == 0)
            expenseCatInINt = 3;
        user.addTransaction(std::make_shared<Transaction>(description,money,static_cast<ExpenseCategory>(expenseCatInINt+10)));
        std::cout<<MenuFunctions::SetTextColor(Color::Green,"Transaction added, corectlly!:)\n");

        MenuFunctions::WaitForAction();
        break;
    case 2:
        MenuFunctions::ClearTerminal();
        std::cout<<"Insert description\n:";
        std::getline( std::cin, description );
        std::getline( std::cin, description );
        std::cout<<"\nInsert expense amount\n:";
        money = MenuFunctions::insertNumber(0.0,99999.99);
        std::cout<<"\nInsert expense category\n:";
        expenseCatInINt = MenuFunctions::arrowMenu({"Housing","Transportation","Food", "Utilities", "Insurance", "Medical", "PersonalSpending", "Entertainment", "Miscellaneous", "SettingTheBill"});
        if(expenseCatInINt == 0)
            expenseCatInINt = 10;
        user.addTransaction(std::make_shared<Transaction>(description,-money,static_cast<ExpenseCategory>(expenseCatInINt)));
        std::cout<<MenuFunctions::SetTextColor(Color::Green,"Transaction added, corectlly!:)\n");

        MenuFunctions::WaitForAction();
        break;
    
    default:
        break;
    }
    
}

void Menu_Main::SetCurrentMoney_Menu(User& user){
    MenuFunctions::ClearTerminal();


    double moneyToSet;
    std::cout<<"Insert your current balance:\n";
    moneyToSet = MenuFunctions::insertNumber(-99999.9,99999.9);
    user.setCurrentMoney(moneyToSet);
    std::cout<<MenuFunctions::SetTextColor(Color::Green,"Your current balance have been set to " + std::to_string(moneyToSet) + "PLN, correctly!\n" );

    user.sortByDate(SortOrder::Descending);

    MenuFunctions::WaitForAction();
}

void Menu_Main::printAllTransactions_Menu(User& user){
    MenuFunctions::ClearTerminal();

    std::cout<<user.printAllTransations();


    MenuFunctions::WaitForAction();
}

void Menu_Main::sortTransactionByDate_Menu(User& user){
    MenuFunctions::ClearTerminal();

    int choice;
    choice = MenuFunctions::arrowMenu({"Ascending","Descending","EXIT"});

    switch (choice)
    {
    case 1:
        user.sortByDate(SortOrder::Ascending);
        break;
    case 2:
        user.sortByDate(SortOrder::Descending);
        break;
    case 0:
            
        break;
    default:
        break;
    }

    MenuFunctions::WaitForAction();
}

void Menu_Main::sortTransactionByNumberOfExpenseCategory_Menu(User& user){
    MenuFunctions::ClearTerminal();


    user.sortByNumberOfEnums();
    std::cout<<MenuFunctions::SetTextColor(Color::Green,"All your transactions have been sorted by the number of expense category, correctly! \n");


    MenuFunctions::WaitForAction();
}

void Menu_Main::showEarningsOnIndividualExpenseCategory_Menu(User& user){ 
    MenuFunctions::ClearTerminal();
    std::string zestawienie;
    int counterColor = static_cast<int>(Color::Red);
    std::map<ExpenseCategory,double> map = user.countIndividualEarning();
    double wholeEarnings = user.countWholeEarnings();


     for(auto[key,value] : map){
        std::cout<<Transaction::returnExpenseCategoryInString(key) <<":"<<value<<"\n[";
        value = round((value/wholeEarnings) * 100);
        for(int i = 0; i<int(value); i++){
            std::cout<<MenuFunctions::SetBackgroundColor(static_cast<Color>(counterColor), " ");
            zestawienie += MenuFunctions::SetBackgroundColor(static_cast<Color>(counterColor), " ");
        }

        if(static_cast<Color>(++counterColor) == Color::White)
        {
            counterColor = 90;
        }

        for(int i = 0; i<100-int(value); i++){
            std::cout<<MenuFunctions::SetBackgroundColor(Color::White, " ");
        }
        std::cout<<"]  ->" <<value<<"%\n\n";
        
     }
    
    std::cout<<MenuFunctions::SetBoldText("                                           Summary of results:");
    std::cout<<"\n["+ zestawienie +"]\n";

     MenuFunctions::WaitForAction();
}

void Menu_Main::showSpendingsPercentageOnIndividualExpenseCategory_Menu(User& user){
     MenuFunctions::ClearTerminal();
    std::string zestawienie;
    int counterColor = static_cast<int>(Color::Red);
    std::map<ExpenseCategory,double> map = user.countIndividualSpending();
    double wholeSpendigs = user.countWholeSpendings();


     for(auto[key,value] : map){
        std::cout<<Transaction::returnExpenseCategoryInString(key) <<":"<<value<<"\n[";
        value = round((value/wholeSpendigs) * 100);
        for(int i = 0; i<int(value); i++){
            std::cout<<MenuFunctions::SetBackgroundColor(static_cast<Color>(counterColor), " ");
            zestawienie += MenuFunctions::SetBackgroundColor(static_cast<Color>(counterColor), " ");
        }

        if(static_cast<Color>(++counterColor) == Color::White)
        {
            counterColor = 90;
        }

        for(int i = 0; i<100-int(value); i++){
            std::cout<<MenuFunctions::SetBackgroundColor(Color::White, " ");
        }
        std::cout<<"]  ->" <<value<<"%\n\n";
        
     }
    
    std::cout<<MenuFunctions::SetBoldText("                                           Summary of results:");
    std::cout<<"\n["+ zestawienie +"]\n";

     MenuFunctions::WaitForAction();
}

void Menu_Main::modifyDateTransactionByID_Menu(User& user){ 
     MenuFunctions::ClearTerminal();

     std::string dateInString;
     int ID, day,month,year;

     std::cout<<"Insert transaction ID number to set date\n>";
     ID = MenuFunctions::insertNumber();

    MenuFunctions::ClearTerminal();
    std::cout<<"Transaction ID for which you want to change the date: "<< ID <<"\n";
    std::cout<<"DD-MM-YYYY\n";
    std::cout<<"Insert day\n>";
    day = MenuFunctions::insertNumber();

    MenuFunctions::ClearTerminal();
    std::cout<<"Transaction ID for which you want to change the date: "<< ID <<"\n";
    std::cout<<day<<"-MM-YYYY\n";
    std::cout<<"Insert month\n>";
    month = MenuFunctions::insertNumber();

    MenuFunctions::ClearTerminal();
    std::cout<<"Transaction ID for which you want to change the date: "<< ID <<"\n";
    std::cout<<day<<"-"<<month<<"-YYYY\n";
    std::cout<<"Insert year\n>";
    year = MenuFunctions::insertNumber();

    MenuFunctions::ClearTerminal();
    std::cout<<"Transaction ID for which you want to change the date: "<< ID <<"\n";
    std::cout<<day<<"-"<<month<<"-"<<year<<"\n";
    UserErrorCode UserError = user.modifyDateTransactionById(ID,day, month, year);
     
     if(UserError == UserErrorCode::Ok)
     {
       std::cout<<MenuFunctions::SetTextColor(Color::Green, "New date have been setted correctly!\n");
     }else if( UserError == UserErrorCode::IncorrectData)
     {
       std::cout<<MenuFunctions::SetTextColor(Color::Red, "Incorrect date given!\n");
     }else
     {
       std::cout<<MenuFunctions::SetTextColor(Color::Red, "Transaction with given ID have not been found!\n");
     }


     MenuFunctions::WaitForAction(); 
}

void Menu_Main::removeTransactionByID_Menu(User& user){ 
    MenuFunctions::ClearTerminal();


    int choice;
    std::cout<<"Insert ID number, which u want to remove\n>";
    choice = MenuFunctions::insertNumber();
    user.removeTransactionById(choice) == UserErrorCode::Ok ?
    std::cout<<MenuFunctions::SetTextColor(Color::Green, "Transaction with given ID removed correctly :)\n") : 
    std::cout<<MenuFunctions::SetTextColor(Color::Red, "Transaction with given ID have not been found ;/\n");
    MenuFunctions::WaitForAction(); 


}

void Menu_Main::deleteAllTransactions_Menu(User& user){
     MenuFunctions::ClearTerminal();


    user.clearTransactions();
    user.setTransactionCounter(0);
    std::cout<<MenuFunctions::SetTextColor(Color::Green,"All your transactions have been deleted, correctly! \n");

    MenuFunctions::WaitForAction();
}


void Menu_Main::run(){
    MenuLOG.run();
    std::string description;
    int money;
    int expenseCatInINt;
    ExpenseCategory expenseCategory;
    int liczba = 0;


    if(std::get<0>(ValidatePassword::getCurrentUser()) != "LogedOUT"){
       

        User User{ValidatePassword::getCurrentUser()};
        ExcelGenerator ExcelGenerator{User};
        do{
            greetUser(User);
            printOptions();
            liczba = MenuFunctions::insertNumber(0,12);
            switch (liczba)
            {
            case 1:
                AddNewTransaction_Menu(User);
                
                break;
            case 2:
                SetCurrentMoney_Menu(User);

                break;
            case 3:
                printAllTransactions_Menu(User);

                break;
            case 4:
                sortTransactionByDate_Menu(User);
                
                break;
            case 5:
                sortTransactionByNumberOfExpenseCategory_Menu(User);
                
                break;
            case 6:
                showEarningsOnIndividualExpenseCategory_Menu(User);
                
                break;
            case 7:
                showSpendingsPercentageOnIndividualExpenseCategory_Menu(User);
                
                break;
            case 8:
                modifyDateTransactionByID_Menu(User);
                
                break;
            case 9:
                removeTransactionByID_Menu(User);
                
                break;
            case 10:
                deleteAllTransactions_Menu(User);
                
                break;
            case 11:
                if(User.getTransactions().size() > 0)
                {
                    excelMenuRun(User, ExcelGenerator);
                }
                else
                {
                    MenuFunctions::ClearTerminal();
                    std::cout<<MenuFunctions::SetTextColor(Color::Red, "You must have at least one transaction assigned to your account!\n");
                    MenuFunctions::WaitForAction();
                }          
                break;
            case 12:
                ObligationsMenuRun(User);
                
                break;
            case 0:
                MenuFunctions::ClearTerminal();
                User.savePersonalConfigToFile();            
                ExcelGenerator.close_Excel();
                break;
            default:
                break;
            }
        }while(liczba != 0);



    }

}