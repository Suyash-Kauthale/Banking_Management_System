#include "Bank.h"
#include <algorithm>

using namespace std;

Bank::Bank(string name) {
    bankName = name;
}

// The Bank created every customer and account with new,
// so the Bank deletes them.
Bank::~Bank() {
    for (int i = 0; i < (int)accounts.size(); i++) {
        delete accounts[i];
    }
    accounts.clear();

    for (int i = 0; i < (int)customers.size(); i++) {
        delete customers[i];
    }
    customers.clear();
}

void Bank::recordTransaction(int accountNumber, string type, double amount, double balanceAfter) {
    Transaction t(accountNumber, type, amount, balanceAfter);
    transactions.push_back(t);
}

// ======================= customers =======================

// A valid phone number is exactly 10 digits.
bool isValidPhone(string phone) {
    if (phone.length() != 10) {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return false;
        }
    }
    return true;
}

int Bank::addCustomer(string name, string phone) {
    if (name == "" || !isValidPhone(phone)) {
        return -1;
    }
    Customer* c = new Customer(name, phone);
    customers.push_back(c);
    return c->getCustomerId();
}

Customer* Bank::findCustomer(int customerId) const {
    for (int i = 0; i < (int)customers.size(); i++) {
        if (customers[i]->getCustomerId() == customerId) {
            return customers[i];
        }
    }
    return NULL;
}

int Bank::getCustomerCount() const {
    return (int)customers.size();
}

Customer* Bank::getCustomerAt(int index) const {
    if (index < 0 || index >= (int)customers.size()) {
        return NULL;
    }
    return customers[index];
}

// ======================= accounts =======================

int Bank::openAccount(int customerId, int accountType, double openingBalance) {
    Customer* owner = findCustomer(customerId);
    if (owner == NULL || openingBalance < 0) {
        return -1;
    }

    Account* acc = NULL;

    if (accountType == SAVINGS) {
        if (openingBalance < SavingsAccount::MIN_BALANCE) {
            return -1;
        }
        acc = new SavingsAccount(customerId, openingBalance);
    } else if (accountType == CURRENT) {
        acc = new CurrentAccount(customerId, openingBalance);
    } else {
        return -1;
    }

    accounts.push_back(acc);   // base-class pointer holds a derived object
    owner->addAccount(acc->getAccountNumber());
    recordTransaction(acc->getAccountNumber(), "Open", openingBalance, acc->getBalance());
    return acc->getAccountNumber();
}

Account* Bank::findAccount(int accountNumber) const {
    for (int i = 0; i < (int)accounts.size(); i++) {
        if (accounts[i]->getAccountNumber() == accountNumber) {
            return accounts[i];
        }
    }
    return NULL;
}

bool Bank::deposit(int accountNumber, double amount) {
    Account* acc = findAccount(accountNumber);
    if (acc == NULL) {
        return false;
    }
    if (!acc->deposit(amount)) {
        return false;
    }
    recordTransaction(accountNumber, "Deposit", amount, acc->getBalance());
    return true;
}

bool Bank::withdraw(int accountNumber, double amount) {
    Account* acc = findAccount(accountNumber);
    if (acc == NULL) {
        return false;
    }
    // Run-time polymorphism: Savings or Current withdraw() is chosen here.
    if (!acc->withdraw(amount)) {
        return false;
    }
    recordTransaction(accountNumber, "Withdraw", amount, acc->getBalance());
    return true;
}

bool Bank::transfer(int fromNumber, int toNumber, double amount) {
    if (fromNumber == toNumber) {
        return false;
    }

    Account* from = findAccount(fromNumber);
    Account* to = findAccount(toNumber);
    if (from == NULL || to == NULL) {
        return false;
    }

    // Step 1: take the money out.
    if (!from->withdraw(amount)) {
        return false;
    }

    // Step 2: put it in. If that fails, refund step 1 so no money is lost.
    if (!to->deposit(amount)) {
        from->deposit(amount);
        return false;
    }

    // Both halves worked, so record one entry on each account.
    recordTransaction(fromNumber, "Transfer Out", amount, from->getBalance());
    recordTransaction(toNumber, "Transfer In", amount, to->getBalance());
    return true;
}

// ======================= reports =======================

string Bank::getBankName() const {
    return bankName;
}

int Bank::getAccountCount() const {
    return (int)accounts.size();
}

Account* Bank::getAccountAt(int index) const {
    if (index < 0 || index >= (int)accounts.size()) {
        return NULL;
    }
    return accounts[index];
}

double Bank::getTotalBalance() const {
    double total = 0;
    for (int i = 0; i < (int)accounts.size(); i++) {
        total = total + accounts[i]->getBalance();
    }
    return total;
}

int Bank::getTransactionCount() const {
    return (int)transactions.size();
}

// Walk backwards from the newest transaction and collect up to n
// that belong to this account.
vector<Transaction> Bank::getMiniStatement(int accountNumber, int n) const {
    vector<Transaction> result;
    for (int i = (int)transactions.size() - 1; i >= 0; i--) {
        if ((int)result.size() == n) {
            break;
        }
        if (transactions[i].getAccountNumber() == accountNumber) {
            result.push_back(transactions[i]);
        }
    }
    return result;
}

// sort() on a vector of POINTERS would compare memory addresses,
// not balances. This helper dereferences both pointers so that
// Account::operator< is the one actually used.
bool compareByBalance(Account* a, Account* b) {
    return *a < *b;
}

vector<Account*> Bank::getAccountsSortedByBalance() const {
    vector<Account*> sorted = accounts;   // copy the pointers, not the accounts
    sort(sorted.begin(), sorted.end(), compareByBalance);
    return sorted;
}

// ======================= restore (M5) =======================

bool Bank::restoreCustomer(int customerId, string name, string phone) {
    if (findCustomer(customerId) != NULL) {
        return false;   // duplicate ID in the file
    }
    customers.push_back(new Customer(customerId, name, phone));
    return true;
}

bool Bank::restoreAccount(int accountNumber, int customerId, int accountType, double balance) {
    Customer* owner = findCustomer(customerId);
    if (owner == NULL || findAccount(accountNumber) != NULL) {
        return false;   // unknown owner, or duplicate account number
    }

    Account* acc = NULL;
    if (accountType == SAVINGS) {
        acc = new SavingsAccount(accountNumber, customerId, balance);
    } else if (accountType == CURRENT) {
        acc = new CurrentAccount(accountNumber, customerId, balance);
    } else {
        return false;
    }

    accounts.push_back(acc);
    owner->addAccount(accountNumber);   // rebuild the customer's account list
    return true;
}
