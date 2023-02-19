#include "Include/Menu_Main.hpp"
#include "Include/ExcelGenerator.hpp"

int main(){

    Menu_Main Menu_Main;
    Menu_Main.run();

 
    // lxw_workbook  *workbook  = workbook_new("chart_line.xlsx");
    // lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
    // lxw_chart *chart;
    // lxw_chart_series *series;
 
    // /* Write some data for the chart. */
    // worksheet_write_number(worksheet, 0, 1, 10, NULL);
    // worksheet_write_number(worksheet, 1, 1, 40, NULL);
    // worksheet_write_number(worksheet, 2, 1, 50, NULL);
    // worksheet_write_number(worksheet, 3, 1, 20, NULL);
    // worksheet_write_number(worksheet, 4, 1, 10, NULL);
    // worksheet_write_number(worksheet, 5, 1, 50, NULL);
    // worksheet_write_number(worksheet, 6, 1, -20, NULL);

    // worksheet_write_string(worksheet, 0, 0, "adsadasdasda", NULL);
    // worksheet_write_string(worksheet, 1, 0, "bdasdas", NULL);
    // worksheet_write_string(worksheet, 2, 0, "cdsadas", NULL);
    // worksheet_write_string(worksheet, 3, 0, "dasdd", NULL);
    // worksheet_write_string(worksheet, 4, 0, "e", NULL);
    // worksheet_write_string(worksheet, 5, 0, "f", NULL);
    // worksheet_write_string(worksheet, 6, 0, "g", NULL);
 
    // /* Create a chart object. */
    // chart = workbook_add_chart(workbook, LXW_CHART_COLUMN_STACKED );
 
    // /* Configure the chart. */
    // series = chart_add_series(chart, "=Sheet1!$A$1:$A$7", "=Sheet1!$B$1:$B$7");
 
    // chart_legend_set_position(chart, LXW_CHART_LEGEND_NONE);
    // //(void)series; /* Do something with series in the real examples. */
    
    // /* Write the chart title with a font. */
    // chart_title_set_name(chart, "Summary of results");
 
    // /* Write the Y axis with a font. */
    // chart_axis_set_name(chart->y_axis, "[PLN]");

    // /* Write the X axis with a font. */
    // chart_axis_set_name(chart->x_axis, "Category");




    // /* Insert the chart into the worksheet. */
    // worksheet_insert_chart(worksheet, CELL("C1"), chart);
 
    // workbook_close(workbook);

    return 0;
}

