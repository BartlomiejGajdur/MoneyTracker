#include "../Include/Transaction.hpp"

size_t Transaction::counter{0};

std::string Transaction::returnExpenseCategoryInString(const ExpenseCategory& ExpenseCategory){
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

std::ostream& operator<<(std::ostream& os,Transaction& transaction){

    os<<"ID: " << transaction.ID_<<"      | "
    <<"Description: " << transaction.description_<<"      | "
    <<"Money: " << transaction.money_<<" [PLN]      | "
    <<"Category: " <<transaction.returnExpenseCategoryInString(transaction.expenseCategory_)<<" \n";

    return os;
}

std::string Transaction::transactionInString(){
    return "ID: "  +  std::to_string(this->ID_) + "      | "
     + "Description: "  +  this->description_ + "      | "
     + "Money: "  +  std::to_string(this->money_) + " [PLN]      | "
     + "Category: "  + this->returnExpenseCategoryInString(this->expenseCategory_) + " \n";
}