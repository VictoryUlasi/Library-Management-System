#pragma once

#include <string>
#include <vector>

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

