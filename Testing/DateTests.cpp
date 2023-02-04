#include "gtest/gtest.h"

#include <functional>
#include <vector>

#include "../Include/Date.hpp"

using setDateResponse = std::pair<DateErrorCode,DateErrorCode>;
Date data(30,4,2000);

std::vector<setDateResponse> setDateWithResponse = {
    {data.setDate(1,1,1),DateErrorCode::InvalidYear},
    {data.setDate(1,1,-5),DateErrorCode::InvalidYear},
    {data.setDate(1,1,2201),DateErrorCode::InvalidYear},
    {data.setDate(1,1,1799),DateErrorCode::InvalidYear},
    {data.setDate(1,13,1901),DateErrorCode::InvalidMonth},
    {data.setDate(1,0,1901),DateErrorCode::InvalidMonth},
    {data.setDate(32,2,1904),DateErrorCode::InvalidDay},
    {data.setDate(32,12,1901),DateErrorCode::InvalidDay},
    {data.setDate(29,2,1900),DateErrorCode::InvalidDay},
    {data.setDate(29,2,1904),DateErrorCode::Ok},
    {data.setDate(3,12,2000),DateErrorCode::Ok},
    {data.setDate(31,12,2000),DateErrorCode::Ok},
    {data.setDate(30,4,2000),DateErrorCode::Ok},
};

class CheckData : public testing::TestWithParam<setDateResponse>
{
};

TEST_P(CheckData, ValidateData)
{
    auto [DataToCheck, Response] = GetParam();

    ASSERT_EQ(static_cast<int>(DataToCheck), static_cast<int>(Response));
}

INSTANTIATE_TEST_SUITE_P(Date,
                         CheckData,
                         testing::ValuesIn(setDateWithResponse));

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

using LeapYearResponce = std::pair<int,bool>;

std::vector<LeapYearResponce> LeapYearWithResponse = {
    {2000, true},
    {2100, false},
    {2200, false},
    {2300, false},
    {2400, true},
    {2004, true},
    {2008, true},
    {1900, false},
    {1873, false},
    {2033, false},
};

class CheckLeapYear : public testing::TestWithParam<LeapYearResponce>
{
};

TEST_P(CheckLeapYear, ValidateLeapYear)
{
    auto [LeapYearToCheck, Response] = GetParam();

    ASSERT_EQ(Date::isLeapYear(LeapYearToCheck), Response);
}

INSTANTIATE_TEST_SUITE_P(LeapYear,
                         CheckLeapYear,
                         testing::ValuesIn(LeapYearWithResponse));


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

TEST(DataSet, CheckIfDataIsEqual){
    Date a{11,2,2000};
    Date b{11,02,2000};
    EXPECT_EQ(a,b);
}

TEST(DataSet, CheckIfDataIsNotEqual1){
    Date a{11,3,2000};  
    Date b{11,2,2000};
    EXPECT_NE(a,b);
}

TEST(DataSet, CheckIfDataIsNotEqual2){
    Date a{12,2,2000};  
    Date b{11,2,2000};
    EXPECT_NE(a,b);
}

TEST(DataSet, CheckIfDataIsNotEqual3){
    Date a{11,2,2001};  
    Date b{11,2,2000};
    EXPECT_NE(a,b);
}

TEST(DataSet, CheckIfDataIsNotEqual4){
    Date a{2,13,1999};  
    Date b{11,2,2000};
    EXPECT_NE(a,b);
}


TEST(DataSet, CheckPreIncOperator1){
    Date a{10,2,2000}; 
    ++a; 
    Date b{11,2,2000};
    EXPECT_EQ(a,b);
}

TEST(DataSet, CheckPreIncOperator2){
    Date a{31,1,2001}; 
    ++a; 
    Date b{1,2,2001};
    EXPECT_EQ(a,b);
}

TEST(DataSet, CheckPreIncOperator3){
    Date a{31,12,2001}; 
    ++a; 
    Date b{1,1,2002};
    EXPECT_EQ(a,b);
}

TEST(DataSet, CheckBigger_Smaller_Operator1){
    Date a{31,12,2001};  
    Date b{1,1,2002};
    EXPECT_LT(a,b);
}

TEST(DataSet, Check_Bigger_Smaller_Operator2){
    Date a{31,11,2001};  
    Date b{1,12,2001};
    EXPECT_LT(a,b);
}

TEST(DataSet, Check_Bigger_Smaller_Operator3){
    Date a{23,12,2001};  
    Date b{25,12,2001};
    EXPECT_LT(a,b);
}

TEST(DataSet, Check_Bigger_Smaller_Operator4){
    Date a{31,12,2001};  
    Date b{1,1,2002};
    EXPECT_GT(b,a);
}

TEST(DataSet, Check_Bigger_Smaller_Operator5){
    Date a{31,11,2001};  
    Date b{1,12,2001};
    EXPECT_GT(b,a);
}

TEST(DataSet, Check_Bigger_Smaller_Operator6){
    Date a{23,12,2001};  
    Date b{25,12,2001};
    EXPECT_GT(b,a);
}


TEST(DataSet, Distance){
    Date a{23,02,2023};  
    EXPECT_EQ(a.distanceFromCurrentData(),19);
}

TEST(DataSet, Distance2){
    Date a{5,02,2023};  
    EXPECT_EQ(a.distanceFromCurrentData(),1);
}

TEST(DataSet, Distance3){
    Date a{4,02,2023};  
    EXPECT_EQ(a.distanceFromCurrentData(),0);
}

TEST(DataSet, Distance4){
    Date a{1,02,2023};  
    EXPECT_EQ(a.distanceFromCurrentData(),0);
}

TEST(DataSet, Distance5){
    Date a{04,02,2024};  
    EXPECT_EQ(a.distanceFromCurrentData(),365);
}