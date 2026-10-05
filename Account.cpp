#include "Account.h"

using namespace std;

// ---------- static members: defined exactly once, here ----------
int Account::totalAccounts = 0;
int Account::nextAccountNumber = 1001;

const double SavingsAccount::MIN_BALANCE = 1000.0;
const double CurrentAccount::OVERDRAFT_LIMIT = 10000.0;

// ======================= Account =======================

Account::Account(int customerId, double openingBalance) {
    accountNumber = nextAccountNumber;
    nextAccountNumber++;
    this->customerId = customerId;
    balance = openingBalance;
    totalAccounts++;
}

// Used when loading from file: keep the saved number, and make sure the
// next new account gets a higher number than any loaded one.
Account::Account(int accountNumber, int customerId, double balance) {
    this->accountNumber = accountNumber;
    if (accountNumber >= nextAccountNumber) {
        nextAccountNumber = accountNumber + 1;
    }
    this->customerId = customerId;
    this->balance = balance;
    totalAccounts++;
}

Account::~Account() {
    totalAccounts--;
}

int Account::getAccountNumber() const {
    return accountNumber;
}

int Account::getCustomerId() const {
    return customerId;
}

double Account::getBalance() const {
    return balance;
}

bool Account::deposit(double amount) {
    if (amount <= 0) {
        return false;
    }
    balance = balance + amount;
    return true;
}

// Default rule: cannot withdraw more than the balance.
bool Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }
    balance = balance - amount;
    return true;
}

int Account::getTotalAccounts() {
    return totalAccounts;
}

// One account is "less than" another if it has less money.
bool Account::operator<(const Account& other) const {
    return balance < other.balance;
}

// Friend function: it is NOT a member of Account, but because Account
// declared it a friend, it may read the protected members directly.
// type() is virtual, so "Savings" or "Current" is printed correctly.
ostream& operator<<(ostream& out, const Account& acc) {
    out << "Acc " << acc.accountNumber
        << " | " << acc.type()
        << " | Balance Rs. " << acc.balance;
    return out;
}

// ======================= SavingsAccount =======================

// The base-class constructor runs first (member initialiser list).
SavingsAccount::SavingsAccount(int customerId, double openingBalance)
    : Account(customerId, openingBalance) {
}

SavingsAccount::SavingsAccount(int accountNumber, int customerId, double balance)
    : Account(accountNumber, customerId, balance) {
}

// Overrides Account::withdraw - balance must stay >= MIN_BALANCE.
bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0) {
        return false;
    }
    if (balance - amount < MIN_BALANCE) {
        return false;
    }
    balance = balance - amount;
    return true;
}

double SavingsAccount::interestRate() const {
    return 4.0;   // percent per year
}

string SavingsAccount::type() const {
    return "Savings";
}

// ======================= CurrentAccount =======================

CurrentAccount::CurrentAccount(int customerId, double openingBalance)
    : Account(customerId, openingBalance) {
}

CurrentAccount::CurrentAccount(int accountNumber, int customerId, double balance)
    : Account(accountNumber, customerId, balance) {
}

// Overrides Account::withdraw - balance may go down to -OVERDRAFT_LIMIT.
bool CurrentAccount::withdraw(double amount) {
    if (amount <= 0) {
        return false;
    }
    if (balance - amount < -OVERDRAFT_LIMIT) {
        return false;
    }
    balance = balance - amount;
    return true;
}

double CurrentAccount::interestRate() const {
    return 0.0;   // current accounts earn no interest
}

string CurrentAccount::type() const {
    return "Current";
}
