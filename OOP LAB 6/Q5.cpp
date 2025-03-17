#include <iostream>
#include <memory>

// Base class for Vehicles
class Vehicle {
protected:
    double price;

public:
    Vehicle(double p) : price(p) {}
    virtual ~Vehicle() {}
    virtual void displayDetails() const = 0;
};

// Derived class for Car
class Car : public Vehicle {
protected:
    int seatingCapacity;
    int numDoors;
    std::string fuelType;

public:
    Car(double p, int seats, int doors, const std::string& fuel)
        : Vehicle(p), seatingCapacity(seats), numDoors(doors), fuelType(fuel) {}
};

// Derived class for Motorcycle
class Motorcycle : public Vehicle {
protected:
    int numCylinders;
    int numGears;
    int numWheels;

public:
    Motorcycle(double p, int cylinders, int gears, int wheels)
        : Vehicle(p), numCylinders(cylinders), numGears(gears), numWheels(wheels) {}
};

// Derived class for Audi
class Audi : public Car {
private:
    std::string modelType;

public:
    Audi(double p, int seats, int doors, const std::string& fuel, const std::string& model)
        : Car(p, seats, doors, fuel), modelType(model) {}

    void displayDetails() const override {
        std::cout << "Audi Car Details:\n";
        std::cout << "Price: $" << price << "\n";
        std::cout << "Seating Capacity: " << seatingCapacity << "\n";
        std::cout << "Number of Doors: " << numDoors << "\n";
        std::cout << "Fuel Type: " << fuelType << "\n";
        std::cout << "Model Type: " << modelType << "\n\n";
    }
};

// Derived class for Yamaha
class Yamaha : public Motorcycle {
private:
    std::string makeType;

public:
    Yamaha(double p, int cylinders, int gears, int wheels, const std::string& make)
        : Motorcycle(p, cylinders, gears, wheels), makeType(make) {}

    void displayDetails() const override {
        std::cout << "Yamaha Motorcycle Details:\n";
        std::cout << "Price: $" << price << "\n";
        std::cout << "Number of Cylinders: " << numCylinders << "\n";
        std::cout << "Number of Gears: " << numGears << "\n";
        std::cout << "Number of Wheels: " << numWheels << "\n";
        std::cout << "Make Type: " << makeType << "\n\n";
    }
};

int main() {
    std::unique_ptr<Vehicle> audiCar = std::make_unique<Audi>(50000, 5, 4, "Petrol", "A6");
    std::unique_ptr<Vehicle> yamahaBike = std::make_unique<Yamaha>(15000, 2, 6, 2, "R1");

    audiCar->displayDetails();
    yamahaBike->displayDetails();

    return 0;
}

