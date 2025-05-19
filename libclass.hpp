#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>

// ---- Book Class ----
class Book{
    private:
    int bookID;
    std::string bookTitle;
    std::string bookAuthor;
    bool isAvailable;
    int userBook = 0;

    public:
    Book(int bookID, std::string bookTitle, std::string bookAuthor, bool isAvailable);

    int getID() const;
    std::string getTitle();
    std::string getAuthor();
    bool getAvailability();
    void setAvailability(bool);
    int getUserBook() const;
    void setUserBook(int);
};

// ---- User Class ----
class User
{
private:
    std::string userName;
    int userID;
    std::vector<int> borrowedBook;

public:
    User(std::string userName, int userID);

    int getUserID() const;
    std::string getUsername() const;
    void issueUserBook(int bookID);
    std::vector<int> getBorrowedBook();
};

// ---- Library Class ----
class Library
{
    std::vector<Book> books;
    std::vector<User> users;

private:
    int userID = 1;

public:
    int addBook(int bookID, std::string bookTitle, std::string bookAuthor, std::ofstream& oBooksFile, bool isAvailable = true);
    void initBooks(std::ifstream& iBooksFile);
    void removeBook(int id);
    void displayBooks(std::ifstream& iBooksFile);
    void issueBook(int bookID, int userID);
    void returnBook(int bookID);
    int addUser(std::string userName , int userID, std::ofstream& oUsersFile);
    void initUsers(std::ifstream& iUsersFile);
    void displayUsers(std::ifstream& iUsersFile);
};