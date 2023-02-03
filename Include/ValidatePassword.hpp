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

    vecConfig vecOfFileNameLoginPassword_;
    std::string configName = "../config.txt";
    std::tuple<std::string,std::string,std::string> currentUser;


    PasswordErrorCode checkLength(const std::string& password){
        return (password.size() >= 8 && password.size() <= 32) ? PasswordErrorCode::Ok : PasswordErrorCode::WrongLength;
    }

    PasswordErrorCode checkSpecialChar(const std::string& password){
        //!"#$%&'()*+,-./
        //:;<=>?@
        //[\]^_`
        auto it = std::find_if(password.begin(),password.end(),[](char zn)
                                                                    {
                                                                        return (zn>=33 && zn<=47) || (zn>=58 && zn z<=64) || (zn>=91 && zn z<=98) || (zn>=123);
                                                                    });

        return it != password.end() ? PasswordErrorCode::Ok : PasswordErrorCode::NotContainSpecialChar;
    }

     PasswordErrorCode checkUppercaseLetter(const std::string& password){

        auto it = std::find_if(password.begin(),password.end(),[](char zn)
                                                                    {
                                                                        return (zn>=65 && zn<=90);
                                                                    });

        return it != password.end() ? PasswordErrorCode::Ok : PasswordErrorCode::NotContainUppercaseLetter;
    }

     PasswordErrorCode checkLowercaseLetter(const std::string& password){

        auto it = std::find_if(password.begin(),password.end(),[](char zn)
                                                                    {
                                                                        return (zn>=97 && zn<=122);
                                                                    });

        return it != password.end() ? PasswordErrorCode::Ok : PasswordErrorCode::NotContainLowercaseLetter;
    }

    PasswordErrorCode checkNumber(const std::string& password){

        auto it = std::find_if(password.begin(),password.end(),[](char zn)
                                                                    {
                                                                        return (zn>=48 && zn<=57);
                                                                    });

        return it != password.end() ? PasswordErrorCode::Ok : PasswordErrorCode::NotContainNumber;
    }

    PasswordErrorCode checkGivenPassword(const std::string& password){

        if(checkLength(password) != PasswordErrorCode::Ok)
            return checkLength(password);
        
        if(checkSpecialChar(password) != PasswordErrorCode::Ok)
            return checkSpecialChar(password);
        
        if(checkUppercaseLetter(password) != PasswordErrorCode::Ok)
            return checkUppercaseLetter(password);
        
        if(checkLowercaseLetter(password) != PasswordErrorCode::Ok)
            return checkLowercaseLetter(password);
        
        if(checkNumber(password) != PasswordErrorCode::Ok)
            return checkNumber(password);

    }


   
    void loadConfigFromFile(){

        std::vector<std::string> vec;
        char znak;
        std::string linia;
        std::fstream plik;
        plik.open(configName,plik.in);

        if(plik.is_open()){
           
            while (!plik.eof())
             {
                znak = plik.get();

                if (znak == '\n')
                {
                    
                }
                else if(znak != ';')
                {
                    linia += znak;
                }
                else
                {
                    vec.push_back(linia);
                    linia.clear();
                }
             }
             plik.close();

             for(int i = 0; i<vec.size(); i+=3){
                vecOfFileNameLoginPassword_.push_back(std::make_tuple(vec[i],vec[i+1],vec[i+2]));
             }

        }
    }

    bool saveConfigToFile(){

    std::fstream plik;

    plik.open(configName, plik.out | plik.trunc);

    if (plik.is_open())
    {
         for(auto [l,s,r]: vecOfFileNameLoginPassword_){
                plik<<l<<";"<<s<<";"<<r<<";\n";
             }
            plik.close();
            return true;
    }
    else
        return false;
}

    bool registerNewUser(const std::string& Login, const std::string& Password){
        auto it = std::find_if(vecOfFileNameLoginPassword_.begin(),vecOfFileNameLoginPassword_.end(),[&](auto user)
                                                                                                        {
                                                                                                            return bcrypt::validatePassword(Login,std::get<1>(user));
                                                                                                        });

        if(it == vecOfFileNameLoginPassword_.end()){
            std::string PersonalConfigName = "config" + std::to_string(vecOfFileNameLoginPassword_.size()+1);

            vecOfFileNameLoginPassword_.push_back(std::make_tuple(PersonalConfigName,bcrypt::generateHash(Login), bcrypt::generateHash(Password)));
            saveConfigToFile();
            return true;
        }else{
            return false;
        }
            
    }

    bool logIn(const std::string& Login, const std::string& Password){
        auto it = std::find_if(vecOfFileNameLoginPassword_.begin(),vecOfFileNameLoginPassword_.end(),[&](auto user)
                                                                                                        {
                                                                                                            return bcrypt::validatePassword(Login,std::get<1>(user)) && bcrypt::validatePassword({Password},std::get<2>(user)) ;
                                                                                                        });

        if(it != vecOfFileNameLoginPassword_.end()){
            currentUser = std::make_tuple(std::get<0>(*it), Login, std::get<2>(*it));
            return true;
        }else{
            return false;
        }
    }

    //To będzie raczej w jakims MENU CZY COS
    std::string insertPassword(){
        std::string password{};
        char ch;

        do{
            ch = _getch();
            if(ch == 8)
            {
                if(password.size()>0)
                {
                    std::cout<<"\b \b";
                    password.pop_back();
                }
                
            }else if(ch == 13){

            }
            else{
                std::cout<<"*";
                password+=ch;
            }

        }while(ch != 13);

        return password;
    }

   

}