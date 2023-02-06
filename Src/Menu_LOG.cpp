#include <string>

#include "../Include/Menu_LOG.hpp"
#include "../Include/MenuFunctions.hpp"
   


bool Menu_LOG::firstRun()
{   
    return ValidatePassword::getVecOfFileNameLoginPassword_().size() == 0 ? true : false;
}

void Menu_LOG::firstRunMenu(){
        if(firstRun())
        {   
            bool result;
            MenuFunctions::ClearTerminal();
            std::cout<<"You don't have any active account!\n";
            std::cout<<"Create one to start :)\n";
            MenuFunctions::WaitForAction();
            RegisterMenu();
            
        }
       
}

void Menu_LOG::optionsMenu(){
   MenuFunctions::ClearTerminal();
   std::cout<<"1. Register\n";
   std::cout<<"2. LogIn\n";
   std::cout<<"0. Exit\n"; 
}

void Menu_LOG::printColoredRequirements(const std::string& password){
    
    ValidatePassword::checkLength(password) == PasswordErrorCode::Ok ? std::cout<<"\n\x1B[32m*The password contains the appropriate number of characters\033[0m\n" : std::cout<<"\n\x1B[31m*The password does not contain the appropriate number of characters\033[0m\n";
    ValidatePassword::checkSpecialChar(password) == PasswordErrorCode::Ok ? std::cout<<"\x1B[32m*The password contains a special character\033[0m\n" : std::cout<<"\x1B[31m*The password does not contain a special character\033[0m\n";
    ValidatePassword::checkLowercaseLetter(password) == PasswordErrorCode::Ok ? std::cout<<"\x1B[32m*The password contains an lowercase letter\033[0m\n" : std::cout<<"\x1B[31m*The password does not contain an lowercase letter\033[0m\n";
    ValidatePassword::checkUppercaseLetter(password) == PasswordErrorCode::Ok ? std::cout<<"\x1B[32m*The password contains an uppercase letter\033[0m\n" : std::cout<<"\x1B[31m*The password does not contain an uppercase letter\033[0m\n";
    ValidatePassword::checkNumber(password) == PasswordErrorCode::Ok ? std::cout<<"\x1B[32m*The password contains a number\033[0m\n" : std::cout<<"\x1B[31m*The password does not contain a number\033[0m\n";
   
}

void Menu_LOG::RegisterMenu(){

        std::string login;
        std::string password;
        bool RegisterNewUserResult = false; 
        do{
        MenuFunctions::ClearTerminal();
        std::cout<<"!!!Registration!!!\n\n";
        std::cout<<"Insert login:\n>";
        std::cin>>login;

        
      

        
            MenuFunctions::ClearTerminal();
            std::cout<<"!!!Registration!!!\n\n";
            std::cout<<"Insert login:\n>";
            std::cout<<login;

            std::cout<<"\nInsert password:\n>";
            password = MenuFunctions::insertPassword();
            printColoredRequirements(password);

            if(ValidatePassword::checkGivenPassword(password)!= PasswordErrorCode::Ok){
                std::cout<<"\nInserted password does not meet the requirements ;/\n";
               MenuFunctions::WaitForAction();
            }else{
                RegisterNewUserResult = !ValidatePassword::registerNewUser(login,password);
                if(RegisterNewUserResult){
                    std::cout<<"\nInserted login is already taken ;/\n";
                   MenuFunctions::WaitForAction();
                }else{
                    std::cout<<"\nCongratulations, You registered a new account! :)\n";
                   MenuFunctions::WaitForAction();
                }
                
            }
        
        }while(ValidatePassword::checkGivenPassword(password)!= PasswordErrorCode::Ok || RegisterNewUserResult );


            
        
}

bool Menu_LOG::LogINMenu(){

        std::string login;
        std::string password;
        system("cls");
        std::cout<<"!!!LogIN!!!\n\n";
        std::cout<<"Insert login:\n>";
        std::cin>>login;
        std::cout<<"Insert password:\n>";
        password = MenuFunctions::insertPassword();
        if(ValidatePassword::logIn(login,password)){
            std::cout<<"\nYou have logged in correctly! Hello "<< login<<"!\n";
            system("PAUSE");
            return true;
        }else{
            std::cout<<"\nUnfortunately, you entered incorrect data ;/\n";
            system("PAUSE");
            return false;
        } 
}

void Menu_LOG::run(){

    firstRunMenu();

    
    int liczba=1;

    do{
        system("cls");
        optionsMenu();
        liczba  = MenuFunctions::insertNumber(0,2);
        switch (liczba)
        {
        case 1:
            RegisterMenu();
            break;

        case 2:
            if(LogINMenu())
            {
                liczba = 0;
            }
            break;

        case 0:
           ValidatePassword::getCurrentUser() = std::make_tuple("LogedOUT","LogedOUT","LogedOUT");
            break;
        default:
            break;
        }

    }while (liczba != 0);

}