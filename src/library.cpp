#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct Transaction {
    string type;
    float amount;
    string category;
    string date;
};

vector<Transaction> transactions;

void addTransaction() {
    Transaction t;
    cout << "Enter transaction type (income/expense): ";
    cin >> t.type;
    cout << "Enter amount: ";
    cin >> t.amount;
    cout << "Enter category: ";
    cin >> t.category;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> t.date;
    transactions.push_back(t);
    cout << "Transaction saved!\n";
}

void saveToFile() {
    ofstream file("transactions.txt");
    for (auto &t : transactions)
        file << t.type << " " << t.amount << " " << t.category << " " << t.date << endl;
    file.close();
}

void loadFromFile() {
    ifstream file("transactions.txt");
    Transaction t;
    while (file >> t.type >> t.amount >> t.category >> t.date)
        transactions.push_back(t);
    file.close();
}

void filterExpenses() {
    cout << "Expenses over ₹100:\n";
    for (auto &t : transactions)
        if (t.type == "expense" && t.amount > 100)
            cout << t.amount << " - " << t.category << " on " << t.date << endl;
}

int main() {
    loadFromFile();
    int choice;
    do {
        cout << "\n1. Add Transaction\n2. Filter Expenses\n3. Save & Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) addTransaction();
        else if (choice == 2) filterExpenses();
    } while (choice != 3);
    saveToFile();
    return 0;
}
