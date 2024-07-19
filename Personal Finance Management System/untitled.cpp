#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<sstream>
#include<fstream>
using namespace std;

struct transaction {
    int id;
    string date;
    double amount;
    string category;
    string type; //"income" or "expense"
};

const int max_transaction = 1000;
transaction transactions[max_transaction]; // Array of transactions
int transactioncount = 0; 
int nextID = 1;

void addtransaction(string date, double amount, string category, string type) {
    if (transactioncount >= max_transaction) {
        cout << "Transaction limit reached!\n";
        return;
    }
    transaction newtransaction = { nextID++, date, amount, category, type };
    transactions[transactioncount++] = newtransaction;
    cout << "Transaction added successfully!\n";
}

void deletetransaction(int ID) {
    bool found = false;
    for (int i = 0; i < transactioncount; i++) {
        if (transactions[i].id == ID) {
            for (int j = i; j < transactioncount - 1; j++) {
                transactions[j] = transactions[j + 1]; // Shift transactions
            }
            transactioncount--;
            found = true;
            cout << "Transaction Deleted Successfully!\n";
            break;
        }
    }
    if (!found) {
        cout << "Transaction Not Found\n";
    }
}

void view() {
    for (int i = 0; i < transactioncount; i++) {
        cout << "ID: " << transactions[i].id << endl;
        cout << "Date: " << transactions[i].date << endl;
        cout << "Amount: " << transactions[i].amount << endl;
        cout << "Category: " << transactions[i].category << endl;
        cout << "Type: " << transactions[i].type << endl;
    }
}

void update(int id, string newdate, double newamount, string newcategory, string newtype) {
    for (int i = 0; i < transactioncount; i++) {
        if (transactions[i].id == id) {
            transactions[i].date = newdate;
            transactions[i].amount = newamount;
            transactions[i].category = newcategory;
            transactions[i].type = newtype;
            cout << "Transaction Updated!\n";
            return;
        }
    }
    cout << "Transaction not found\n";
}

void summary() {
    double totalincome = 0;
    double totalexpenses = 0;
    for (int i = 0; i < transactioncount; i++) {
        if (transactions[i].type == "income") {
            totalincome += transactions[i].amount;
        } else if (transactions[i].type == "expense") {
            totalexpenses += transactions[i].amount;
        }
    }
    double balance = totalincome - totalexpenses;
    cout << "Total Income: " << totalincome << endl;
    cout << "Total Expenses: " << totalexpenses << endl;
    cout << "Balance: " << balance << endl;
}

void categorysummary() {
    map<string, double> categorytotals;
    for (int i = 0; i < transactioncount; i++) {
        categorytotals[transactions[i].category] += transactions[i].amount;
    }
    cout << "Category-wise Summary:\n";
    for (const auto& category : categorytotals) {
        cout << "Category: " << category.first << ", Total Amount: " << category.second << '\n';
    }
}

void monthlyreport(int month, int year) {
    double totalincome = 0, totalexpense = 0, balance = 0;
    for (int i = 0; i < transactioncount; i++) {
        int transmonth, transyear;
        stringstream ss(transactions[i].date);
        char mark;
        ss >> transyear >> mark >> transmonth;
        if (transmonth == month && transyear == year) {
            if (transactions[i].type == "income") {
                totalincome += transactions[i].amount;
            } else if (transactions[i].type == "expense") {
                totalexpense += transactions[i].amount;
            }
        }
    }
    balance = totalincome - totalexpense;
    cout << "Monthly Report for " << month << "/" << year << "\n";
    cout << "Total Income: " << totalincome << endl;
    cout << "Total Expenses: " << totalexpense << endl;
    cout << "Balance: " << balance << endl;
}

// Setting category-wise Budget
map<string, double> categorybudgets;

void setbudget(string category, double budget) {
    categorybudgets[category] = budget;
    cout << "Budget set for category " << category << ": " << budget << endl;
}

void trackbudget() {
    map<string, double> categoryspending;
    for (int i = 0; i < transactioncount; i++) {
        if (transactions[i].type == "expense") {
            categoryspending[transactions[i].category] += transactions[i].amount;
        }
    }
    cout << "Budget Tracking:\n";
    for (const auto& budget : categorybudgets) {
        string category = budget.first;
        double budgetamount = budget.second;
        double spentamount = categoryspending[category];
        cout << "Category: " << category << endl;
        cout << "Budget: " << budgetamount << endl;
        cout << "Spent: " << spentamount;
        if (spentamount > budgetamount) {
            cout << " OVER-BUDGET!";
        }
        cout << endl;
    }
}

void exportdata() {
    ofstream file("transactions.csv");
    if (!file.is_open()) {
        cout << "Failed to open file.\n";
        return;
    }
    file << "ID,Date,Amount,Category,Type\n"; // CSV headers
    for (int i = 0; i < transactioncount; i++) {
        file << transactions[i].id << ','
             << transactions[i].date << ','
             << transactions[i].amount << ','
             << transactions[i].category << ','
             << transactions[i].type << '\n';
    }
    file.close();
    cout << "Data exported to transactions.csv\n";
}

int main() {
    int choice;
    do {
        cout << "1. Add Transaction\n"
             << "2. Delete Transaction\n"
             << "3. View Transactions\n"
             << "4. Update Transaction\n"
             << "5. Generate Summary\n"
             << "6. Category-wise Summary\n"
             << "7. Monthly Report\n"
             << "8. Set Budget\n"
             << "9. Track Budget\n"
             << "10. Export Data\n"
             << "11. Exit\n"
             << "Choose an option: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character after choice input

        if (choice == 1) {
            string date, category, type;
            double amount;
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter amount: ";
            cin >> amount;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter type (income/expense): ";
            cin >> type;
            addtransaction(date, amount, category, type);
        } else if (choice == 2) {
            int id;
            cout << "Enter transaction ID to delete: ";
            cin >> id;
            deletetransaction(id);
        } else if (choice == 3) {
            view();
        } else if (choice == 4) {
            int id;
            string newdate, newcategory, newtype;
            double newamount;
            cout << "Enter transaction ID to update: ";
            cin >> id;
            cout << "Enter new date (YYYY-MM-DD): ";
            cin >> newdate;
            cout << "Enter new amount: ";
            cin >> newamount;
            cout << "Enter new category: ";
            cin >> newcategory;
            cout << "Enter new type (income/expense): ";
            cin >> newtype;
            update(id, newdate, newamount, newcategory, newtype);
        } else if (choice == 5) {
            summary();
        } else if (choice == 6) {
            categorysummary();
        } else if (choice == 7) {
            int month, year;
            cout << "Enter month (1-12): ";
            cin >> month;
            cout << "Enter year (YYYY): ";
            cin >> year;
            monthlyreport(month, year);
        } else if (choice == 8) {
            string category;
            double budget;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter budget: ";
            cin >> budget;
            setbudget(category, budget);
        } else if (choice == 9) {
            trackbudget();
        } else if (choice == 10) {
            exportdata();
        } else if (choice == 11) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 11);

    return 0;
}
