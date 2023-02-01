#include "../Include/Date.hpp"

#include <iostream>

std::string Date::currentDataInString(){

    time_t t = time(nullptr);
    tm* timePtr = localtime(&t);
 
    return std::to_string(timePtr->tm_mday) + "-" +
           std::to_string(1+timePtr->tm_mon) + "-" + 
           std::to_string(1900+ timePtr->tm_year); 
}

Date Date::currentData(){

    time_t t = time(nullptr);
    tm* timePtr = localtime(&t);
 
    return Date(timePtr->tm_mday,1+timePtr->tm_mon,1900+ timePtr->tm_year);
}

Date Date::operator=(const Date& date){
    this->day_ = date.day_;
    this->month_ = date.month_;
    this->year_ = date.year_;
    return *this;
}

bool Date::isLeapYear(){
    return (year_ % 4 == 0 && year_ % 100 != 0) ||
           (year_ % 4 == 0 && year_ % 100 == 0 && year_ % 400 == 0);
}

bool Date::isLeapYear(int year){
    return (year % 4 == 0 && year % 100 != 0) ||
           (year % 4 == 0 && year % 100 == 0 && year % 400 == 0);
}

DateErrorCode Date::setDate(int day, int month, int year){
    
    if(year < 1900 || year > 2023)
        return DateErrorCode::InvalidYear;
    
   

    if(month < 1 || month > 12)
        return DateErrorCode::InvalidMonth;
    
    
    if( 
        ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <=31 && day >=0) ||
        ((month == 4 || month == 6 || month == 9 || month == 11) && day <=30 && day >=0) ||
        (month == 2 && this->isLeapYear(year) && day <=29 && day >=0) ||
        (month == 2 && !this->isLeapYear(year) && day <=28 && day >=0))
        {
            this->month_ = month;
            this->year_ = year;
            this->day_ = day;
            return DateErrorCode::Ok;
        }
        return DateErrorCode::InvalidDay;
            
}

std::ostream& operator<<(std::ostream& os, const Date& date){
    return os<<date.day_<<"."<<date.month_<<"."<<date.year_;
}

std::string Date::dateInString(){
    return std::to_string(this->day_) + "." + std::to_string(this->month_) + "." + std::to_string(this->year_);
}