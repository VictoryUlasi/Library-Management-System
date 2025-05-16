#include <iostream>
#include<vector>
#include "User.hpp"


    User::User(std::string userName, int userID)
        : userName(userName), userID(userID) {}

    int User::getUserID() const
    {
        return userID;
    }
    std::string User::getUsername() const
    {
        return userName;
    }

    void User::issueUserBook(int bookID)
    {
        borrowedBook.push_back(bookID);
    }