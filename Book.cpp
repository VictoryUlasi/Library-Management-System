#include <iostream>
#include "Book.hpp"

    Book::Book(int bookID, std::string bookTitle, std::string bookAuthor, bool isAvailable)
        : bookID(bookID), bookTitle(bookTitle), bookAuthor(bookAuthor), isAvailable(isAvailable) {}

    int Book::getID() const
    {
        return bookID;
    }
    std::string Book::getTitle()
    {
        return bookTitle;
    }
    std::string Book::getAuthor()
    {
        return bookAuthor;
    }
    bool Book::getAvailability()
    {
        return isAvailable;
    }
    void Book::setAvailability(bool availability)
    {
        isAvailable = availability;
    }
    int Book::getUserBook() const{
        return userBook;
    }
    void Book::setUserBook(int userID){
        userBook = userID;
    }