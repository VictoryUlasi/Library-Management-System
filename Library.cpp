#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include "libclass.hpp"
using namespace std;

void Library::initBooks(ifstream& iBooksFile)
{

    string tempBookID;
    string bookTitle;
    string bookAuthor;
    string tempAvailability;
    string tempUserBook;

    string line;

    while (getline(iBooksFile, line))
    {
        stringstream ss(line);

        getline(ss, tempBookID, ';');
        getline(ss, bookTitle, ';');
        getline(ss, bookAuthor, ';');
        getline(ss, tempAvailability, ';');
        getline(ss, tempUserBook, ';');

        Book book(stoi(tempBookID), bookTitle, bookAuthor, stoi(tempAvailability), stoi(tempUserBook));

        books.push_back(book);
    }
}

int Library::addBook(int bookID, string bookTitle, string bookAuthor, ofstream &oBooksFile)
{

    for (const auto& i : books)
    {
        if (i.getID() == bookID)
            return 1;
    }
    Book book(bookID, bookTitle, bookAuthor);
    books.push_back(book);
    refresh(oBooksFile);

    return 0;
}

void Library::removeBook(int id, ofstream &oBooksFile)
{
    if (oBooksFile.is_open())
    {
        /*Needs Better Implementation but works for now,
        im thinking of just loading everything into a vector
        on program start and then writing everything on close
        so i dont have to keep opening and closing files. */
        oBooksFile.close();
        oBooksFile.open("libBook.txt", ios::out);
    }

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

    refresh(oBooksFile);
    cout << "Book Removed." << endl;
}

void Library::displayBooks(ifstream &iBooksFile)
{
    iBooksFile.clear();            // Clear fstream without having to reopen fstream
    iBooksFile.seekg(0, ios::beg); // Move fstream to top right of file so it can re read

    string bookID;
    string bookTitle;
    string bookAuthor;
    string availability;
    string userBook;

    string line;

    string username = "In House";

    while (getline(iBooksFile, line))
    {
        stringstream ss(line);

        getline(ss, bookID, ';');
        getline(ss, bookTitle, ';');
        getline(ss, bookAuthor, ';');
        getline(ss, availability, ';');
        getline(ss, userBook, ';');

        for (const auto& i : users) {
            if (i.getUserID() == stoi(userBook)) {
                username = i.getUsername();
                break;
            }
        }

        cout << left << "ID: " << setw(10) << bookID
             << "Title: " << setw(25) << bookTitle
             << "\tAuthor: " << setw(10) << bookAuthor
             << "\tCheckout: " << setw(20) << username << endl; //Unimplemented For now
    }
}

void Library::issueBook(int bookID, int userID, ofstream& oBooksFile)
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
                    refresh(oBooksFile);
                    return;
                }
            }
            cout << "User Not Found." << endl;
            return;
        }
        else if (i.getID() == bookID && i.getAvailability() == false)
        {
            for (auto &j : users)
            {
                if (j.getUserID() == i.getUserBook())
                {
                    cout << "Book Already Issued to: " << j.getUsername() << endl;
                    return;
                }
            }
            return;
        }
    }
    cout << "Book Not Found." << endl;
}

void Library::returnBook(int bookID, ofstream& oBooksFile)
{
    for (auto &i : books)
    {
        if (i.getID() == bookID && i.getAvailability() == false)
        {
            i.setAvailability(true);
            i.setUserBook(0);
            cout << "Book Returned." << endl;
            refresh(oBooksFile);
            return;
        }
        else if (i.getID() == bookID && i.getAvailability() == true)
        {
            cout << "Book Already In House " << endl;
            return;
        }
    }
    cout << "Book Not Found." << endl;
}

void Library::initUsers(ifstream& iUsersFile)
{
    string tempUserID;
    string userName;

    string line;

    while (getline(iUsersFile, line))
    {
        stringstream ss(line);

        getline(ss, tempUserID, ';');
        getline(ss, userName, ';');

        User user(userName, stoi(tempUserID));

        users.push_back(user);
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

void Library::displayUsers(ifstream &iUsersFile)
{
    iUsersFile.clear();            // Same Implementation in displayBook() function
    iUsersFile.seekg(0, ios::beg); // Same Implementation in displayBook() function

    string userName;
    string userID;
    string line;

    while (getline(iUsersFile, line))
    {
        stringstream ss(line);
        getline(ss, userID, ';');
        getline(ss, userName, ';');

        cout << left <<  "Name: " << setw(10) << userName << "\tUserID: " << setw(10) << stoi(userID) << endl; // Format to look prettier on console later :)
    }
}

void Library::removeUser(int id, ofstream& oUsersFile) {

    int userPos = 0;
    for (const auto& i : users)
    {
        if (i.getUserID() == id)
        {
            users.erase(users.begin() + userPos);

            if (oUsersFile.is_open()) {
                oUsersFile.close();
                oUsersFile.open("libUser.txt", ios::out);
            }

            for (const auto& i : users) {
                oUsersFile << i.getUserID() << ";" << i.getUsername() << ";" << endl;
            }
            cout << "User Removed" << endl;
            return;
        }
        userPos++;
    }
    cout << "User Not Found." << endl;
}

void Library::refresh(ofstream& oBooksFile) {

    if (oBooksFile.is_open())
    {
        /*Needs Better Implementation but works for now,
        im thinking of just loading everything into a vector
        on program start and then writing everything on close
        so i dont have to keep opening and closing files. */
        oBooksFile.close();
        oBooksFile.open("libBook.txt", ios::out);
    }

    for (const auto& i : books) {
        oBooksFile << i.getID() << ";" << i.getTitle() << ";" << i.getAuthor() << ";" << i.getAvailability() << ";" << i.getUserBook() << ";" << endl;
    }

}