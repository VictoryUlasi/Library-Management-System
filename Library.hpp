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