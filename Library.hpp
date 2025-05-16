#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Book.hpp"
#include "User.hpp"

class Library
{
    std::vector<Book> books;
    std::vector<User> users;

private:
    int userID = 1;

public:
    int addBook(int bookID, std::string bookTitle, std::string bookAuthor, std::ofstream& booksFile, bool isAvailable = true);
    void removeBook(int id);
    void displayBooks();
    void issueBook(int bookID, int userID);
    void returnBook(int bookID);
    int addUser(std::string userName , int userID, std::ofstream& usersFile);
    void displayUsers();
};