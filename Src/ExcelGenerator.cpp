#include "../Include/ExcelGenerator.hpp"

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

void ExcelGenerator::close_Excel(){
    workbook_close(workbook_);
}