#include "gtest/gtest.h"


#include "../Include/ValidatePassword.hpp"
#include "bcrypt.h"


//Boundary values check
TEST(ValidatePassword, LengthPassword){

    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbb8"),PasswordErrorCode::Ok);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb32"),PasswordErrorCode::Ok);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbb7"),PasswordErrorCode::WrongLength);
    EXPECT_EQ(ValidatePassword::checkLength("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb34"),PasswordErrorCode::WrongLength);
}

TEST(ValidatePassword, SpecialChar){

    EXPECT_EQ(ValidatePassword::checkSpecialChar("bbbbbbc"),PasswordErrorCode::NotContainSpecialChar);
    EXPECT_EQ(ValidatePassword::checkSpecialChar("bbbbbbbbbbbbsdasc!"),PasswordErrorCode::Ok);
}

TEST(ValidatePassword, UppercaseLetter){

    EXPECT_EQ(ValidatePassword::checkUppercaseLetter("bbbbbbc"),PasswordErrorCode::NotContainUppercaseLetter);
    EXPECT_EQ(ValidatePassword::checkUppercaseLetter("abcdDDE"),PasswordErrorCode::Ok);
}

TEST(ValidatePassword, LowercaseLetter){

    EXPECT_EQ(ValidatePassword::checkLowercaseLetter("NNCMASDLC"),PasswordErrorCode::NotContainLowercaseLetter);
    EXPECT_EQ(ValidatePassword::checkLowercaseLetter("ABCDddedKSSA"),PasswordErrorCode::Ok);
}

TEST(ValidatePassword, Number){

    EXPECT_EQ(ValidatePassword::checkNumber("abcdefgh"),PasswordErrorCode::NotContainNumber);
    EXPECT_EQ(ValidatePassword::checkNumber("abcd1egasg"),PasswordErrorCode::Ok);
}

TEST(ValidatePassword, PasswordMatch){

    EXPECT_EQ(ValidatePassword::checkPasswordMatch("abcdefg" , "abcdefg"),PasswordErrorCode::Ok);
    EXPECT_EQ(ValidatePassword::checkPasswordMatch("abcdefg" , "abcdefG"),PasswordErrorCode::PasswordNotMatch);
}

TEST(ValidatePassword, GivenPassword){

    EXPECT_EQ(ValidatePassword::checkGivenPassword("Br2!lL"),PasswordErrorCode::WrongLength);
    EXPECT_EQ(ValidatePassword::checkGivenPassword("Br2ssslL"),PasswordErrorCode::NotContainSpecialChar);
    EXPECT_EQ(ValidatePassword::checkGivenPassword("bbbbr2!lls"),PasswordErrorCode::NotContainUppercaseLetter);
    EXPECT_EQ(ValidatePassword::checkGivenPassword("ABCDE1!ACEVED"),PasswordErrorCode::NotContainLowercaseLetter);
    EXPECT_EQ(ValidatePassword::checkGivenPassword("ABCEEDEADSDSAF!ssss"),PasswordErrorCode::NotContainNumber);
    EXPECT_EQ(ValidatePassword::checkGivenPassword("ABCD1!ab"),PasswordErrorCode::Ok);
}

TEST(ValidatePassword, BcryptHash){

    std::string hash = bcrypt::generateHash("password");
    
    EXPECT_TRUE(bcrypt::validatePassword("password",hash));
    EXPECT_FALSE(bcrypt::validatePassword("passworD",hash));
}
