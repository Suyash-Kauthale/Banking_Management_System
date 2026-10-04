# Bank Management System

CS2303 Object Oriented Programming — Course Project


## Build

**Windows:**
```
g++ -std=c++11 -Wall main.cpp Account.cpp Bank.cpp Customer.cpp Transaction.cpp Date.cpp FileStorage.cpp -o bank.exe
bank.exe
```
(In PowerShell, run it as `.\bank.exe`.)

**Linux / Mac:**
```
g++ -std=c++11 -Wall main.cpp Account.cpp Bank.cpp Customer.cpp Transaction.cpp Date.cpp FileStorage.cpp -o bank
./bank
```

Run it from the project folder: `customers.txt` and `accounts.txt` are created there.


## Files

| File | What is in it |
|---|---|
| `Account.h` / `.cpp` | `Account` (abstract), `SavingsAccount`, `CurrentAccount` |
| `Bank.h` / `.cpp` | holds customers, accounts and transactions; open / deposit / withdraw / transfer, mini statement, sorting |
| `Customer.h` / `.cpp` | a customer who can own several accounts |
| `Transaction.h` / `.cpp` | one record of money moving in or out |
| `Date.h` / `.cpp` | day / month / year with overloaded operators |
| `FileStorage.h` / `.cpp` | saves and loads customers and accounts as text files |
| `main.cpp` | the menu — all `cout` and `cin` live here |

`Account` and `Bank` contain **no `cout` and no `cin`**.
They return values, and `main.cpp` decides what to print.

## OOP concepts and where they are

| Concept | Where |
|---|---|
| Class, private data, public functions | `Account`, `Bank` |
| Constructor | `Account::Account()`, both child classes |
| Destructor | `Account::~Account()`, `Bank::~Bank()` |
| Static data member | `Account::totalAccounts` |
| Static member function | `Account::getTotalAccounts()` |
| Abstract class + pure virtual | `interestRate()`, `type()` in `Account` |
| Inheritance | `SavingsAccount` and `CurrentAccount` from `Account` |
| Function overriding | `withdraw()` in both child classes |
| Run-time polymorphism | `acc->withdraw()` in `Bank::withdraw()` and `Bank::transfer()` |
| Base class pointer | `vector<Account*>` in `Bank` |
| `new` and `delete` | `Bank::openAccount()` and `Bank::~Bank()` |

## Demo order

1. Option **1** — add a customer (gets ID 101)
2. Option **2** — open a Savings account (1001) with Rs 5000, and a Current account
3. Option **4**, `1001`, `5000` — **declined**, savings must keep Rs 1000
4. Option **5** — transfer between two accounts
5. Option **10** — mini statement for `1001`
6. Option **0**, then run the program again and choose **8** — the data is still there


## Not built yet

Binary file storage for transactions, login, Fixed Deposit accounts, exceptions.
