#include "Customer.h"

using namespace std;

int Customer::nextCustomerId = 101;

Customer::Customer(string name, string phone) {
    customerId = nextCustomerId;
    nextCustomerId++;
    this->name = name;     // "this->" separates the member from the parameter
    this->phone = phone;
}

// Used when loading from file: keep the saved ID, and make sure the
// next new customer gets a higher ID than any loaded one.
Customer::Customer(int customerId, string name, string phone) {
    this->customerId = customerId;
    if (customerId >= nextCustomerId) {
        nextCustomerId = customerId + 1;
    }
    this->name = name;
    this->phone = phone;
}

int Customer::getCustomerId() const {
    return customerId;
}

string Customer::getName() const {
    return name;
}

string Customer::getPhone() const {
    return phone;
}

vector<int> Customer::getAccountNumbers() const {
    return accountNumbers;
}

void Customer::addAccount(int accountNumber) {
    accountNumbers.push_back(accountNumber);
}
