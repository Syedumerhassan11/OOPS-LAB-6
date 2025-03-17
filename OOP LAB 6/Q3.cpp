#include <iostream>
#include <vector>
#include <memory>

// Base Employee class
class Employee {
protected:
    int id;
    std::string name;

public:
    Employee(int empId, const std::string& empName) : id(empId), name(empName) {}
    virtual ~Employee() {}
    virtual void showInfo() const {
        std::cout << "ID: " << id << ", Name: " << name << "\n";
    }
};

// Interfaces
class IOrderTaker {
public:
    virtual void takeOrder(const std::string& order) = 0;
    virtual ~IOrderTaker() {}
};

class IOrderPreparer {
public:
    virtual void prepareOrder(const std::string& order) = 0;
    virtual ~IOrderPreparer() {}
};

class IBiller {
public:
    virtual void generateBill(double amount) = 0;
    virtual ~IBiller() {}
};

// Concrete Employee classes
class Waiter : public Employee, public IOrderTaker {
public:
    Waiter(int empId, const std::string& empName) : Employee(empId, empName) {}

    void takeOrder(const std::string& order) override {
        std::cout << "Waiter " << name << " takes order: " << order << "\n";
    }
};

class Chef : public Employee, public IOrderPreparer {
public:
    Chef(int empId, const std::string& empName) : Employee(empId, empName) {}

    void prepareOrder(const std::string& order) override {
        std::cout << "Chef " << name << " prepares: " << order << "\n";
    }
};

class Cashier : public Employee, public IBiller {
public:
    Cashier(int empId, const std::string& empName) : Employee(empId, empName) {}

    void generateBill(double amount) override {
        std::cout << "Cashier " << name << " generates bill: $" << amount << "\n";
    }
};

class Manager : public Employee, public IOrderTaker, public IBiller {
public:
    Manager(int empId, const std::string& empName) : Employee(empId, empName) {}

    void takeOrder(const std::string& order) override {
        std::cout << "Manager " << name << " takes order: " << order << "\n";
    }

    void generateBill(double amount) override {
        std::cout << "Manager " << name << " generates bill: $" << amount << "\n";
    }
};

// Menu base class
class Menu {
public:
    virtual double calculateTotal(double basePrice) const = 0;
    virtual ~Menu() {}
};

class FoodMenu : public Menu {
public:
    double calculateTotal(double basePrice) const override {
        return basePrice; // No extra taxes
    }
};

class BeverageMenu : public Menu {
public:
    double calculateTotal(double basePrice) const override {
        return basePrice * 1.1; // 10% beverage tax
    }
};

int main() {
    std::vector<std::unique_ptr<Employee>> employees;

    employees.push_back(std::make_unique<Waiter>(1, "Alice"));
    employees.push_back(std::make_unique<Chef>(2, "Bob"));
    employees.push_back(std::make_unique<Cashier>(3, "Charlie"));
    employees.push_back(std::make_unique<Manager>(4, "David"));

    // Demonstrate dynamic dispatch
    for (const auto& employee : employees) {
        employee->showInfo();
    }

    // Using interfaces
    IOrderTaker* orderTaker = dynamic_cast<IOrderTaker*>(employees[0].get());
    if (orderTaker) orderTaker->takeOrder("Pasta");

    IOrderPreparer* orderPreparer = dynamic_cast<IOrderPreparer*>(employees[1].get());
    if (orderPreparer) orderPreparer->prepareOrder("Pasta");

    IBiller* biller = dynamic_cast<IBiller*>(employees[2].get());
    if (biller) biller->generateBill(20.0);

    // Menu handling
    FoodMenu foodMenu;
    BeverageMenu beverageMenu;

    std::cout << "Food total: $" << foodMenu.calculateTotal(50.0) << "\n";
    std::cout << "Beverage total (with tax): $" << beverageMenu.calculateTotal(10.0) << "\n";

    return 0;
}
