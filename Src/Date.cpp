#include "../Include/Date.hpp"

std::string Date::currentData(){

    time_t t = time(nullptr);
    tm* timePtr = localtime(&t);
 
    return std::to_string(timePtr->tm_mday) + "-" +
           std::to_string(1+timePtr->tm_mon) + "-" + 
           std::to_string(1900+ timePtr->tm_year); 
}

bool Date::isLeapYear(){
    return (year_ % 4 == 0 && year_ % 100 != 0) ||
           (year_ % 4 == 0 && year_ % 100 == 0 && year_ % 400 == 0);
}

DateErrorCode Date::setDate(int day, int month, int year){
    if(year < 1900 || year > 2023)
        return DateErrorCode::InvalidYear;
    year_ = year;

    if(month < 0 || month > 12)
        return DateErrorCode::InvalidMonth;
    month_ = month;
    
    
}