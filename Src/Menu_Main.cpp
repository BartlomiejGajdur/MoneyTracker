#include <cmath>

#include "../Include/MenuFunctions.hpp"
#include "../Include/Menu_Main.hpp"
#include "../Include/User.hpp"
#include "../Include/Transaction.hpp"
#include "../Include/Date.hpp"

void Menu_Main::greetUser(const User& User){
    MenuFunctions::ClearTerminal();
    std::string moneyToDisplay = std::to_string(User.getCurrentMoney());
    moneyToDisplay.erase(moneyToDisplay.length()-4,moneyToDisplay.length());
    moneyToDisplay+=" PLN\n";
    std::cout <<"                                  Hello "+std::get<1>(ValidatePassword::getCurrentUser()) +"!                      "<<Date::currentData()<<"\n";
    std::cout <<"                        Current balance: ";
    User.getCurrentMoney() >= 0 ? std::cout<<MenuFunctions::SetTextColor(Color::Green,"+"+moneyToDisplay) :
                                  std::cout<<MenuFunctions::SetTextColor(Color::Red, moneyToDisplay);
}

void Menu_Main::printOptions(){

    std::cout <<"+----------------------------------OPTIONS-----------------------------------+\n";
    std::cout <<"| > 1.   Add new transaction                                                 |\n";
    std::cout <<"| > 2.   Set current money                                                   |\n";
    std::cout <<"| > 3.   Print all transactions                                              |\n";
    std::cout <<"| > 4.   Sort transaction by date                                            |\n";
    std::cout <<"| > 5.   Sort transaction by number of expense category                      |\n";
    std::cout <<"| > 6.   Show earnings on individual expense category                        |\n";
    std::cout <<"| > 7.   Show spendings on individual expense category                       |\n";
    std::cout <<"| > 8.   Modify date transaction by ID                                       |\n";
    std::cout <<"| > 9.   Remove transaction by ID                                            |\n";
    std::cout <<"| > 10.  Delete all transactions                                             |\n";
    std::cout <<"| > 0.   SAVE & EXIT                                                         |\n";
    std::cout <<"+----------------------------------------------------------------------------+\n";
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
    user.sortByDate(SortOrder::Descending);
    
}

void Menu_Main::SetCurrentMoney_Menu(User& user){
    MenuFunctions::ClearTerminal();


    int moneyToSet;
    std::cout<<"Insert your current balance:\n";
    moneyToSet = MenuFunctions::insertNumber(-99999,99999);
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
        do{
            greetUser(User);
            printOptions();
            liczba = MenuFunctions::insertNumber(0,10);
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
            case 0:
                MenuFunctions::ClearTerminal();
                std::cout<<" Goodbay! \n";
                MenuFunctions::WaitForAction();
                
                break;
            default:
                break;
            }
        }while(liczba != 0);



    }

}