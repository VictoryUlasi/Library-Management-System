#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

// ---- Book Class ----
class Book{
    private:
    int bookID;
    string bookTitle;
    string bookAuthor;
    bool isAvailable;
    int userBook;

    public:
    Book(int bookID, string bookTitle, string bookAuthor, bool isAvailable = true , int userBook = 0);

    int getID() const;
    string getTitle() const;
    string getAuthor() const;
    bool getAvailability() const;
    void setAvailability(bool);
    int getUserBook() const;
    void setUserBook(int);
};

// ---- User Class ----
class User
{
private:
    string userName;
    int userID;
    vector<int> borrowedBook;

public:
    User(string userName, int userID);

    int getUserID() const;
    string getUsername() const;
    void issueUserBook(int bookID);
    vector<int> getBorrowedBook();
};

// ---- Library Class ----
class Library
{
    vector<Book> books;
    vector<User> users;

private:
    int userID = 1;

public:
    void initBooks(ifstream& iBooksFile);
    int addBook(int bookID, string bookTitle, string bookAuthor, ofstream& oBooksFile);
    void removeBook(int id, ofstream& oBooksFile);
    void displayBooks(ifstream& iBooksFile);
    void issueBook(int bookID, int userID, ofstream& oBooksFile);
    void returnBook(int bookID, ofstream& oBooksFile);
    void searchBook(string bookName);
    void initUsers(ifstream& iUsersFile);
    int addUser(string userName , int userID, ofstream& oUsersFile);
    void displayUsers(ifstream& iUsersFile);
    void removeUser(int id, ofstream& oUsersFile);
    void refresh(ofstream& oBooksFile);
};