#include "ValidatePassword.hpp"

class Menu_LOG{
public:
    Menu_Log(){ValidatePassword::loadConfigFromFile();};
    
private:
    bool firstRun();
    void firstRunMenu();

};