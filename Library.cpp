#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include "Book.hpp"
#include "User.hpp"
#include "Library.hpp"

void Library::addBook(int bookID, std::string bookTitle, std::string bookAuthor, bool isAvailable)
{
    Book book(bookID, bookTitle, bookAuthor, isAvailable);
    books.push_back(book);
}

void Library::removeBook(int id)
{
    int bookPos = 0;
    for (const auto &i : books)
    {
        if (i.getID() == id)
        {
            books.erase(books.begin() + bookPos);
            break;
        }
        bookPos++;
    }
}

void Library::displayBooks()
{
    for (auto &i : books)
    {
        std::string username = "In House";

        for (auto &j : users)
        {
            if (j.getUserID() == i.getUserBook())
            {
                username = j.getUsername();
                break;
            }
        }
        std::cout << std::left << "ID: " << std::setw(10) << i.getID()
                  << " Title: " << std::setw(25) << i.getTitle()
                  << "\tAuthor: " << std::setw(10) << i.getAuthor()
                  << "\tAvail: " << std::setw(5) << ((i.getAvailability()) ? "In" : "Out")
                  << "\tCheckout: " << std::setw(20) << username << std::endl;
    }
}

void Library::issueBook(int bookID, int userID)
{
    for (auto &i : books)
    {
        if (i.getID() == bookID && i.getAvailability() == true)
        {
            for (auto &j : users)
            {
                if (j.getUserID() == userID)
                {
                    j.issueUserBook(bookID);
                    i.setAvailability(false);
                    i.setUserBook(userID);
                    std::cout << "Book Issued." << std::endl;
                    break;
                }
            }
        }
        else if (i.getID() == bookID && i.getAvailability() == false)
        {
            std::string username;
            for (auto &j : users)
            {
                if (j.getUserID() == i.getUserBook())
                {
                    username = j.getUsername();
                    break;
                }
            }
            std::cout << "Book Already Issued to " << username << std::endl;
            break;
        }
    }
}

void Library::returnBook(int bookID)
{
    for (auto &i : books)
    {
        if (i.getID() == bookID && i.getAvailability() == false)
        {
            i.setAvailability(true);
            i.setUserBook(0);
            std::cout << "Book Returned." << std::endl;
            break;
        }
        else if (i.getID() == bookID && i.getAvailability() == true)
        {
            std::cout << "Book Already In House " << std::endl;
            break;
        }
    }
}

int Library::addUser(std::string userName , int userID)
{
    User user(userName, userID);
    users.push_back(user);

    return 0;
}

void Library::displayUsers()
{
    for (const auto &i : users)
    {
        std::cout << "Name: " << i.getUsername() << "\tUserID: " << i.getUserID() << std::endl;
    }
}