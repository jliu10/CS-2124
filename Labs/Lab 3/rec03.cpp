/*
  rec03_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
    string name;
    int number;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
class Account2 {
public:
    Account2(const string& iname, int inumber) : name(iname), number(inumber){}

    const string& getName() const {
      return name;
    }

    int const getNumber() const {
      return number;
    }
    friend ostream& operator<<(ostream& os, const Account2& account);

private:
    string name;
    int number;
};

ostream& operator<<(ostream& os, const Account2& account) {
    // os << "Account2: Name = " << account.getName() << ", Number = " << account.getNumber() << endl;
    os << "Account2: Name = " << account.name << ", Number = " << account.number;
    return os;
}

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
class Transaction {
public:
    Transaction(bool iIsDeposit, int iAmount) : isDeposit(iIsDeposit), amount(iAmount) {}

    friend ostream& operator<<(ostream& os, const Transaction& transaction);
private:
    bool isDeposit;
    int amount;
};

class Account3 {
public:
    Account3(const string& iname, int inumber) : name(iname), number(inumber){}

    const string& getName() const {
      return name;
    }

    int const getNumber() const  {
      return number;
    }
    friend ostream& operator<<(ostream& os, const Account3& account);
    void deposit(int amount) {
        transactions.emplace_back(true, amount);
        balance += amount;
    }
    void withdrawal(int amount) {
        transactions.emplace_back(false, amount);
        if (balance - amount >= 0) {
            balance -= amount;
        } else {
          cerr << "Failed to withdraw " << amount << " from Account3 " << number << endl;
        }
    }

private:
    string name;
    int number;
    vector<Transaction> transactions;
    int balance;
};

ostream& operator<<(ostream& os, const Account3& account) {
    os << "Account3: Name = " << account.name << ", Number = " << account.number << endl;
    for (const Transaction& transaction : account.transactions) {
        os << "\t" << transaction;
        // os << "\t\tBalance = " << account.balance << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const Transaction& transaction) {
    string type;
    if (transaction.isDeposit) {
        type = "Deposit";
    } else {
        type = "Withdrawal";
    }
    os << "Transaction: " << type << " of " << transaction.amount << endl;
    return os;
}

// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)
class Account4 {
    friend ostream& operator<<(ostream& os, const Account4& account);
public:
    class Transaction2 {
        friend ostream& operator<<(ostream& os, const Transaction2& transaction);
    public:
        Transaction2(bool iIsDeposit, int iAmount) : isDeposit(iIsDeposit), amount(iAmount) {}
    private:
        bool isDeposit;
        int amount;
    };

    friend ostream& operator<<(ostream& os, const Account4::Transaction2& transaction);
    
    Account4(const string& iname, int inumber) : name(iname), number(inumber){}

    const string& getName() const {
      return name;
    }

    int const getNumber() const {
      return number;
    }
    void deposit(int amount) {
        transactions.emplace_back(true, amount);
        balance += amount;
    }
    void withdrawal(int amount) {
        transactions.emplace_back(false, amount);
        if (balance - amount >= 0) {
            balance -= amount;
        } else {
          cerr << "Failed to withdraw " << amount << " from Account4 " << number << endl;
        }
    }

private:
    string name;
    int number;
    vector<Transaction2> transactions;
    int balance;
};

ostream& operator<<(ostream& os, const Account4& account) {
    os << "Account4: Name = " << account.name << ", Number = " << account.number << endl;
    for (const Account4::Transaction2& transaction : account.transactions) {
        os << "\t" << transaction;
        // os << "\t\tBalance = " << account.balance << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const Account4::Transaction2& transaction) {
    string type;
    if (transaction.isDeposit) {
        type = "Deposit";
    } else {
        type = "Withdrawal";
    }
    os << "Transaction: " << type << " of " << transaction.amount << endl;
    return os;
}


// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)


int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream ifs("accounts.txt");
    if (!ifs) {
        cerr << "Failed to open accounts.txt";
        exit(1);
    }
    vector<Account> accounts;
    string name;
    int number;
    while(ifs >> name >> number) {
        Account account;
        account.name = name;
        account.number = number;
        accounts.push_back(account);
    }
    ifs.close();
    for (const Account& account : accounts) {
      cout << "Account: Name = " << account.name << ", Number = " << account.number << endl;
    }
    cout << endl;


    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accounts.clear();
    ifs.open("accounts.txt");
    if (!ifs) {
        cerr << "Failed to open accounts.txt";
        exit(1);
    }
    while(ifs >> name >> number) {
        Account account = {name, number};
        accounts.push_back(account);
    }
    ifs.close();
    for (const Account& account : accounts) {
      cout << "Account: Name = " << account.name << ", Number = " << account.number << endl;
    }
    cout << endl;


    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    vector<Account2> accounts2;
    ifs.open("accounts.txt");
    if (!ifs) {
        cerr << "Failed to open accounts.txt";
        exit(1);
    }
    while(ifs >> name >> number) {
        Account2 account(name, number);
        accounts2.push_back(account);
    }
    ifs.close();
    for (const Account2& account : accounts2) {
      cout << "Account2: Name = " << account.getName() << ", Number = " << account.getNumber() << endl;
    }
    cout << endl;


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    accounts2.clear();
    ifs.open("accounts.txt");
    if (!ifs) {
        cerr << "Failed to open accounts.txt";
        exit(1);
    }
    while(ifs >> name >> number) {
        Account2 account(name, number);
        accounts2.push_back(account);
    }
    ifs.close();
    for (const Account2& account : accounts2) {
      cout << account << endl;
    }
    cout << endl;


    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    accounts2.clear();
    ifs.open("accounts.txt");
    if (!ifs) {
        cerr << "Failed to open accounts.txt";
        exit(1);
    }
    while(ifs >> name >> number) {
        Account2 account(name, number);
        accounts2.push_back(account);
    }
    ifs.close();
    for (const Account2& account : accounts2) {
      cout << account << endl;
    }
    cout << endl;


    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    accounts2.clear();
    ifs.open("accounts.txt");
    if (!ifs) {
        cerr << "Failed to open accounts.txt";
        exit(1);
    }
    while(ifs >> name >> number) {
        accounts2.push_back(Account2(name, number));
    }
    ifs.close();
    for (const Account2& account : accounts2) {
      cout << account << endl;
    }
    cout << endl;

    
    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    accounts2.clear();
    ifs.open("accounts.txt");
    if (!ifs) {
        cerr << "Failed to open accounts.txt";
        exit(1);
    }
    while(ifs >> name >> number) {
        accounts2.emplace_back(name, number);
    }
    ifs.close();
    for (const Account2& account : accounts2) {
      cout << account << endl;
    }
    cout << endl;

    
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
    ifs.open("transactions.txt");
    if (!ifs) {
        cerr << "Failed to open transactions.txt";
        exit(1);
    }
    vector<Account3> accounts3;
    string command;
    int amount;
    while(ifs >> command) {
        if (command == "Account") {
            ifs >> name >> number;
            accounts3.emplace_back(name, number);
        } else {
            ifs >> number >> amount;
            size_t i = 0;
            while (i < accounts3.size()) {
                if (accounts3[i].getNumber() == number) {
                    break;
                }
                i++;
            }
            if (command == "Deposit") {
                accounts3[i].deposit(amount);
            } else if (command == "Withdraw") {
                accounts3[i].withdrawal(amount);
            }
        }
    }
    ifs.close();
    for (const Account3& account : accounts3) {
      cout << account << endl;
    }
    cout << endl;


    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
    ifs.open("transactions.txt");
    if (!ifs) {
        cerr << "Failed to open transactions.txt";
        exit(1);
    }
    vector<Account4> accounts4;
    while(ifs >> command) {
        if (command == "Account") {
            ifs >> name >> number;
            accounts4.emplace_back(name, number);
        } else {
            ifs >> number >> amount;
            size_t i = 0;
            while (i < accounts4.size()) {
                if (accounts4[i].getNumber() == number) {
                    break;
                }
                i++;
            }
            if (command == "Deposit") {
                accounts4[i].deposit(amount);
            } else if (command == "Withdraw") {
                accounts4[i].withdrawal(amount);
            }
        }
    }
    ifs.close();
    for (Account4& account : accounts4) {
      cout << account << endl;
    }
    cout << endl;


    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

    
}
