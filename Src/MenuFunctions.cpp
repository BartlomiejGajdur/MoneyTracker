#include <string>
#include <iostream>
#include <conio.h>

#include "../Include/MenuFunctions.hpp"
#include "bcrypt.h"


void MenuFunctions::ClearTerminal(){
    system("cls");
}

void MenuFunctions::WaitForAction(){
    system("PAUSE");
}

std::string MenuFunctions::insertPassword(){
        std::string password{};
        char ch;

        do{
            ch = _getch();
            if(ch == 8)
            {
                if(password.size()>0)
                {
                    std::cout<<"\b \b";
                    password.pop_back();
                }
                
            }else if(ch == 13){

            }
            else{
                std::cout<<"*";
                password+=ch;
            }

        }while(ch != 13);

        return password;
    }