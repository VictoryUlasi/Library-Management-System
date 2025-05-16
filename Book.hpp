#pragma once

#include <string>

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