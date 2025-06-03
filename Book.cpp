#include <iostream>
#include <string>
#include "libclass.hpp"

using namespace std;

Book::Book(int bookID, string bookTitle, string bookAuthor, bool isAvailable, int userBook)
    : bookID(bookID), bookTitle(bookTitle), bookAuthor(bookAuthor), isAvailable(isAvailable), userBook(userBook) {}

int Book::getID() const
{
    return bookID;
}
string Book::getTitle() const
{
    return bookTitle;
}
string Book::getAuthor() const
{
    return bookAuthor;
}
bool Book::getAvailability() const
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