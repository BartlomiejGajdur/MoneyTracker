#include "../Include/Menu_LOG.hpp"


bool Menu_LOG::firstRun()
{   
    return ValidatePassword::getVecOfFileNameLoginPassword_().size() == 0 ? true : false;
}

void Menu_LOG::firstRunMenu(){
        if(firstRun())
        {
            std::cout<<"NAPOCZATKU MUSISZ SIE ZAREJESTROWAC BO NIE MASZ ZADNEGO KONTA HEHE:";
            std::cout<<"          REJESTRACJA\n\n";
            std::cout<<"PODAJ LOGIN:\n>";
            std::cin>>login;
            std::cout<<"PODAJ password:\n>";
            password = ValidatePassword::insertPassword();
            ValidatePassword::registerNewUser(login,password);
        }
       
}