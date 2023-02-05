#include "gtest/gtest.h"


#include "../Include/ValidatePassword.hpp"
#include "C:\Users\gajdu\Desktop\C++\MoneyTracker\build\_deps\bcrypt-src\include\bcrypt.h"

//Boundary values check
TEST(ValidatePassword, LengthPassword){

    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbb8"),PasswordErrorCode::Ok);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb32"),PasswordErrorCode::Ok);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbb7"),PasswordErrorCode::WrongLength);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb34"),PasswordErrorCode::WrongLength);
}

TEST(ValidatePassword, HashPOSITIVE){

    EXPECT_TRUE(bcrypt::validatePassword("password",bcrypt::generateHash("password")));
}

TEST(ValidatePassword, HashNEGATIVE){

    EXPECT_FALSE(bcrypt::validatePassword("passworD",bcrypt::generateHash("password")));
}
