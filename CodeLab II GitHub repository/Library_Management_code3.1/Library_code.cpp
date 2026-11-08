/*
 * Coding Challenge 3 - Library Book Management System
 * Loads books from bookData.txt, lets the user view, search, borrow
 * and return books, then saves changes back to the file.
 * File format: title,author,pages,id,available
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Represents a single book
class Book {
private:
    string title, author, id;   // id is a string to keep leading zeros ("001")
    int pages;
    bool available;

public:
    Book(string t, string a, int p, string i, bool av)
        : title(t), author(a), id(i), pages(p), available(av) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getId() const { return id; }

    // Change status; returns false if the book is already in that state
    bool borrow()   { if (!available) return false; available = false; return true; }
    bool giveBack() { if (available)  return false; available = true;  return true; }

    void display() const {
        cout << id << " | " << title << " by " << author << " | " << pages
             << " pages | " << (available ? "Available" : "On loan") << '\n';
    }

    string toFileLine() const {
        return title + "," + author + "," + to_string(pages) + "," + id + "," +
               (available ? "true" : "false");
    }
};

// Reads each line of the file and splits it into a Book
vector<Book> loadBooks(const string& filename) {
    vector<Book> books;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, pages, id, avail;
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pages, ',');
        getline(ss, id, ',');
        getline(ss, avail);
        if (!avail.empty() && avail.back() == '\r') avail.pop_back(); // Windows line endings
        books.push_back(Book(title, author, stoi(pages), id, avail == "true"));
    }
    return books;
}

// Overwrites the file with the current book list
void saveBooks(const string& filename, const vector<Book>& books) {
    ofstream file(filename);
    for (const Book& b : books) file << b.toFileLine() << '\n';
}

// Returns a pointer to the matching book, or nullptr if none
Book* findById(vector<Book>& books, const string& id) {
    for (Book& b : books)
        if (b.getId() == id) return &b;
    return nullptr;
}

int main() {
    const string FILE_NAME = "bookData.txt";
    vector<Book> books = loadBooks(FILE_NAME);

    if (books.empty()) {
        cout << "Could not load " << FILE_NAME << '\n';
        return 1;
    }

    string choice;
    do {
        cout << "\n1. Display all  2. Search  3. Borrow  4. Return  0. Save & exit\nChoice: ";
        getline(cin, choice);

        if (choice == "1") {
            for (const Book& b : books) b.display();
        }
        else if (choice == "2") {
            string term;
            cout << "Search title or author: ";
            getline(cin, term);
            bool found = false;
            for (const Book& b : books) {
                if (b.getTitle().find(term) != string::npos ||
                    b.getAuthor().find(term) != string::npos) {
                    b.display();
                    found = true;
                }
            }
            if (!found) cout << "No matches.\n";
        }
        else if (choice == "3" || choice == "4") {
            string id;
            cout << "Book ID: ";
            getline(cin, id);
            Book* b = findById(books, id);

            if (!b) cout << "No book with that ID.\n";
            else if (choice == "3")
                cout << (b->borrow() ? "Borrowed: " : "Already on loan: ") << b->getTitle() << '\n';
            else
                cout << (b->giveBack() ? "Returned: " : "Not on loan: ") << b->getTitle() << '\n';
        }
        else if (choice != "0") {
            cout << "Invalid option.\n";
        }
    } while (choice != "0");

    saveBooks(FILE_NAME, books);
    cout << "Saved. Goodbye!\n";
    return 0;
}
