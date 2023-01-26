
#include <string>
#include <ctime>
enum class DateErrorCode { Ok, InvalidYear, InvalidMonth, InvalidDay };

class Date{
public:
    Date() = default;
    Date(int day, int month, int year): day_(day) , month_(month), year_(year) {};

    //Setters  
    DateErrorCode setDate(int day, int month, int year); 
    // void setDay(int day)        { day_ = day;}
    // void setMonth(int month)    { month_ = month;}
    // void setYear(int year)      { year_ = year;}

    //Getters
    int getDay()   const   { return day_;}
    int getMonth() const   { return month_;}
    int getYear()  const   { return year_ ;}

    //Functions
    static std::string currentData();
    

private:
    int day_{};
    int month_{};
    int year_{};

    bool isLeapYear();
};