#include <iostream>
#include <vector>
#include <memory>

// Base class for Books
class Book {
protected:
    std::string genre;

public:
    Book(const std::string& gen) : genre(gen) {}
    virtual ~Book() {}

    virtual void displayDetails() const = 0;
};

// Derived class for Novel
class Novel : public Book {
private:
    std::string title;
    std::string author;

public:
    Novel(const std::string& t, const std::string& a)
        : Book("Novel"), title(t), author(a) {}

    void displayDetails() const override {
        std::cout << "Genre: " << genre << "\n"
                  << "Title: " << title << "\n"
                  << "Author: " << author << "\n\n";
    }
};

// Derived class for Mystery
class Mystery : public Book {
private:
    std::string title;
    std::string author;

public:
    Mystery(const std::string& t, const std::string& a)
        : Book("Mystery"), title(t), author(a) {}

    void displayDetails() const override {
        std::cout << "Genre: " << genre << "\n"
                  << "Title: " << title << "\n"
                  << "Author: " << author << "\n\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Book>> library;

    library.push_back(std::make_unique<Novel>("Pride and Prejudice", "Jane Austen"));
    library.push_back(std::make_unique<Mystery>("Sherlock Holmes", "Arthur Conan Doyle"));

    // Display details of all books
    for (const auto& book : library) {
        book->displayDetails();
    }

    return 0;
}

