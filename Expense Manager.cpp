#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Date {
    int day, month, year;

    Date(int d, int m, int y) : day(d), month(m), year(y) {}
};

struct Transaction {
    Date date;
    string itemName;
    double price;

    Transaction(Date d, const string& name, double p) : date(d), itemName(name), price(p) {}
};

struct Account {
    string name;
    vector<Transaction> transactions;

    Account(const string& accName) : name(accName) {}
};

class ExpenseManagementSystem {
private:
    vector<Account> accounts;

public:
    int totalIncome,totalSpending;
    void displayMenu() {
        cout << "\n                                Expense Management System Menu:\n" << endl;
        cout << "1. Add new account" << endl;
        cout << "2. New transaction" << endl;
        cout << "3. Income transaction" << endl;
        cout << "4. Delete transactions" << endl;
        cout << "5. Sort transactions" << endl;
        cout << "6. Display" << endl;
        cout << "7. Choose account" << endl;
        cout << "8. Delete account" << endl;
        cout << "9. Export data" << endl;
        cout << "10. Exit" << endl;
    }

    void chooseAccount() {
         int accountIndex;
    cout << "\nAvailable accounts:" << endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << i + 1 << ". " << accounts[i].name << endl;
    }

    cout << "Choose account (enter number): ";
    cin >> accountIndex;
    if (accountIndex <= accounts.size() && accountIndex > 0) {
        // Implement logic to perform actions on the selected account
        Account& selectedAccount = accounts[accountIndex - 1];
        // Additional actions can be performed on the selected account
        cout << "You selected account: " << selectedAccount.name <<endl;
    } else {
        cout << "Invalid account selection!" << endl;
    }
    }



    void newTransaction() {
        int accountIndex;
    string itemName;
    int day, month, year;
    double price;

    cout << "Enter account number to add transaction: ";
        cout << "\nAvailable accounts:" << endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << i + 1 << ". " << accounts[i].name << endl;
    }
    cin >> accountIndex;
    if (accountIndex <= accounts.size() && accountIndex > 0) {
        cout << "Enter transaction details:" << endl;
        cout << "Item Name: ";
        cin.ignore(); // Ignore newline left in the buffer
        getline(cin, itemName);

        cout << "Date (dd mm yyyy): ";
        cin >> day >> month >> year;

        cout << "Use \"-\" for spending\nPrice: ";
        cin >> price;

        Date date(day, month, year);
        Transaction newTransaction(date, itemName, price);

        accounts[accountIndex - 1].transactions.push_back(newTransaction);
        cout << "Transaction added successfully to account: " << accounts[accountIndex - 1].name << endl;
    } else {
        cout << "Invalid account selection!" << endl;
    }
    }



    void incomeTransaction() {
        int accountIndex;
    cout << "Enter account number to add income transaction: ";
        cout << "\nAvailable accounts:" << endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << i + 1 << ". " << accounts[i].name << endl;
    }
    cin >> accountIndex;

    if (accountIndex <= accounts.size() && accountIndex > 0) {
        string incomeType;
        int day, month, year;
        double incomeAmount;

        cout << "Enter details for income transaction:" << endl;
        cout << "Income Type: ";
        cin.ignore(); // Ignore newline left in the buffer
        getline(cin, incomeType);

        cout << "Date (dd mm yyyy): ";
        cin >> day >> month >> year;

        cout << "Income Amount: ";
        cin >> incomeAmount;

        Date date(day, month, year);
        Transaction newIncome(date, incomeType, incomeAmount);

        accounts[accountIndex - 1].transactions.push_back(newIncome);
        cout << "Income transaction added successfully to account '" << accounts[accountIndex - 1].name << "'" << endl;
    } else {
        cout << "Invalid account selection!" << endl;
    }
    }

    void deleteTransactions() {
    int accountIndex;
    cout << "Enter account number to delete transactions: ";
        cout << "\nAvailable accounts:" << endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << i + 1 << ". " << accounts[i].name << endl;
    }
    cin >> accountIndex;
    if (accountIndex <= accounts.size() && accountIndex > 0) {
        vector<Transaction>& transactions = accounts[accountIndex - 1].transactions;

        if (transactions.empty()) {
            cout << "No transactions found for deletion." << endl;
            return;
        }

        cout << "Transactions for account '" << accounts[accountIndex - 1].name << "':" << endl;
        cout << "Transaction ID\tDate\t\tItem Name\tPrice" << endl;
        for (size_t i = 0; i < transactions.size(); ++i) {
            cout << i + 1 << "\t\t" << transactions[i].date.day << "/" << transactions[i].date.month << "/" << transactions[i].date.year << "\t";
            cout << transactions[i].itemName << "\t\t" << transactions[i].price << endl;
        }

        cout << "Enter the Transaction ID to delete: ";
        int transactionID;
        cin >> transactionID;
        if (transactionID <= transactions.size() && transactionID > 0) {
            transactions.erase(transactions.begin() + transactionID - 1);
            cout << "Transaction ID " << transactionID << " deleted successfully." << endl;
        } else {
            cout << "Invalid Transaction ID!" << endl;
        }
    } else {
        cout << "Invalid account selection!" << endl;
    }
}


    void sortTransactionsByDate(int accountIndex) {
    if (accountIndex <= accounts.size() && accountIndex > 0) {
        vector<Transaction>& transactions = accounts[accountIndex - 1].transactions;

        // Custom comparison function to sort transactions by date
        auto compareByDate = [](const Transaction& a, const Transaction& b) {
            if (a.date.year != b.date.year)
                return a.date.year < b.date.year;
            if (a.date.month != b.date.month)
                return a.date.month < b.date.month;
            return a.date.day < b.date.day;
        };

        sort(transactions.begin(), transactions.end(), compareByDate);

        cout << "Transactions sorted by date for account '" << accounts[accountIndex - 1].name << "'" << endl;
    } else {
        cout << "Invalid account selection!" << endl;
    }
}

    void displayAllTransactions() {
      int accountIndex;
    cout << "Enter account number to display transactions: ";
        cout << "\nAvailable accounts:" << endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << i + 1 << ". " << accounts[i].name << endl;
    }
    cin >> accountIndex;

    if (accountIndex <= accounts.size() && accountIndex > 0) {
        cout << "Transactions for account '" << accounts[accountIndex - 1].name << "':" << endl;
        const vector<Transaction>& transactions = accounts[accountIndex - 1].transactions;

        if (transactions.empty()) {
            cout << "No transactions found." << endl;
        } else {
            double totalIncome = 0.0;
            double totalSpending = 0.0;

            cout << "Income Transactions:" << endl;
            cout << "Date\t\tIncome Type\tAmount" << endl;
            for (const auto& transaction : transactions) {
                if (transaction.price > 0) {
                    cout << transaction.date.day << "/" << transaction.date.month << "/" << transaction.date.year << "\t";
                    cout << transaction.itemName << "\t\t" << transaction.price << endl;
                    totalIncome += transaction.price;
                }
            }

            cout << "\nExpense Transactions:" << endl;
            cout << "Date\t\tItem Name\tAmount" << endl;
            for (const auto& transaction : transactions) {
                if (transaction.price < 0) {
                    cout << transaction.date.day << "/" << transaction.date.month << "/" << transaction.date.year << "\t";
                    cout << transaction.itemName << "\t\t" << -transaction.price << endl; // Convert negative to positive for display
                    totalSpending -= transaction.price; // Convert negative to positive for total spending
                }
            }

            cout << "\nTotal Income: " << totalIncome << endl;
            cout << "Total Spending: " << totalSpending << endl;
            cout << "Current Balance: " << totalIncome-totalSpending << endl;
        }
    } else {
        cout << "Invalid account selection!" << endl;
    }
}


    void addNewAccount() {
         string newAccountName;
    cout << "Enter the name for the new account: ";
    cin.ignore(); // Ignore newline left in the buffer
    getline(cin, newAccountName);

    Account newAccount(newAccountName);
    accounts.push_back(newAccount);

    cout << "New account '" << newAccountName << "' added successfully." << endl;
}



    void deleteAccount() {
            int accountIndex;
    cout << "Enter account number to delete: ";
        cout << "\nAvailable accounts:" << endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << i + 1 << ". " << accounts[i].name << endl;
    }
    cin >> accountIndex;
    if (accountIndex <= accounts.size() && accountIndex > 0) {
        string deletedAccountName = accounts[accountIndex - 1].name;
        accounts.erase(accounts.begin() + accountIndex - 1);
        cout << "Account '" << deletedAccountName << "' deleted successfully." << endl;
    } else {
        cout << "Invalid account selection!" << endl;
    }
    }



    void exportData() {


      int accountIndex;
    cout << "Enter account number to display transactions: ";
        cout << "\nAvailable accounts:" << endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << i + 1 << ". " << accounts[i].name << endl;
    }
    cin >> accountIndex;

    if (accountIndex <= accounts.size() && accountIndex > 0) {
        cout << "Transactions for account '" << accounts[accountIndex - 1].name << "':" << endl;
        const vector<Transaction>& transactions = accounts[accountIndex - 1].transactions;

        if (transactions.empty()) {
            cout << "No transactions found." << endl;
        } else {
            double totalIncome = 0.0;
            double totalSpending = 0.0;

           // cout << "Income Transactions:" << endl;
          //  cout << "Date\t\tIncome Type\tAmount" << endl;
            for (const auto& transaction : transactions) {
                if (transaction.price > 0) {
                  //  cout << transaction.date.day << "/" << transaction.date.month << "/" << transaction.date.year << "\t";
                  //  cout << transaction.itemName << "\t\t" << transaction.price << endl;
                    totalIncome += transaction.price;
                }
            }

          //  cout << "\nExpense Transactions:" << endl;
          //  cout << "Date\t\tItem Name\tAmount" << endl;
            for (const auto& transaction : transactions) {
                if (transaction.price < 0) {
                 //   cout << transaction.date.day << "/" << transaction.date.month << "/" << transaction.date.year << "\t";
                //    cout << transaction.itemName << "\t\t" << -transaction.price << endl; // Convert negative to positive for display
                    totalSpending -= transaction.price; // Convert negative to positive for total spending
                }
            }

        //    cout << "\nTotal Income: " << totalIncome << endl;
         //   cout << "Total Spending: " << totalSpending << endl;
         //   cout << "Current Balance: " << totalIncome-totalSpending << endl;

        }
    } else {
        cout << "Invalid account selection!" << endl;
    }




















        // Implement logic to export data to an Excel file
        ofstream outputFile("D://Zeeshan(excel).csv");

        if (!outputFile.is_open()) {
            cerr << "Unable to open file!" << endl;
            return;
        }








        outputFile << "Date,Item Name/Salary Type,Price\n";

        for (const auto& account : accounts) {
            for (const auto& transaction : account.transactions) {
                outputFile << transaction.date.day << "/" << transaction.date.month << "/" << transaction.date.year
                           << "," << transaction.itemName << "," << transaction.price << "\n";
            }

        }
          //          outputFile << "\nTotal Income,Total Spending,Current Balance\n";
        //    outputFile << totalIncome << "," << totalSpending << "," << totalIncome-totalSpending;

        outputFile.close();
        cout << "Data exported successfully to 'D://Zeeshan(excel).csv" << endl;
    }



    void run() {
        int choice;
        do {
            displayMenu();
            cout << "\n\tEnter your choice: \n";
            cin >> choice;

            switch (choice) {
                case 1:
                    addNewAccount();
                    break;
                case 2:
                    newTransaction();
                    break;
                case 3:
                    incomeTransaction();
                    break;
                case 4:
                    deleteTransactions();
                    break;
                case 5:
                    int accountIndex;
                    cout << "Enter account number to sort transactions by date: ";
                    cin >> accountIndex;
                    sortTransactionsByDate(accountIndex);
                    break;
                case 6:
                    displayAllTransactions();
                    break;
                case 7:
                    chooseAccount();
                    break;
                case 8:
                    deleteAccount();
                    break;
                case 9:
                    exportData();
                    break;
                case 10:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice! Please enter a valid option." << endl;
            }
        } while (choice != 8);
    }
};

int main() {
    ExpenseManagementSystem system;
    system.run();

    return 0;
}
