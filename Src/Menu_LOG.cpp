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