#include "gtest/gtest.h"


#include <vector>

#include "../Include/User.hpp"


struct UserUnderTestFixture : public ::testing::Test{
    User person{};

    Transaction T1{"A",12,ExpenseCategory::PersonalSpending};
    Transaction T2{"B",123,ExpenseCategory::Medical};
    Transaction T3{"C",1242,ExpenseCategory::Food};
    Transaction T4{"D",1244,ExpenseCategory::Entertainment};
    Transaction T5{"E",12.22,ExpenseCategory::Housing};

    void addAllTransactions(){
        person.addTransaction(std::make_shared<Transaction>(T1));
        person.addTransaction(std::make_shared<Transaction>(T2));
        person.addTransaction(std::make_shared<Transaction>(T3));
        person.addTransaction(std::make_shared<Transaction>(T4));
        person.addTransaction(std::make_shared<Transaction>(T5));
    }
};


TEST_F(UserUnderTestFixture, RemovingByID){

    addAllTransactions();

    EXPECT_EQ(person.removeTransactionById(0),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTransactionById(1),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTransactionById(2),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTransactionById(6),UserErrorCode::NoTransactionFound);


}