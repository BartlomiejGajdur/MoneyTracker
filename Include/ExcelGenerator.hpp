#include "xlsxwriter.h"

#include "User.hpp"
class ExcelGenerator{

    ExcelGenerator(const User& user) : user_(user) {};

    //Getters
    int getRow()    const {return row_;};
    int getColumn() const {return column_;};
    
    private:
    User user_;
    int row_{0}, column_{0};
};