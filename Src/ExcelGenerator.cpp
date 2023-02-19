#include "../Include/ExcelGenerator.hpp"
#include <iostream>
#include <cmath>
void ExcelGenerator::greetUser_Excel(){

    std::string greetText = "Hello " + user_.getLogin() + "!";

    lxw_format *merge_format = workbook_add_format(workbook_);

    format_set_font_size(merge_format, 24);
    format_set_align   (merge_format, LXW_ALIGN_CENTER);
    format_set_align   (merge_format, LXW_ALIGN_VERTICAL_CENTER);
    format_set_border  (merge_format, LXW_BORDER_DOUBLE);
    format_set_bold    (merge_format);
    format_set_bg_color(merge_format, 0x95B3D7);    

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
    format_set_bg_color(format, 0xB8CCE4); 
    
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

std::string ExcelGenerator::generateSeriesRange(const int firstRow, const int Column, const int secondRow){

    std::string columnInLetters;
    columnInLetters.push_back(char(Column + 65));

    std::string result = "=" + SheetName_ + "!$" + columnInLetters + "$" + std::to_string(firstRow) + ":$" +columnInLetters + "$" + std::to_string(secondRow);

    return result.c_str();
}

void ExcelGenerator::PieChart_Excel(const std::map<ExpenseCategory, double>& map, const std::string& ChartTitle){
    
    lxw_chart_series *series;
    
    for(auto [key,value] :map){

        
        value*=100;
        value = ceil(value);
        value/=100;
           worksheet_write_string(worksheet_, row_, column_, Transaction::returnExpenseCategoryInString(key).c_str(), NULL);
           worksheet_write_number(worksheet_, row_, column_+1, value,     NULL);
        ++row_;
    }
 
    /* Create a pie chart. */
    lxw_chart *chart = workbook_add_chart(workbook_, LXW_CHART_PIE);

    /* Add the data series to the chart. */
    series = chart_add_series(chart, generateSeriesRange(row_ - map.size()+1, column_, row_).c_str(),
                                     generateSeriesRange(row_ - map.size()+1, column_+1, row_).c_str());

    chart_series_set_labels(series);
 
    lxw_chart_point *points[] = {NULL};
 
    /* Add the points to the series. */
    chart_series_set_points(series, points);

    /*Percentage and title*/
    chart_series_set_labels(series);
    chart_series_set_labels_options(series, LXW_FALSE, LXW_FALSE, LXW_FALSE);
    chart_series_set_labels_percentage(series);
    chart_title_set_name(chart, ChartTitle.c_str());
 
    /* Insert the chart into the worksheet. */
    worksheet_insert_chart(worksheet_,row_ - map.size(),column_ , chart);

    row_ = row_ - map.size() + 15;
    column_ = 0;

}


void  ExcelGenerator::SummaryTable_Excel(){
    
        std::map<ExpenseCategory,double> spendings = user_.countIndividualSpending();
        std::map<ExpenseCategory,double> earnings = user_.countIndividualEarning();

        lxw_table_column col1 = {.header         = const_cast<char*>("Spendings Category")};
        lxw_table_column col2 = {.header         = const_cast<char*>("Money Spend [PLN]")};

        lxw_table_column col3 = {.header         = const_cast<char*>("Earnings Category")};
        lxw_table_column col4 = {.header         = const_cast<char*>("Money Earn [PLN]")};
        
        lxw_table_column *columns1[] = {&col1, &col2, NULL};
        lxw_table_column *columns2[] = {&col3, &col4, NULL};
        
        lxw_table_options options1 = {.columns = columns1};
        lxw_table_options options2 = {.columns = columns2};

        worksheet_set_column(worksheet_, column_, column_, 19, NULL);
        worksheet_set_column(worksheet_, column_+1, column_+1, 19, NULL);
        worksheet_set_column(worksheet_, column_+2, column_+2, 18, NULL);
        worksheet_set_column(worksheet_, column_+3, column_+3, 18, NULL);

       
        worksheet_add_table(worksheet_, row_, column_, row_ + spendings.size(), column_+1, &options1) ;


        worksheet_add_table(worksheet_, row_, column_+2, row_ + earnings.size(), column_+3, &options2) ;

        

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


        row_++;
        for(const auto& [key,value] : spendings)
        {   
            
            //EXPENSE CATEGORY
            worksheet_write_string(worksheet_, row_, column_, Transaction::returnExpenseCategoryInString(key).c_str(), format);

             if(value >= 0)
            {   
                format_set_font_color(formatG, LXW_COLOR_GREEN);
                worksheet_write_number(worksheet_, row_, column_+1, value , formatG);
            }else
            {
                format_set_font_color(formatR, LXW_COLOR_RED);
                worksheet_write_number(worksheet_, row_, column_+1, value , formatR);
            }

            //INC row_ index
            ++row_;
        }
        lxw_format *formatTotal = workbook_add_format(workbook_);
        format_set_border  (formatTotal, LXW_BORDER_THIN);
        format_set_bold(formatTotal);
        format_set_font_size(formatTotal, 12);
        format_set_align   (formatTotal, LXW_ALIGN_CENTER);
        format_set_align   (formatTotal, LXW_ALIGN_VERTICAL_CENTER);
        format_set_bg_color(formatTotal, 0x95B3D7); 

        worksheet_write_string(worksheet_, row_, column_, "Total Spending: ", formatTotal);

        format_set_font_color(formatTotal, LXW_COLOR_RED);
        worksheet_write_number(worksheet_, row_, column_+1, user_.countWholeSpendings() , formatTotal);

        
        row_ = row_ - spendings.size();

        for(const auto& [key,value] : earnings)
        {   
            
            //EXPENSE CATEGORY
            worksheet_write_string(worksheet_, row_, column_+2, Transaction::returnExpenseCategoryInString(key).c_str(), format);

             if(value >= 0)
            {   
                format_set_font_color(formatG, LXW_COLOR_GREEN);
                worksheet_write_number(worksheet_, row_, column_+3, value , formatG);
            }else
            {
                format_set_font_color(formatR, LXW_COLOR_RED);
                worksheet_write_number(worksheet_, row_, column_+3, value , formatR);
            }

            //INC row_ index
            ++row_;
        }
        lxw_format *formatTotalEarning = workbook_add_format(workbook_);
        format_set_border  (formatTotalEarning, LXW_BORDER_THIN);
        format_set_bold(formatTotalEarning);
        format_set_font_size(formatTotalEarning, 12);
        format_set_align   (formatTotalEarning, LXW_ALIGN_CENTER);
        format_set_align   (formatTotalEarning, LXW_ALIGN_VERTICAL_CENTER);
        format_set_bg_color(formatTotalEarning, 0x95B3D7); 
        worksheet_write_string(worksheet_, row_, column_+2, "Total Earning: ", formatTotalEarning);

        format_set_font_color(formatTotalEarning, LXW_COLOR_GREEN);
        worksheet_write_number(worksheet_, row_, column_+3, user_.countWholeEarnings() , formatTotalEarning);

        row_= row_ - earnings.size();
        spendings.size() > earnings.size() ? row_+=spendings.size() : row_+= earnings.size();
        row_++;
    
}


void ExcelGenerator::open_Excel(const std::string& ExcelName, const std::string& SheetName){
    ExcelName_ = ExcelName;
    SheetName_ = SheetName;

    workbook_  = workbook_new(ExcelName_.c_str());
    worksheet_ = workbook_add_worksheet(workbook_, SheetName_.c_str());

    row_ = 0;
    column_ = 0;
}

lxw_error ExcelGenerator::close_Excel(){
    return workbook_close(workbook_);
}