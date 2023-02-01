#include "gtest/gtest.h"


#include <vector>

#include "../Include/User.hpp"


struct UserUnderTestFixture : public ::testing::Test{
    
    User person{};
    Transaction T1{"A",-0.01,ExpenseCategory::Food, Date{11,01,2000}};
    Transaction T2{"B",-123,ExpenseCategory::PersonalSpending, Date{11,01,2000}};
    Transaction T3{"C",1242,ExpenseCategory::Food, Date{11,01,2000}};
    Transaction T4{"C",-1242,ExpenseCategory::Food, Date{11,01,2000}};
    Transaction T5{"E",12454,ExpenseCategory::PersonalSpending, Date{11,01,2000}};
    Transaction T6{"F",-0.2,ExpenseCategory::Housing, Date{11,01,2000}};

    void addAllTransactions(){
        

        person.addTransaction(std::make_shared<Transaction>(T1));
        person.addTransaction(std::make_shared<Transaction>(T2));
        person.addTransaction(std::make_shared<Transaction>(T3));
        person.addTransaction(std::make_shared<Transaction>(T4));
        person.addTransaction(std::make_shared<Transaction>(T5));
        person.addTransaction(std::make_shared<Transaction>(T6));
    }
};


TEST_F(UserUnderTestFixture, RemovingByID){

    addAllTransactions();

    EXPECT_EQ(person.removeTransactionById(0),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTransactionById(1),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTransactionById(2),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTransactionById(6),UserErrorCode::NoTransactionFound);

    person.clearTransactions();


}

TEST_F(UserUnderTestFixture, CountSpendings){

    addAllTransactions();

    EXPECT_EQ(person.countWholeSpendings(),double(-1365.21));

    person.clearTransactions();

}

TEST_F(UserUnderTestFixture, ModifyDateTransactionByID){

    addAllTransactions();

    EXPECT_EQ(person.modifyDateTransactionById(12,20,12,2000),UserErrorCode::Ok);
    EXPECT_EQ(person.modifyDateTransactionById(100000,32,13,2000),UserErrorCode::NoTransactionFound);
    EXPECT_EQ(person.modifyDateTransactionById(100000,2,12,2000),UserErrorCode::NoTransactionFound);
    EXPECT_EQ(person.modifyDateTransactionById(12,32,12,2000),UserErrorCode::IncorrectData);
    EXPECT_EQ(person.modifyDateTransactionById(12,20,32,2000),UserErrorCode::IncorrectData);
    EXPECT_EQ(person.modifyDateTransactionById(12,20,12,211111),UserErrorCode::IncorrectData);

    person.clearTransactions();

}

TEST_F(UserUnderTestFixture, GetCurrentMoneyWITHOUTdeclaratedStartedOne){

    addAllTransactions();

    EXPECT_EQ(person.getCurrentMoney(),12330.79);
   
    person.clearTransactions();

}