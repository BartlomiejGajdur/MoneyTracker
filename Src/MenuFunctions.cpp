#include <string>
#include <iostream>
#include <conio.h>
#include <vector>

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

int MenuFunctions::insertNumber(){
    int choice;
    while(!(std::cin>>choice)){
        std::cout<<"Please enter numbers only: \n>";
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

std::string MenuFunctions::SetBoldText(const std::string& text){
    return "\e[1m" + text + "\e[0m";
}

//Options Menu should be formatted in a way that 0.EXit is the last string in vector Options
int MenuFunctions::arrowMenu(const std::vector<std::string>& Options){
    
    int counter = 1;
    char znak;
    bool exit = false;
    int vecSize = Options.size();

    while(!exit)
    {
        
        MenuFunctions::ClearTerminal();
        std::cout<<"+-------------------+\n";
        std::cout<<"|     W -> UP       |\n"; 
        std::cout<<"|     S -> DOWN     |\n"; 
        std::cout<<"| ENTER -> APPROVAL |\n";
        std::cout<<"+-------------------+\n\n"; 
        for (int i = 0; i < vecSize ; i++)
        {
            if(i+1 == counter){
                std::cout<<"--> "<<MenuFunctions::SetBoldText(Options[i])<<"\n";
            }else{
                std::cout<<Options[i]<<"\n";
            }
            
        }
        znak = _getch();

        if(znak == 'W' || znak =='w')
        {
            if(counter == 1){

            }else{
                --counter;
            }
        }

        if(znak == 'S' || znak == 's')
        {
            if(counter == vecSize){

            }else{
                ++counter;
            }
        }

        if(znak == 13)
        {
            exit = true;
        }

        if(znak == 13 && counter == vecSize)
        {
            counter = 0;
            exit = true;
        }

    }

    return counter;
}