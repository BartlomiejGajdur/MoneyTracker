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
            do{

            MenuFunctions::ClearTerminal();
            std::string login{},password{};
            std::cout<<"You don't have any active account!\n";
            std::cout<<"Create one to start :)\n";
            std::cout<<"Insert login:\n>";
            std::cin>>login;
            std::cout<<"Insert password:\n>";
            password = MenuFunctions::insertPassword();
            result = ValidatePassword::registerNewUser(login,password);
            if(result){
                std::cout<<"\nCongratulations " + login + " you created a new account! :)\n";
                MenuFunctions::WaitForAction();
            }else{
                std::cout<<"Something went wrong ;/ Try again.\n";
                MenuFunctions::WaitForAction();
            }
            }while(!result);
            
        }
       
}

void Menu_LOG::optionsMenu(){
   MenuFunctions::ClearTerminal();
   std::cout<<"1. Register\n";
   std::cout<<"2. LogIn\n";
   std::cout<<"0. Exit\n"; 
}

void Menu_LOG::RegisterMenu(){

        std::string login;
        std::string password;
        system("cls");
        std::cout<<"!!!Registration!!!\n\n";
        std::cout<<"Insert login:\n>";
        std::cin>>login;
        std::cout<<"Insert password:\n>";
        password = MenuFunctions::insertPassword();
        if(!ValidatePassword::registerNewUser(login,password)){
            std::cout<<"\nInserted login is already taken ;/\n";
            system("PAUSE");
        }   
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
            std::cout<<"Unfortunately, you entered incorrect data ;/\n";
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