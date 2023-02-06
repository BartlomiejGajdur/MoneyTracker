#pragma once
#include "ValidatePassword.hpp"

class Menu_LOG{
public:
    Menu_LOG(){ValidatePassword::loadConfigFromFile();};

    void firstRunMenu();
private:
    bool firstRun();
    void optionsMenu();

};