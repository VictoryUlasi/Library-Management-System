#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include "libclass.hpp"

using namespace std;

int Library::addBook(int bookID, string bookTitle, string bookAuthor, ofstream &oBooksFile, bool isAvailable)
{

    for (auto i : books)
    {
        if (i.getID() == bookID)
            return 1;
    }
    Book book(bookID, bookTitle, bookAuthor, isAvailable);
    books.push_back(book);

    oBooksFile << bookID << ";" << bookTitle << ";" << bookAuthor << ";" << endl;
    return 0;
}

void Library::initBooks(ifstream &iBooksFile)
{

    string tempBookID;
    string bookTitle;
    string bookAuthor;
    int bookID;

    string line;

    while (getline(iBooksFile, line))
    {
        stringstream ss(line);

        getline(ss, tempBookID, ';');
        getline(ss, bookTitle, ';');
        getline(ss, bookAuthor, ';');

        bookID = stoi(tempBookID);

        Book book(bookID, bookTitle, bookAuthor, true);

        books.push_back(book);
    }
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

void Library::displayBooks(ifstream &iBooksFile)
{
    iBooksFile.clear();                 // Clear fstream without having to reopen fstream
    iBooksFile.seekg(0, ios::beg); // Move fstream to top right of file so it can re read

    string bookID;
    string bookTitle;
    string bookAuthor;

    string line;

    string username = "In House";

    while (getline(iBooksFile, line))
    {
        stringstream ss(line);

        getline(ss, bookID, ';');
        getline(ss, bookTitle, ';');
        getline(ss, bookAuthor, ';');

        /*
        for(auto &i : users){ //Brain rot :( doesnt work for some reason
            for(auto j : i.getBorrowedBook()){
                if(j == stoi(bookID)){
                    username = i.getUsername();
                    goto print_data;
                }
            }
        }

        print_data: //break out of outer for-loop so program doesnt keep looping even after finding the user. ** Looking for a better implementation of this :( **
        */

        cout << left << "ID: " << setw(10) << bookID
                  << " Title: " << setw(25) << bookTitle
                  << "\tAuthor: " << setw(10) << bookAuthor << endl;
        //<< "\tCheckout: " << setw(20) << username << endl; //Unimplemented For now
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
                    cout << "Book Issued." << endl;
                    break;
                }
            }
        }
        else if (i.getID() == bookID && i.getAvailability() == false)
        {
            string username;
            for (auto &j : users)
            {
                if (j.getUserID() == i.getUserBook())
                {
                    username = j.getUsername();
                    break;
                }
            }
            cout << "Book Already Issued to " << username << endl;
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
            cout << "Book Returned." << endl;
            break;
        }
        else if (i.getID() == bookID && i.getAvailability() == true)
        {
            cout << "Book Already In House " << endl;
            break;
        }
    }
}

int Library::addUser(string userName, int userID, ofstream &oUsersFile)
{
    for (auto i : users)
    {
        if (i.getUserID() == userID)
            return 1;
    }
    User user(userName, userID);
    users.push_back(user);

    oUsersFile << userID << ";" << userName << ";" << endl;

    return 0;
}

void Library::initUsers(ifstream &iUsersFile)
{
    string tempUserID;
    string userName;
    int userID;

    string line;

    while (getline(iUsersFile, line))
    {
        stringstream ss(line);

        getline(ss, tempUserID, ';');
        getline(ss, userName, ';');

        userID = stoi(tempUserID);

        User user(userName, userID);

        users.push_back(user);
    }
}

void Library::displayUsers(ifstream &iUsersFile)
{
    iUsersFile.clear();                 // Same Implementation in displayBook() function
    iUsersFile.seekg(0, ios::beg); // Same Implementation in displayBook() function

    string userName;
    string userID;
    string line;

    while (getline(iUsersFile, line))
    {
        stringstream ss(line);
        getline(ss, userID, ';');
        getline(ss, userName, ';');

        cout << "Name: " << userName << "\tUserID: " << stoi(userID) << endl; // Format to look prettier on console later :)
    }
}