#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "bcrypt.h"

using vecConfig = std::vector<std::tuple<std::string,std::string,std::string>>;

enum class PasswordErrorCode {Ok, WrongLength, NotContainSpecialChar, NotContainUppercaseLetter, NotContainLowercaseLetter, NotContainNumber, PasswordNotMatch};

namespace ValidatePassword{

    PasswordErrorCode checkLength(const std::string& password);
    PasswordErrorCode checkSpecialChar(const std::string& password);
    PasswordErrorCode checkUppercaseLetter(const std::string& password);
    PasswordErrorCode checkLowercaseLetter(const std::string& password);
    PasswordErrorCode checkNumber(const std::string& password);
    PasswordErrorCode checkPasswordMatch(const std::string& LHSpassword, const std::string& RHSpassword);
    PasswordErrorCode checkGivenPassword(const std::string& password);

    std::tuple<std::string,std::string,std::string>& getCurrentUser();
    vecConfig& getVecOfFileNameLoginPassword_();
    void loadConfigFromFile();
    bool registerNewUser(const std::string& Login, const std::string& Password);
    bool saveConfigToFile();
    bool logIn(const std::string& Login, const std::string& Password);
    
}