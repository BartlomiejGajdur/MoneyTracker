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

size_t  MenuFunctions::insertNumber(const size_t& zakresL, const size_t& zakresP){
    size_t choice;
    std::cout<<"Insert number in range: "<<zakresL <<  " to " <<zakresP<<"\n>";
    while(!(std::cin>>choice) || choice<zakresL || choice >zakresP){
        std::cout<<"Please enter number only in range: "<<zakresL <<  " to " <<zakresP<<"\n>";
        std::cin.clear();
        std::cin.ignore(1000,'\n');
    }

    return choice;
}

std::string MenuFunctions::SetTextColor(const Color& color, const std::string& text){
    return "\x1B["+ std::to_string(static_cast<int>(color))+"m" + text+"\033[0m";
}

std::string MenuFunctions::SetBackgroundColor(const Color& color, const std::string& text){
    return "\x1B["+ std::to_string(static_cast<int>(color)+10)+"m" + text+"\033[0m";
}