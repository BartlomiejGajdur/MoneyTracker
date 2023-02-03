#include "gtest/gtest.h"


#include "../Include/ValidatePassword.hpp"


//Boundary values check
TEST(ValidatePassword, LengthPassword){

    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbb8"),PasswordErrorCode::Ok);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb32"),PasswordErrorCode::Ok);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbb7"),PasswordErrorCode::WrongLength);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb34"),PasswordErrorCode::WrongLength);
}

