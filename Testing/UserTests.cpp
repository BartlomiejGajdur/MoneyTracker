#include "gtest/gtest.h"


#include <vector>

#include "../Include/User.hpp"


struct UserUnderTestFixture : public ::testing::Test{
    User person{};

    Tranzaction T1{"A",12,ExpenseCategory::PersonalSpending};
    Tranzaction T2{"B",123,ExpenseCategory::Medical};
    Tranzaction T3{"C",1242,ExpenseCategory::Food};
    Tranzaction T4{"D",1244,ExpenseCategory::Entertainment};
    Tranzaction T5{"E",12.22,ExpenseCategory::Housing};

    void addAllTranzactions(){
        person.addTranzaction(std::make_shared<Tranzaction>(T1));
        person.addTranzaction(std::make_shared<Tranzaction>(T2));
        person.addTranzaction(std::make_shared<Tranzaction>(T3));
        person.addTranzaction(std::make_shared<Tranzaction>(T4));
        person.addTranzaction(std::make_shared<Tranzaction>(T5));
    }
};


TEST_F(UserUnderTestFixture, RemovingByID){

    addAllTranzactions();

    EXPECT_EQ(person.removeTranzactionById(0),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTranzactionById(1),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTranzactionById(2),UserErrorCode::Ok);
    EXPECT_EQ(person.removeTranzactionById(6),UserErrorCode::NoTranzactionFound);


}