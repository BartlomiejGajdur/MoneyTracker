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

    if( 
        ((month_ == 1 || month_ == 3 || month_ == 5 || month_ == 7 || month_ == 8 || month_ == 10 || month_ == 12) && day <=31 && day >=0) ||
        ((month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) && day <=30 && day >=0) ||
        (month_ == 2 && this->isLeapYear() && day <=29 && day >=0) ||
        (month_ == 2 && !this->isLeapYear() && day <=28 && day >=0))
        {
            day_ = day;
            return DateErrorCode::Ok;
        }
        return DateErrorCode::InvalidDay;
            
}