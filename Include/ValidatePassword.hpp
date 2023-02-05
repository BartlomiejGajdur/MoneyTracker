#pragma once

#include <tuple>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include "bcrypt.h"

using vecConfig = std::vector<std::tuple<std::string,std::string,std::string>>;

enum class PasswordErrorCode {Ok, WrongLength, NotContainSpecialChar, NotContainUppercaseLetter, NotContainLowercaseLetter, NotContainNumber};

namespace ValidatePassword{


    PasswordErrorCode checkLength(const std::string& password);
    PasswordErrorCode checkSpecialChar(const std::string& password);
    PasswordErrorCode checkUppercaseLetter(const std::string& password);
    PasswordErrorCode checkLowercaseLetter(const std::string& password);
    PasswordErrorCode checkNumber(const std::string& password);
    PasswordErrorCode checkGivenPassword(const std::string& password);

    std::tuple<std::string,std::string,std::string>& getCurrentUser();
    vecConfig& getVecOfFileNameLoginPassword_();
    void loadConfigFromFile();
    bool registerNewUser(const std::string& Login, const std::string& Password);
    bool saveConfigToFile();
    bool logIn(const std::string& Login, const std::string& Password);

    //To będzie raczej w jakims MENU CZY COS
    std::string insertPassword();

}