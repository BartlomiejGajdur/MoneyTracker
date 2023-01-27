#include "../Include/Tranzaction.hpp"

size_t Tranzaction::counter{0};

std::string Tranzaction::printExpenseCategory(const ExpenseCategory& ExpenseCategory){
    switch (ExpenseCategory)
    {
    case ExpenseCategory::Housing :
        return "Housing" ;
        break;
    case ExpenseCategory::Transportation :
        return "Transportation" ;
        break;
    case ExpenseCategory::Food :
        return "Food" ;
        break;
    case ExpenseCategory::Utilities :
        return "Utilities" ;
        break;
    case ExpenseCategory::Insurance :
        return "Insurance" ;
        break;
    case ExpenseCategory::Medical :
        return "Medical" ;
        break;
    case ExpenseCategory::Savings :
        return "Savings" ;
        break;
    case ExpenseCategory::PersonalSpending :
        return "PersonalSpending" ;
        break;
    case ExpenseCategory::Entertainment :
        return "Entertainment" ;
        break;
    case ExpenseCategory::Miscellaneous :
        return "Miscellaneous" ;
        break;
    
    default:
        return "Error";
        break;
    }
}

std::ostream& operator<<(std::ostream& os,Tranzaction& tranzaction){

    os<<"ID: " << tranzaction.ID_<<"      | "
    <<"Description: " << tranzaction.description_<<"      | "
    <<"Money: " << tranzaction.money_<<" [PLN]      | "
    <<"Category: " <<tranzaction.printExpenseCategory(tranzaction.expenseCategory_)<<" \n";

    return os;
}