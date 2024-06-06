#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
public:
    std::string title;
    std::string author;
    std::string isbn;
    int year;
    bool borrowed;

    Book(std::string t, std::string a, std::string i, int y)
        : title(t), author(a), isbn(i), year(y), borrowed(false) {}
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const std::string& title, const std::string& author, const std::string& isbn, int year) {
        books.push_back(Book(title, author, isbn, year));
        std::cout << "Book '" << title << "' added successfully." << std::endl;
    }

    void viewBooks() const {
        if (books.empty()) {
            std::cout << "No books available in the library." << std::endl;
        } else {
            for (const auto& book : books) {
                std::string status = book.borrowed ? "Borrowed" : "Available";
                std::cout << "Title: " << book.title << ", Author: " << book.author
                          << ", ISBN: " << book.isbn << ", Year: " << book.year
                          << ", Status: " << status << std::endl;
            }
        }
    }

    void searchBooks(const std::string& keyword) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(keyword) != std::string::npos || book.author.find(keyword) != std::string::npos) {
                found = true;
                std::string status = book.borrowed ? "Borrowed" : "Available";
                std::cout << "Title: " << book.title << ", Author: " << book.author
                          << ", ISBN: " << book.isbn << ", Year: " << book.year
                          << ", Status: " << status << std::endl;
            }
        }
        if (!found) {
            std::cout << "No books found for keyword: " << keyword << std::endl;
        }
    }

    void borrowBook(const std::string& title) {
        for (auto& book : books) {
            if (book.title == title && !book.borrowed) {
                book.borrowed = true;
                std::cout << "You have borrowed '" << title << "'." << std::endl;
                return;
            }
        }
        std::cout << "Book '" << title << "' is either not available or already borrowed." << std::endl;
    }

    void returnBook(const std::string& title) {
        for (auto& book : books) {
            if (book.title == title && book.borrowed) {
                book.borrowed = false;
                std::cout << "You have returned '" << title << "'." << std::endl;
                return;
            }
        }
        std::cout << "Book '" << title << "' was not borrowed or does not exist in the library." << std::endl;
    }
};

void displayMenu() {
    std::cout << "\nLibrary Menu:" << std::endl;
    std::cout << "1. Add New Book" << std::endl;
    std::cout << "2. View All Books" << std::endl;
    std::cout << "3. Search for a Book" << std::endl;
    std::cout << "4. Borrow a Book" << std::endl;
    std::cout << "5. Return a Book" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

int main() {
    Library library;
    int choice;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // To ignore the newline character after the choice input

        if (choice == 1) {
            std::string title, author, isbn;
            int year;

            std::cout << "Enter the title of the book: ";
            std::getline(std::cin, title);
            std::cout << "Enter the author of the book: ";
            std::getline(std::cin, author);
            std::cout << "Enter the ISBN of the book: ";
            std::getline(std::cin, isbn);
            std::cout << "Enter the publication year of the book: ";
            std::cin >> year;
            std::cin.ignore();

            library.addBook(title, author, isbn, year);
        } else if (choice == 2) {
            library.viewBooks();
        } else if (choice == 3) {
            std::string keyword;
            std::cout << "Enter the title or author to search: ";
            std::getline(std::cin, keyword);
            library.searchBooks(keyword);
        } else if (choice == 4) {
            std::string title;
            std::cout << "Enter the title of the book to borrow: ";
            std::getline(std::cin, title);
            library.borrowBook(title);
        } else if (choice == 5) {
            std::string title;
            std::cout << "Enter the title of the book to return: ";
            std::getline(std::cin, title);
            library.returnBook(title);
        } else if (choice == 6) {
            std::cout << "Exiting the library system. Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}