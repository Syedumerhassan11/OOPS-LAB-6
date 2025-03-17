#include <iostream>
#include <string>
using namespace std;

// Base class: Student
class Student {
protected:
    int id;
    string name;

public:
    void getStudentDetails(int i, const string& n) {
        id = i;
        name = n;
    }

    void displayStudentDetails() const {
        cout << "Student ID: " << id << "\n";
        cout << "Name: " << name << "\n";
    }
};

// Derived class: Marks
class Marks : public Student {
protected:
    int marks_oop, marks_pf, marks_ds, marks_db;

public:
    void getMarks(int oop, int pf, int ds, int db) {
        marks_oop = oop;
        marks_pf = pf;
        marks_ds = ds;
        marks_db = db;
    }

    void displayMarks() const {
        cout << "Marks in OOP: " << marks_oop << "\n";
        cout << "Marks in PF: " << marks_pf << "\n";
        cout << "Marks in DS: " << marks_ds << "\n";
        cout << "Marks in DB: " << marks_db << "\n";
    }
};

// Derived class: Result
class Result : public Marks {
private:
    int total_marks;
    double avg_marks;

public:
    void calculateResult() {
        total_marks = marks_oop + marks_pf + marks_ds + marks_db;
        avg_marks = total_marks / 4.0;
    }

    void displayResult() const {
        cout << "Total Marks: " << total_marks << "\n";
        cout << "Average Marks: " << avg_marks << "\n";
    }
};

int main() {
    Result student;

    // Input data
    student.getStudentDetails(101, "Alice");
    student.getMarks(85, 90, 78, 88);

    // Calculate result
    student.calculateResult();

    // Display data
    student.displayStudentDetails();
    student.displayMarks();
    student.displayResult();

    return 0;
}
