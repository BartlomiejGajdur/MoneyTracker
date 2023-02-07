#include "../Include/MenuFunctions.hpp"
#include "../Include/Menu_Main.hpp"
#include "../Include/User.hpp"

void Menu_Main::greetUser(const User& User){
    system("CLS");
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
    std::cout <<"| > 0.   EXIT                                                                |\n";
    std::cout <<"+----------------------------------------------------------------------------+\n";
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
                std::cout<<"PODAJ MI TERAZ PLS DESCRIPTION, money, I NA CO ZOSTALO WYDANE ";
   
                std::getline( std::cin, description );
                std::getline( std::cin, description );
                std::cin>>money;
                std::cin>>expenseCatInINt;
                expenseCategory = static_cast<ExpenseCategory>(expenseCatInINt);
                User.addTransaction(std::make_shared<Transaction>(description,money,expenseCategory));
                break;
            case 2:
                double moneySetted;
                moneySetted = MenuFunctions::insertNumber(-9999,9999); 
                User.setCurrentMoney(moneySetted);
                MenuFunctions::WaitForAction();
                break;
            case 3:
                std::cout<<User.printAllTransations();
                MenuFunctions::WaitForAction();
                
                break;
            case 4:
                
                
                break;
            case 5:
                
                
                break;
            case 6:
                
                
                break;
            case 7:
                
                
                break;
            case 8:
                
                
                break;
            case 9:
                
                
                break;
            case 10:
                
                
                break;
            case 0:
                
                
                break;
            default:
                break;
            }
        }while(liczba != 0);


        MenuFunctions::WaitForAction();

    }

}