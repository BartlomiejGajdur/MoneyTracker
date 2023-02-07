#pragma once
#include "ValidatePassword.hpp"
class Menu_LOG{
public:
    Menu_LOG(){ValidatePassword::loadConfigFromFile();};


    void run();
private:
    bool firstRun();
    void firstRunMenu();
    void optionsMenu();
    void RegisterMenu();
    bool LogINMenu();
    void printColoredRequirements(const std::string& password);
    void printPasswordRequirements();
};