#include "Menu_LOG.hpp"
#include "User.hpp"

class Menu_Main{
public:
    void run();

private:
    Menu_LOG MenuLOG;

    void printOptions();
    void greetUser(const User& user);

};