#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    bool isBorrowed;
    Book* next;
};

Book* head = nullptr;
stack<Book*> undoStack;

void addBook() {
    Book* b = new Book;
    cout << "Enter title: ";
    cin.ignore(); getline(cin, b->title);
    cout << "Enter author: ";
    getline(cin, b->author);
    b->isBorrowed = false;
    b->next = head;
    head = b;
    cout << "Book added!\n";
}

void borrowBook() {
    string title;
    cout << "Enter title to borrow: ";
    cin.ignore(); getline(cin, title);
    Book* temp = head;
    while (temp) {
        if (temp->title == title && !temp->isBorrowed) {
            temp->isBorrowed = true;
            undoStack.push(temp);
            cout << "Borrowed: " << temp->title << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Book not available.\n";
}

void returnBook() {
    string title;
    cout << "Enter title to return: ";
    cin.ignore(); getline(cin, title);
    Book* temp = head;
    while (temp) {
        if (temp->title == title && temp->isBorrowed) {
            temp->isBorrowed = false;
            undoStack.push(temp);
            cout << "Returned: " << temp->title << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Book not found or not borrowed.\n";
}

void undoAction() {
    if (!undoStack.empty()) {
        Book* b = undoStack.top(); undoStack.pop();
        b->isBorrowed = !b->isBorrowed;
        cout << "Undo: " << (b->isBorrowed ? "Borrowed" : "Returned") << " \"" << b->title << "\"\n";
    } else {
        cout << "No actions to undo.\n";
    }
}

void searchBook() {
    string keyword;
    cout << "Enter title or author keyword: ";
    cin.ignore(); getline(cin, keyword);
    Book* temp = head;
    while (temp) {
        if (temp->title.find(keyword) != string::npos || temp->author.find(keyword) != string::npos)
            cout << temp->title << " by " << temp->author << (temp->isBorrowed ? " [Borrowed]" : "") << endl;
        temp = temp->next;
    }
}

int main() {
    int choice;
    do {
        cout << "\n1. Add Book\n2. Borrow Book\n3. Return Book\n4. Undo\n5. Search\n6. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) addBook();
        else if (choice == 2) borrowBook();
        else if (choice == 3) returnBook();
        else if (choice == 4) undoAction();
        else if (choice == 5) searchBook();
    } while (choice != 6);
    return 0;
}
