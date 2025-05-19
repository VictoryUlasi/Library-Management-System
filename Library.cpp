#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include "Book.hpp"
#include "User.hpp"
#include "Library.hpp"

int Library::addBook(int bookID, std::string bookTitle, std::string bookAuthor,std::ofstream& oBooksFile, bool isAvailable)
{

    for(auto i : books){
        if(i.getID() == bookID) return 1;
    }
    Book book(bookID, bookTitle, bookAuthor, isAvailable);
    books.push_back(book);

    oBooksFile << bookID << ";" << bookTitle << ";" << bookAuthor << ";" << std::endl;
    return 0;
}

void Library::initBooks(std::ifstream& iBooksFile){

    std::string tempBookID;
    std::string bookTitle;
    std::string bookAuthor;
    int bookID;

    std::string line;

    while(getline(iBooksFile,line)){
        std::stringstream ss(line);

        std::getline(ss,tempBookID,';');
        std::getline(ss,bookTitle,';');
        std::getline(ss,bookAuthor,';');

        bookID = std::stoi(tempBookID);

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

void Library::displayBooks(std::ifstream& iBooksFile)
{
    iBooksFile.clear();                // Clear fstream without having to reopen fstream
    iBooksFile.seekg(0,std::ios::beg); // Move fstream to top right of file so it can re read

    std::string bookID;
    std::string bookTitle;
    std::string bookAuthor;

    std::string line;

    std::string username = "In House";

    while(std::getline(iBooksFile, line)){
        std::stringstream ss(line);

        std::getline(ss, bookID, ';');
        std::getline(ss, bookTitle, ';');
        std::getline(ss, bookAuthor, ';');

        /*
        for(auto &i : users){ //Brain rot :( doesnt work for some reason
            for(auto j : i.getBorrowedBook()){
                if(j == std::stoi(bookID)){
                    username = i.getUsername();
                    goto print_data;
                }
            }
        }
            
        print_data: //break out of outer for-loop so program doesnt keep looping even after finding the user. ** Looking for a better implementation of this :( **
        */

        std::cout << std::left << "ID: " << std::setw(10) << bookID
                  << " Title: " << std::setw(25) << bookTitle
                  << "\tAuthor: " << std::setw(10) << bookAuthor << std::endl;
                  //<< "\tCheckout: " << std::setw(20) << username << std::endl; //Unimplemented For now
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

int Library::addUser(std::string userName , int userID, std::ofstream& oUsersFile)
{
    for(auto i : users){
        if(i.getUserID() == userID) return 1;
    }
    User user(userName, userID);
    users.push_back(user);

    oUsersFile << userID << ";" << userName << ";" << std::endl;

    return 0;
}

void Library::initUsers(std::ifstream& iUsersFile){
    std::string tempUserID;
    std::string userName;
    int userID;

    std::string line;

    while(getline(iUsersFile,line)){
        std::stringstream ss(line);

        std::getline(ss,tempUserID,';');
        std::getline(ss,userName,';');

        userID = std::stoi(tempUserID);

        User user(userName,userID);

        users.push_back(user);
    }
}

void Library::displayUsers(std::ifstream& iUsersFile)
{
    iUsersFile.clear(); // Same Implementation in displayBook() function
    iUsersFile.seekg(0,std::ios::beg); // Same Implementation in displayBook() function

    std::string userName;
    std::string userID;
    std::string line;

    while(std::getline(iUsersFile, line)){
        std::stringstream ss(line);
        std::getline(ss, userID, ';');
        std::getline(ss, userName, ';');

        std::cout << "Name: " << userName << "\tUserID: " << std::stoi(userID) << std::endl; //Format to look prettier on console later :)
    }
}