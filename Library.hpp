#pragma once

#include <string>
#include <vector>
#include <map>
#include "Book.hpp"
#include "User.hpp"

class Library
{
    std::vector<Book> books;
    std::vector<User> users;

private:
    int userID = 1;

public:
    void addBook(int bookID, std::string bookTitle, std::string bookAuthor, bool isAvailable = true);
    void removeBook(int id);
    void displayBooks();
    void issueBook(int bookID, int userID);
    void returnBook(int bookID);
    int addUser(std::string userName);
    void displayUsers();
};