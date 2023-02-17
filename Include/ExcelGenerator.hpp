#include "xlsxwriter.h"

#include "User.hpp"
class ExcelGenerator{
public:
    ExcelGenerator(const User& user) : user_(user) {};
    ExcelGenerator() {};

    //Getters
    int getRow()    const {return row_;};
    int getColumn() const {return column_;};

    
    void greetUser_Excel();
    void CurrentMoney_Excel();
    void Transactions_Excel();
    void open_Excel(const std::string& Name_excel, const std::string& Name_Sheet);
    void close_Excel();
    void updateTransactions(const User& user) {user_ = user;};

private:
    User user_;
    int row_{0}, column_{0};
    lxw_workbook  *workbook_;
    lxw_worksheet *worksheet_;
};