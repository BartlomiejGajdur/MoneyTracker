#include "../Include/ExcelGenerator.hpp"
#include <iostream>
void ExcelGenerator::greetUser_Excel(){

    std::string greetText = "Hello " + user_.getLogin() + "!";

    lxw_format *merge_format = workbook_add_format(workbook_);

    format_set_font_size(merge_format, 24);
    format_set_align   (merge_format, LXW_ALIGN_CENTER);
    format_set_align   (merge_format, LXW_ALIGN_VERTICAL_CENTER);
    format_set_border  (merge_format, LXW_BORDER_DOUBLE);
    format_set_bold    (merge_format);
    format_set_bg_color(merge_format, 0xD7E4BC);    

    int size = 4;

    worksheet_merge_range(worksheet_, row_, column_, row_+size, column_+size,greetText.c_str(), merge_format);

    //Set Row and Column Index To next free row of cells
    ++row_+=size;
    column_ = 0;    
}

void ExcelGenerator::CurrentMoney_Excel(){
    lxw_format *format = workbook_add_format(workbook_);

    format_set_bold(format);
    format_set_font_size(format, 12);
    format_set_align   (format, LXW_ALIGN_CENTER);
    format_set_align   (format, LXW_ALIGN_VERTICAL_CENTER);
    format_set_border  (format, LXW_BORDER_DOUBLE);
    format_set_bold    (format);
    format_set_bg_color(format, 0xD7E4BC); 
    
    worksheet_merge_range(worksheet_, row_, column_, row_+2, column_ +4," ", format);

   
    std::string toDisplay;
    std::string money = std::to_string(user_.getCurrentMoney());
    money.erase(money.length()-4,money.length());
    money+=" PLN\n";
    toDisplay = "Current money: " + money;

    if(user_.getCurrentMoney() >= 0)
    {   
        format_set_font_color(format, LXW_COLOR_GREEN);
        worksheet_write_string(worksheet_,row_,0, toDisplay.c_str(), format);
    }else
    {
        format_set_font_color(format, LXW_COLOR_RED);
        worksheet_write_string(worksheet_,row_,0, toDisplay.c_str(), format);
    }

    //Set Row and Column Index To next free row of cells
    ++row_+=2;
    column_ = 0;
}

void ExcelGenerator::Transactions_Excel(){
    vecTransactionPtr transactions = user_.getTransactions();
    std::string money;

    if(transactions.size() > 0)
    { 
        worksheet_set_column(worksheet_, column_, column_, 5, NULL);
        worksheet_set_column(worksheet_, column_+1, column_+1, 16, NULL);
        worksheet_set_column(worksheet_, column_+2, column_+2, 12, NULL);
        worksheet_set_column(worksheet_, column_+3, column_+3, 17, NULL);
        worksheet_set_column(worksheet_, column_+4, column_+4, 15, NULL);

        lxw_table_column col1 = {.header         = const_cast<char*>("ID")};
        lxw_table_column col2 = {.header         = const_cast<char*>("Description")};
        lxw_table_column col3 = {.header         = const_cast<char*>("Money")};
        lxw_table_column col4 = {.header         = const_cast<char*>("Expense Category")};
        lxw_table_column col5 = {.header         = const_cast<char*>("Date")};
        
        lxw_table_column *columns[] = {&col1, &col2, &col3, &col4, &col5, NULL};
        
        lxw_table_options options = {.columns = columns};
 
        worksheet_add_table(worksheet_, row_, column_, row_ + transactions.size(), column_+4, &options);

        row_++;

        lxw_format *format = workbook_add_format(workbook_);
        format_set_align   (format, LXW_ALIGN_CENTER);
        format_set_align   (format, LXW_ALIGN_VERTICAL_CENTER);

        lxw_format *formatG = workbook_add_format(workbook_);
        format_set_align   (formatG, LXW_ALIGN_CENTER);
        format_set_align   (formatG, LXW_ALIGN_VERTICAL_CENTER);
        format_set_bold(formatG);

        lxw_format *formatR = workbook_add_format(workbook_);
        format_set_align   (formatR, LXW_ALIGN_CENTER);
        format_set_align   (formatR, LXW_ALIGN_VERTICAL_CENTER);
        format_set_bold(formatR);

        for(const auto& v : transactions)
        {   
            
            //ID
            worksheet_write_number(worksheet_, row_, column_, v->getID(),  format);

            //DESCRIPTION
            worksheet_write_string(worksheet_, row_, column_+1, v->getDescription().c_str(),   format);
            
            //MONEY
            money = std::to_string(v->getMoney());
            money.erase(money.length()-4,money.length());
            money+=" PLN";
             if(v->getMoney() >= 0)
            {   
                format_set_font_color(formatG, LXW_COLOR_GREEN);
                worksheet_write_string(worksheet_, row_, column_+2, money.c_str() , formatG);
            }else
            {
                format_set_font_color(formatR, LXW_COLOR_RED);
                worksheet_write_string(worksheet_, row_, column_+2, money.c_str() , formatR);
            }

            //EXPENSE CATEGORY
            worksheet_write_string(worksheet_, row_, column_+3, Transaction::returnExpenseCategoryInString(v->getExpenseCategory()).c_str(), format);

            //ENTERTANMENT
            worksheet_write_string(worksheet_, row_, column_+4, v->getDate().dateInString().c_str(), format);

            //INC row_ index
            ++row_;
        }
    }
}

void ExcelGenerator::open_Excel(const std::string& Name_excel, const std::string& Name_Sheet){
    workbook_  = workbook_new(Name_excel.c_str());
    worksheet_ = workbook_add_worksheet(workbook_, Name_Sheet.c_str());

    row_ = 0;
    column_ = 0;
}

void ExcelGenerator::close_Excel(){
    workbook_close(workbook_);
}