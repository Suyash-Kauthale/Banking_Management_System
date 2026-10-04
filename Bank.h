#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include "Account.h"
#include "Customer.h"
#include "Transaction.h"

// Account type codes used by openAccount()
const int SAVINGS = 1;
const int CURRENT = 2;

// ---------------------------------------------------------------
// Bank : owns all customers, accounts and transactions, and
// contains the banking logic. Like Account, it never prints anything.
// ---------------------------------------------------------------
class Bank {
private:
    std::string bankName;
    std::vector<Customer*> customers;        
    std::vector<Account*> accounts;
    std::vector<Transaction> transactions;   // every money movement

    void recordTransaction(int accountNumber, std::string type, double amount, double balanceAfter);

public:
    Bank(std::string name);
    ~Bank();
/*
    ----- customers \ -----
    Returns the new customer ID, or -1 if the name is empty
    or the phone is not exactly 10 digits.
*/
    int addCustomer(std::string name, std::string phone);
    Customer* findCustomer(int customerId) const;
    int getCustomerCount() const;
    Customer* getCustomerAt(int index) const;

    // ----- accounts -----
    // Returns the new account number, or -1 if the request is invalid.
    int openAccount(int customerId, int accountType, double openingBalance);

    // Returns NULL if no account has that number.
    Account* findAccount(int accountNumber) const;

    bool deposit(int accountNumber, double amount);
    bool withdraw(int accountNumber, double amount);
    bool transfer(int fromNumber, int toNumber, double amount);

    // ----- reports -----
    std::string getBankName() const;
    int getAccountCount() const;
    Account* getAccountAt(int index) const;
    double getTotalBalance() const;
    int getTransactionCount() const;

    // M3: last n transactions of one account, newest first
    std::vector<Transaction> getMiniStatement(int accountNumber, int n) const;

    // M4: a copy of the account list sorted by balance, lowest first
    std::vector<Account*> getAccountsSortedByBalance() const;

    // ----- used only by the storage layer (M5) -----
    // These put back saved data exactly as it was. They do NOT record
    // new transactions, because nothing new is happening.
    bool restoreCustomer(int customerId, std::string name, std::string phone);
    bool restoreAccount(int accountNumber, int customerId, int accountType, double balance);
};

#endif
