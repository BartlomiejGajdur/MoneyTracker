#include "../include/Bills.hpp"

std::string Bills::getBillType(){
    switch (billType_)
    {
    case BillType::Electricity:
        return "Electricity";
        break;

    case BillType::Water:
        return "Water";
        break;

    case BillType::Gas:
        return "Gas";
        break;

    case BillType::Internet:
        return "Internet";
        break;
    
    default:
        return "ERROR";
        break;
    }
}