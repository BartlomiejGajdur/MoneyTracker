#pragma once
#include <ctime>
#include <ostream>
#include <string>



enum class DateErrorCode { Ok, InvalidYear, InvalidMonth, InvalidDay, ERROR404};


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
    static std::string currentDataInString();
    static Date currentData();
    static Date DateFromString(const std::string& dateInString);
    static bool isLeapYear(int year);

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    Date operator=(const Date& otherDate);
    bool operator==(const Date& otherDate) const;
    bool operator!=(const Date& otherDate) const;
    Date& operator++(); //Prefix
    // Date operator++(int); // Postfix
    // Date& operator--(); //Prefix
    // Date operator--(int); // Postfix


    std::string dateInString();

private:
    int day_{};
    int month_{};
    int year_{};

    bool isLeapYear();
    
};