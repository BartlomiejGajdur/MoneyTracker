
#include <string>
#include <ctime>
enum class DateErrorCode { Ok, InvalidCode };

class Date{
public:
    Date() = default;
    Date(int day, int month, int year): day_(day) , month_(month), year_(year) {};

    //Setters   
    void setDay(int day)        { day_ = day;}
    void setMonth(int month)    { month_ = month;}
    void setYear(int year)      { year_ = year;}

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
};