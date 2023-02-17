#include "xlsxwriter.h"

#include "User.hpp"
class ExcelGenerator{
public:
    ExcelGenerator(const User& user) : user_(user) {};
    ExcelGenerator() {};

    //Getters
    int getRow()    const {return row_;};
    int getColumn() const {return column_;};

    //Take User name and Greet him
    void greetUser_Excel();
    void CurrentMoney_Excel();
    void close_Excel();

private:
    User user_;
    int row_{0}, column_{0};
    lxw_workbook  *workbook_  = workbook_new("TEST.xlsx");
    lxw_worksheet *worksheet_ = workbook_add_worksheet(workbook_, "TEST_KARTKA_1");
};