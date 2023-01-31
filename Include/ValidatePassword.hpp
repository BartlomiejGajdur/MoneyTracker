#pragma once
#include <tuple>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "bcrypt.h"

using vecConfig = std::vector<std::tuple<std::string,std::string,std::string>>;

namespace ValidatePassword{

    vecConfig vecOfFileNameLoginPassword_;
    std::string configName = "../config.txt";
   
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
            
            return true;
        }else{
            std::cout<<"PODANY LOGIN JUZ ISTNIEJE W BAZIE";
            return false;
        }
            
    }

   

}