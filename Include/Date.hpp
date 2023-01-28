#pragma once
#include <ctime>
#include <ostream>
#include <string>
enum class DateErrorCode { Ok, InvalidYear, InvalidMonth, InvalidDay };

class Date{
public:
    Date() = default;
    Date(int day, int month, int year): day_(day) , month_(month), year_(year) {};

    //Setters  
    DateErrorCode setDate(int day, int month, int year); 

    //Getters
    int getDay()   const   { return day_;}
    int getMonth() const   { return month_;}
    int getYear()  const   { return year_ ;}

    //Functions
    static std::string currentData();
    static bool isLeapYear(int year);

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    std::string dateInString();

private:
    int day_{};
    int month_{};
    int year_{};

    bool isLeapYear();
    
};