#include "Include/Menu_Main.hpp"
#include "Include/ExcelGenerator.hpp"
int main(){

    ExcelGenerator excel{};

    Menu_Main Menu_Main;
    Menu_Main.run();

    return 0;
}

