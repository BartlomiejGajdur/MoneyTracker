#include "Menu_LOG.hpp"
#include "User.hpp"

class Menu_Main{
public:
    void run();

private:
    Menu_LOG MenuLOG;

    void printOptions();
    void greetUser(const User& user);

    void AddNewTransaction_Menu(User& user);
    void SetCurrentMoney_Menu(User& user);
    void printAllTransactions_Menu(User& user);
    void sortTransactionByDate_Menu(User& user);
    void sortTransactionByNumberOfExpenseCategory_Menu(User& user);
    void showSpendingOnIndividualExpenseCategory_Menu(User& user);
    void showSpendingsPercentageOnIndividualExpenseCategory_Menu(User& user);
    void modifyDateTransactionByID_Menu(User& user);
    void removeTransactionByID_Menu(User& user);
    void deleteAllTransactions_Menu(User& user);

};