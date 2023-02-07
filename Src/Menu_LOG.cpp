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

void Menu_LOG::printPasswordRequirements(){
    std::cout<<"+-------------------------------------------------------+\n";
    std::cout<<"|Password should have 8 to 32 characters long!          |\n";
    std::cout<<"|Password should have at least one special char!        |\n";
    std::cout<<"|Password should have at least one lowercase letter!    |\n";
    std::cout<<"|Password should have at least one uppercase letter!    |\n";
    std::cout<<"|Password should have at least one number!              |\n";
    std::cout<<"+-------------------------------------------------------+\n";
}

void Menu_LOG::printColoredRequirements(const std::string& password){
    
    ValidatePassword::checkLength(password) == PasswordErrorCode::Ok ? std::cout<<"\n\x1B[32m*The password contains the appropriate number of characters\033[0m\n" : std::cout<<"\n\x1B[31m*The password does not contain the appropriate number of characters\033[0m\n";
    ValidatePassword::checkSpecialChar(password) == PasswordErrorCode::Ok ? std::cout<<"\x1B[32m*The password contains a special character\033[0m\n" : std::cout<<"\x1B[31m*The password does not contain a special character\033[0m\n";
    ValidatePassword::checkLowercaseLetter(password) == PasswordErrorCode::Ok ? std::cout<<"\x1B[32m*The password contains an lowercase letter\033[0m\n" : std::cout<<"\x1B[31m*The password does not contain an lowercase letter\033[0m\n";
    ValidatePassword::checkUppercaseLetter(password) == PasswordErrorCode::Ok ? std::cout<<"\x1B[32m*The password contains an uppercase letter\033[0m\n" : std::cout<<"\x1B[31m*The password does not contain an uppercase letter\033[0m\n";
    ValidatePassword::checkNumber(password) == PasswordErrorCode::Ok ? std::cout<<"\x1B[32m*The password contains a number\033[0m\n" : std::cout<<"\x1B[31m*The password does not contain a number\033[0m\n";
   
}

void Menu_LOG::RegisterMenu(){

        int choice;
        std::string login;
        std::string password, passwordToMatch;

        bool RegisterNewUserResult = false; 
        do{
        MenuFunctions::ClearTerminal();
        std::cout<<"                  Registration\n\n";
        printPasswordRequirements();
        std::cout<<"Insert login:\n>";
        std::cin>>login;
        std::cout<<"Insert password:\n>";
        password = MenuFunctions::insertPassword();
        std::cout<<"\nConfirm Password:\n>";
        passwordToMatch =  MenuFunctions::insertPassword();
        printColoredRequirements(password);

            if(ValidatePassword::checkGivenPassword(password)!= PasswordErrorCode::Ok){
                std::cout<< MenuFunctions::SetTextColor(Color::Red,"\nInserted password does not meet the requirements ;/\n");
                std::cout<<"Do you want to try again?\n";
                std::cout<<"1. Yes\n";
                std::cout<<"2. No\n>";
                choice = MenuFunctions::insertNumber(1,2);

            }else if (ValidatePassword::checkPasswordMatch(password,passwordToMatch) != PasswordErrorCode::Ok ){
                std::cout<< MenuFunctions::SetTextColor(Color::Red,"\nConfirmed Password doesn't match with the first one!\n");
                std::cout<<"Do you want to try again?\n";
                    std::cout<<"1. Yes\n";
                    std::cout<<"2. No\n>";
                    choice = MenuFunctions::insertNumber(1,2);

            }else{
                RegisterNewUserResult = !ValidatePassword::registerNewUser(login,password);
                if(RegisterNewUserResult){
                    std::cout<< MenuFunctions::SetTextColor(Color::Red,"\nInserted login is already taken ;/\n");
                    std::cout<<"Do you want to try again?\n";
                    std::cout<<"1. Yes\n";
                    std::cout<<"2. No\n>";
                    choice = MenuFunctions::insertNumber(1,2);
                }else{
                    std::cout<<"\nCongratulations, You registered a new account! :)\n";
                    choice = 0;
                   MenuFunctions::WaitForAction();
                }
                
            }
        
        }while(choice == 1);


            
        
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