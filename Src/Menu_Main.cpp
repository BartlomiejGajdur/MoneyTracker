#include "../Include/MenuFunctions.hpp"
#include "../Include/Menu_Main.hpp"
#include "../Include/User.hpp"
#include "../Include/Transaction.hpp"

void Menu_Main::greetUser(const User& User){
    MenuFunctions::ClearTerminal();
    std::string moneyToDisplay = std::to_string(User.getCurrentMoney())+" PLN\n";
    std::cout <<"                                  Hello "+std::get<1>(ValidatePassword::getCurrentUser()) +"!\n";
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
    std::cout <<"| > 6.   Show spendings on individual expense category                       |\n";
    std::cout <<"| > 7.   Show spendings percentage on individual expense category            |\n";
    std::cout <<"| > 8.   Modify date transaction by ID                                       |\n";
    std::cout <<"| > 9.   Remove transaction by ID                                            |\n";
    std::cout <<"| > 10.  Delete all transactions                                             |\n";
    std::cout <<"| > 0.   SAVE & EXIT                                                         |\n";
    std::cout <<"+----------------------------------------------------------------------------+\n";
}

void Menu_Main::AddNewTransaction_Menu(User& user){

}

void Menu_Main::SetCurrentMoney_Menu(User& user){
    MenuFunctions::ClearTerminal();


    int moneyToSet;
    std::cout<<"Insert your current balance:\n";
    moneyToSet = MenuFunctions::insertNumber(-99999,99999);
    user.setCurrentMoney(moneyToSet);
    std::cout<<MenuFunctions::SetTextColor(Color::Green,"Your current balance have been set to " + std::to_string(moneyToSet) + "PLN, correctly!\n" );


    MenuFunctions::WaitForAction();
}

void Menu_Main::printAllTransactions_Menu(User& user){
    MenuFunctions::ClearTerminal();


    std::cout<<user.printAllTransations();


    MenuFunctions::WaitForAction();
}

void Menu_Main::sortTransactionByDate_Menu(User& user){

}

void Menu_Main::sortTransactionByNumberOfExpenseCategory_Menu(User& user){
    MenuFunctions::ClearTerminal();


    user.sortByNumberOfEnums();
    std::cout<<MenuFunctions::SetTextColor(Color::Green,"All your transactions have been sorted by the number of expense category, correctly! \n");

    MenuFunctions::WaitForAction();
}

void Menu_Main::showSpendingOnIndividualExpenseCategory_Menu(User& user){

}

void Menu_Main::showSpendingsPercentageOnIndividualExpenseCategory_Menu(User& user){
     MenuFunctions::ClearTerminal();

    int counterColor = static_cast<int>(Color::Black);
    std::map<ExpenseCategory,double> map = user.percentageOfIndividualSpending();


     for(auto[key,value] : map){
        std::cout<<Transaction::returnExpenseCategoryInString(key) <<":\n[";

        for(int i = 0; i<int(value); i++){
            std::cout<<MenuFunctions::SetBackgroundColor(static_cast<Color>(counterColor), " ");
        }
        for(int i = 0; i<100-int(value); i++){
            std::cout<<MenuFunctions::SetBackgroundColor(Color::White, " ");
        }
        std::cout<<"]  ->" <<value<<"%\n\n";

     }

     MenuFunctions::WaitForAction();
}

void Menu_Main::modifyDateTransactionByID_Menu(User& user){

}

void Menu_Main::removeTransactionByID_Menu(User& user){

}

void Menu_Main::deleteAllTransactions_Menu(User& user){
     MenuFunctions::ClearTerminal();


    user.clearTransactions();
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
                //AddNewTransaction_Menu(User);
                std::cout<<"PODAJ MI TERAZ PLS DESCRIPTION, money, I NA CO ZOSTALO WYDANE ";
   
                std::getline( std::cin, description );
                std::getline( std::cin, description );
                std::cin>>money;
                std::cin>>expenseCatInINt;
                expenseCategory = static_cast<ExpenseCategory>(expenseCatInINt);
                User.addTransaction(std::make_shared<Transaction>(description,money,expenseCategory));
                break;
            case 2:
                SetCurrentMoney_Menu(User);
                // double moneySetted;
                // moneySetted = MenuFunctions::insertNumber(-9999,9999); 
                // User.setCurrentMoney(moneySetted);
                // MenuFunctions::WaitForAction();
                break;
            case 3:
                printAllTransactions_Menu(User);
                // std::cout<<User.printAllTransations();
                // MenuFunctions::WaitForAction();
                
                break;
            case 4:
                sortTransactionByDate_Menu(User);
                
                break;
            case 5:
                sortTransactionByNumberOfExpenseCategory_Menu(User);
                
                break;
            case 6:
                showSpendingOnIndividualExpenseCategory_Menu(User);
                
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