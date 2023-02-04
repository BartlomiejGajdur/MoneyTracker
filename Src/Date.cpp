#include "../Include/Date.hpp"

#include <vector>
#include <iostream>
#include <sstream>

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



bool Date::isLeapYear(){
    return (year_ % 4 == 0 && year_ % 100 != 0) ||
           (year_ % 4 == 0 && year_ % 100 == 0 && year_ % 400 == 0);
}

bool Date::isLeapYear(int year){
    return (year % 4 == 0 && year % 100 != 0) ||
           (year % 4 == 0 && year % 100 == 0 && year % 400 == 0);
}

DateErrorCode Date::setDate(int day, int month, int year){
    
    if(year < 1800 || year > 2200)
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

Date Date::DateFromString(const std::string& dateInString){

    std::string a;
    std::istringstream extractFrom(dateInString);
    std::vector<std::string> vec;
    while(getline(extractFrom,a, '.'))
        {
            vec.push_back(a);
        }

    return Date{std::stoi(vec[0]),std::stoi(vec[1]),std::stoi(vec[2])};

}

int Date::distanceFromCurrentData(){
    Date currentDate = Date::currentData() ;
    int counter{0};
    while(*this > currentDate ){
        ++counter;
        ++currentDate;
    }

    return counter;
}

Date Date::operator=(const Date& otherDate){
    this->day_ = otherDate.day_;
    this->month_ = otherDate.month_;
    this->year_ = otherDate.year_;
    return *this;
}

bool Date::operator==(const Date& otherDate) const{
    return this->day_ == otherDate.day_ && 
           this->month_ == otherDate.month_ && 
           this->year_ == otherDate.year_;
}

bool Date::operator!=(const Date& otherDate) const{
    return this->day_ != otherDate.day_ || 
           this->month_ != otherDate.month_ || 
           this->year_ != otherDate.year_;
}

Date& Date::operator++(){
    DateErrorCode errorCode = this->setDate(++this->day_,this->month_,this->year_);

    if(errorCode == DateErrorCode::InvalidDay)
    {
        this->day_ = 1;
        errorCode = this->setDate(this->day_,++this->month_,this->year_);

        if(errorCode == DateErrorCode::InvalidMonth)
        {
            this->month_ = 1;
            ++this->year_;
        }
    }

    return *this;
} 

// Date Date::operator++(int){


// }

// Date& Date::operator--(){


// }

// Date Date::operator--(int){


// }

bool Date::operator<(const Date& other) const {
        if (year_ != other.year_) return year_ < other.year_;
        if (month_ != other.month_) return month_ < other.month_;
        return day_ < other.day_;
    }

bool Date::operator>(const Date& other) const{
    return other < *this;
  }
