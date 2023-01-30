#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using vecConfig = std::vector<std::tuple<std::string,std::string,std::string>>;

namespace ValidatePassword{

    vecConfig vecOfFileNameLoginPassword_;
    std::string config = "../config.txt";
   
    void loadFromFile(vecConfig& vecTuple){
        std::cout<<"hej";
        std::vector<std::string> vec;
        char znak;
        std::string linia;
        std::fstream plik;
        plik.open(config,plik.in);

        if(plik.is_open()){
            std::cout<<"hej";
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

             for(int i = 0; i<vec.size(); i+=3){
                vecOfFileNameLoginPassword_.push_back(std::make_tuple(vec[i],vec[i+1],vec[i+2]));
             }

             for(auto [l,s,r]: vecOfFileNameLoginPassword_){
                std::cout<<l<<" "<<s<<" "<<r<<" \n";
             }
        }
    }

}