#include "../Include/MenuFunctions.hpp"
#include "../Include/Menu_Main.hpp"

void Menu_Main::run(){
    MenuLOG.run();

    int liczba = 0;
        std::cout<<"Przed PETLA: " <<std::get<0>(ValidatePassword::getCurrentUser())<<"\n";
        std::cout<<"Przed PETLA: " <<std::get<1>(ValidatePassword::getCurrentUser())<<"\n";
        std::cout<<"Przed PETLA: " <<std::get<2>(ValidatePassword::getCurrentUser())<<"\n";
    while(std::get<0>(ValidatePassword::getCurrentUser()) != "LogedOUT" || liczba != 0){

        std::cout<<"W PETLI: " <<std::get<0>(ValidatePassword::getCurrentUser())<<"\n";
        std::cout<<"W PETLI: " <<std::get<1>(ValidatePassword::getCurrentUser())<<"\n";
        std::cout<<"W PETLI: " <<std::get<2>(ValidatePassword::getCurrentUser())<<"\n";


        MenuFunctions::WaitForAction();

    }

}