#pragma once
#include <string>

#include "User.hpp"
#include "xlsxwriter.h"

class ExcelGenerator {
public:
    ExcelGenerator(const User& user)
        : user_(user){};
    ExcelGenerator(){};

    //Getters
    int getRow() const { return row_; };
    int getColumn() const { return column_; };
    User getUser() const { return user_; };
    //Functions
    void greetUser_Excel();
    void CurrentMoney_Excel();
    void Transactions_Excel();
    void SummaryTable_Excel();
    void PieChart_Excel(const std::map<ExpenseCategory, double>& map, const std::string& ChartTitle);
    void updateTransactions(const User& user) { user_ = user; };
    void open_Excel(const std::string& ExcelName, const std::string& SheetName);
    lxw_error close_Excel();

private:
    User user_;
    int row_{0}, column_{0};
    std::string ExcelName_{"Report001.xlsx"}, SheetName_{"Sheet1"};
    lxw_workbook* workbook_;
    lxw_worksheet* worksheet_;

    std::string generateSeriesRange(const int firstRow, const int Column, const int secondRow);
};