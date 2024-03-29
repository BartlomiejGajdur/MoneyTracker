#pragma once
#include <ctime>
#include <ostream>
#include <string>

enum class DateErrorCode { Ok,
                           InvalidYear,
                           InvalidMonth,
                           InvalidDay,
                           ERROR404 };

class Date {
public:
    Date() = default;
    Date(int day, int month, int year)
        : day_(day), month_(month), year_(year){};

    //Setters
    DateErrorCode setDate(int day, int month, int year);

    //Getters
    int getDay() const { return day_; }
    int getMonth() const { return month_; }
    int getYear() const { return year_; }

    //Functions
    std::string dateInString() const;
    int distanceFromCurrentData();
    static std::string currentDataInString();
    static Date currentData();
    static Date DateFromString(const std::string& dateInString);
    static bool isLeapYear(int year);
    static int distance(const Date& lhsDATE, const Date& rhsDATE);

    //Operators
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    Date operator=(const Date& otherDate);
    bool operator==(const Date& otherDate) const;
    bool operator!=(const Date& otherDate) const;
    Date& operator++();  //Prefix
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;

private:
    int day_{};
    int month_{};
    int year_{};

    bool isLeapYear();
};