#pragma once
#include <iostream>
#include <string>
#include <vector>

enum class Color {Black = 30, Red, Green, Yellow, Blue, Magenta, Cyan, White,
                  Bright_Black = 90, Bright_Red, Bright_Green, Bright_Yellow, Bright_Blue, 
                  Bright_Magenta, Bright_Cyan, Bright_White};

namespace MenuFunctions{
    void ClearTerminal();
    void WaitForAction();
    std::string insertPassword();
    int insertNumber();
    std::string SetTextColor(const Color& color, const std::string& text);
    std::string SetBackgroundColor(const Color& color, const std::string& text);
    std::string SetBoldText(const std::string& text);
    std::string SetBoldText(const bool& text);
    int arrowMenu(const std::vector<std::string>& Options);
    int arrowMenu(std::vector<std::pair<std::string,bool>> Options);

    template<typename Type>
    Type insertNumber(const Type& zakresL, const Type& zakresP){
        Type choice;
        std::cout<<"Insert number in range: "<<zakresL <<  " to " <<zakresP<<"\n>";
        while(!(std::cin>>choice) || choice<zakresL || choice >zakresP){
            std::cout<<"Please enter number only in range: "<<zakresL <<  " to " <<zakresP<<"\n>";
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        }

        return choice;
    }

}