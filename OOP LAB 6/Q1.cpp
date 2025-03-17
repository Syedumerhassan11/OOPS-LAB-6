#include <iostream>
#include <vector>
#include <memory>

// Base class for BankAccount
class BankAccount {
protected:
    int accountNumber;
    double balance;

public:
    BankAccount(int accNum, double bal) : accountNumber(accNum), balance(bal) {}
    virtual ~BankAccount() {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient funds.\n";
        }
    }

    virtual void applyMonthlyInterest() {}

    virtual void displayBalance() const {
        std::cout << "Account Number: " << accountNumber << ", Balance: " << balance << "\n";
    }
};

// Derived classes for specific account types
class SavingsAccount : public BankAccount {
    double interestRate;

public:
    SavingsAccount(int accNum, double bal, double rate) : BankAccount(accNum, bal), interestRate(rate) {}

    void applyMonthlyInterest() override {
        balance += balance * interestRate;
    }
};

class CheckingAccount : public BankAccount {
    double overdraftLimit;

public:
    CheckingAccount(int accNum, double bal, double limit) : BankAccount(accNum, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (balance - amount >= -overdraftLimit) {
            balance -= amount;
            if (balance < 0) {
                std::cout << "Overdraft alert!\n";
            }
        } else {
            std::cout << "Overdraft limit exceeded.\n";
        }
    }
};

class BusinessAccount : public BankAccount {
    double taxRate;

public:
    BusinessAccount(int accNum, double bal, double tax) : BankAccount(accNum, bal), taxRate(tax) {}

    void deposit(double amount) override {
        double taxedAmount = amount * (1.0 - taxRate);
        balance += taxedAmount;
    }
};

// Base class for User Roles
class User {
public:
    virtual ~User() {}
    virtual void performDeposit(BankAccount& account, double amount) = 0;
    virtual void performWithdraw(BankAccount& account, double amount) = 0;
};

// Derived classes for roles
class Customer : public User {
public:
    void performDeposit(BankAccount& account, double amount) override {
        account.deposit(amount);
    }

    void performWithdraw(BankAccount& account, double amount) override {
        account.withdraw(amount);
    }
};

class Teller : public Customer {
public:
    void freezeAccount(BankAccount& account) {
        std::cout << "Account frozen.\n";
    }
};

class Manager : public Teller {
public:
    void adjustAccountLimit(BankAccount& account, double newBalance) {
        std::cout << "Manager overriding balance.\n";
    }
};

int main() {
    std::vector<std::unique_ptr<BankAccount>> accounts;
    accounts.push_back(std::make_unique<SavingsAccount>(101, 1000.0, 0.02));
    accounts.push_back(std::make_unique<CheckingAccount>(102, 500.0, 200.0));
    accounts.push_back(std::make_unique<BusinessAccount>(103, 2000.0, 0.1));

    Customer customer;
    Teller teller;
    Manager manager;

    for (auto& account : accounts) {
        account->displayBalance();
        customer.performDeposit(*account, 200);
        account->displayBalance();
        customer.performWithdraw(*account, 150);
        account->displayBalance();
        account->applyMonthlyInterest();
        account->displayBalance();
    }

    teller.freezeAccount(*accounts[0]);
    manager.adjustAccountLimit(*accounts[1], 10000.0);

    return 0;
}

