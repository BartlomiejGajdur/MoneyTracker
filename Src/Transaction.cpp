#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

#include "../Include/MenuFunctions.hpp"
#include "../Include/Transaction.hpp"

size_t Transaction::counter{0};

DateErrorCode Transaction::setDate(int day, int month, int year) {
    return date_.setDate(day, month, year);
}

std::string Transaction::returnExpenseCategoryInString(const ExpenseCategory& ExpenseCategory) {
    switch (ExpenseCategory) {
    case ExpenseCategory::Housing:
        return "Housing";
        break;
    case ExpenseCategory::Transportation:
        return "Transportation";
        break;
    case ExpenseCategory::Food:
        return "Food";
        break;
    case ExpenseCategory::Utilities:
        return "Utilities";
        break;
    case ExpenseCategory::Insurance:
        return "Insurance";
        break;
    case ExpenseCategory::Medical:
        return "Medical";
        break;
    case ExpenseCategory::Savings:
        return "Savings";
        break;
    case ExpenseCategory::PersonalSpending:
        return "PersonalSpending";
        break;
    case ExpenseCategory::Entertainment:
        return "Entertainment";
        break;
    case ExpenseCategory::Miscellaneous:
        return "Miscellaneous";
        break;
    case ExpenseCategory::SettingTheBill:
        return "SettingTheBill";
        break;
    case ExpenseCategory::Work:
        return "Work";
        break;
    case ExpenseCategory::Others:
        return "Others";
        break;
    case ExpenseCategory::Bills:
        return "Bills";
        break;
    case ExpenseCategory::Loan:
        return "Loan";
        break;

    default:
        return "Error";
        break;
    }
}

std::ostream& operator<<(std::ostream& os, Transaction& transaction) {
    os << "ID: " << transaction.ID_ << "      | "
       << "Description: " << transaction.description_ << "      | "
       << "Money: " << transaction.money_ << " [PLN]      | "
       << "Category: " << transaction.returnExpenseCategoryInString(transaction.expenseCategory_) << "      | "
       << "Date: " << transaction.date_ << " \n";

    return os;
}

std::string Transaction::transactionInString() {
    std::string money = std::to_string(this->money_);
    money.erase(money.length() - 4, money.length());
    money += " PLN";
    std::stringstream is;
    this->money_ >= 0 ? money = MenuFunctions::SetTextColor(Color::Green, money) : money = MenuFunctions::SetTextColor(Color::Red, money);

    std::string shortedDescirption = this->description_;

    if (shortedDescirption.size() >= 35) {
        shortedDescirption.erase(shortedDescirption.begin() + 35, shortedDescirption.end());
        shortedDescirption += "(...)";
    }

    is << "| " << std::setw(3) << std::left << this->ID_ << " | "
       << std::setw(40) << std::left << shortedDescirption << " | "
       << std::setw(25) << std::left << money << " | "
       << std::setw(20) << std::left << this->returnExpenseCategoryInString(this->expenseCategory_) << " | "
       << std::setw(10) << std::left << this->date_.dateInString() << " |\n";

    return is.str();
}
