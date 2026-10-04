#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <string>
#include "Bank.h"

// ---------------------------------------------------------------
// FileStorage : saves the Bank to text files and loads it back. (M5)
//   customers.txt - one customer per line:  id,phone,name
//   accounts.txt  - one account per line:   number,customerId,type,balance
// Like Bank, it never prints anything - it returns true/false.
//
// M5 in progress: transactions are not saved yet (next step).
// ---------------------------------------------------------------
class FileStorage {
private:
    std::string customersFile;
    std::string accountsFile;

    bool loadCustomers(Bank& bank);
    bool loadAccounts(Bank& bank);

    bool saveCustomers(const Bank& bank);
    bool saveAccounts(const Bank& bank);

public:
    FileStorage();

    // Returns false if a file had badly formed data.
    bool loadAll(Bank& bank);

    // Returns false if a file could not be written.
    bool saveAll(const Bank& bank);
};

#endif
