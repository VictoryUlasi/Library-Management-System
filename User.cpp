#include <iostream>
#include <vector>
#include <string>
#include "libclass.hpp"

using namespace std;

User::User(string userName, int userID)
    : userName(userName), userID(userID) {}

int User::getUserID() const
{
    return userID;
}
string User::getUsername() const
{
    return userName;
}
void User::issueUserBook(int bookID)
{
    borrowedBook.push_back(bookID);
}
vector<int> User::getBorrowedBook()
{
    return borrowedBook;
}