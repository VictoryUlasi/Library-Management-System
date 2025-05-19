#include <iostream>
#include <string>
#include "libclass.hpp"

using namespace std;

Book::Book(int bookID, string bookTitle, string bookAuthor, bool isAvailable)
    : bookID(bookID), bookTitle(bookTitle), bookAuthor(bookAuthor), isAvailable(isAvailable) {}

int Book::getID() const
{
    return bookID;
}
string Book::getTitle()
{
    return bookTitle;
}
string Book::getAuthor()
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
int Book::getUserBook() const
{
    return userBook;
}
void Book::setUserBook(int userID)
{
    userBook = userID;
}