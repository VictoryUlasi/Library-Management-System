#include <iostream>    // For standard I/O operations
#include <windows.h>   // For Windows-specific console functions
#include <conio.h>     // For getch() to capture keyboard input
#include "Library.hpp" // Custom header for the Library class and related functionality
#include <fstream>

using namespace std; // Allows use of standard names without ' '

void displayMenu();                                  // Displays the main menu
void performSelection(int &selection, Library &lib, ofstream& booksFile, ofstream& usersFile); // Handles user selection based on menu input
void ClearScreen();                                  // Clears the console screen

int main()
{
    Library lib1; // Create a Library object
    ofstream booksFile("libBook.txt" , ios::app);
    ofstream usersFile("libUser.txt" , ios::app);

    int user_selection; // Variable to store user's menu selection

    do
    {
        ClearScreen();                          // Clear the screen before displaying the menu
        displayMenu();                          // Show the menu options
        cin >> user_selection;                  // Get user input
        performSelection(user_selection, lib1, booksFile, usersFile); // Call function to handle the selection
    } while (user_selection != 0); // Repeat until user chooses to exit

    booksFile.close();
    return 0; // End of program
}

void displayMenu()
{
    // Display the available options in the menu
    cout << "----Library Management System----" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Remove Book" << endl;

    cout << "3. Add User" << endl;
    cout << "4. Display All Users" << endl;

    cout << "5. Display All Books" << endl;
    cout << "6. Issue Book" << endl;
    cout << "7. Return Book" << endl;

    cout << "0. Exit" << endl;
}

void performSelection(int &selection, Library &lib ,ofstream& booksFile, ofstream& usersFile)
{
    switch (selection)
    {
    case 1: // add book
    {
        int bookID;
        string bookName;
        string bookAuthor;

        cout << "Enter Book ID: ";
        cin >> bookID; // Get the book ID from user
        cout << "Enter Book Name: ";
        cin.ignore();           // Clears the input buffer to ensure getline reads properly.
        getline(cin, bookName); // Get the book title
        cout << "Enter Book Author: ";
        getline(cin, bookAuthor); // Get the author's name

        lib.addBook(bookID, bookName, bookAuthor); // Add book to library

        string nbookID = to_string(bookID);
        booksFile << nbookID + ";" + bookName + ";" + bookAuthor << endl;
        break;
    }
    case 2: // remove book
    {
        int bookID;
        cout << "Enter Book ID to Remove: ";
        cin >> bookID;          // Get the book ID to remove
        lib.removeBook(bookID); // Remove book from library
        break;
    }
    case 3: // add user
    {
        string userName;
        int userID;

        cout << "Enter UserID: ";
        cin >> userID;
        cout << "Enter name (first last): ";
        cin.ignore();           // Clears the input buffer to ensure getline reads properly.
        getline(cin, userName); // Get full name

        lib.addUser(userName , userID);  // Add user to library

        string nuserID = to_string(userID);
        usersFile << nuserID << ";" << userName << endl;
        break;
    }
    case 4: // display all users
    {
        ClearScreen();      // Clear console for better readability
        lib.displayUsers(); // Show all registered users
        cout << "Press Enter/Return to continue....\n";
        getch(); // Pauses the program until a key is pressed (for Windows only).
        break;
    }
    case 5: // display books
    {
        ClearScreen();      // Clear console for better readability
        lib.displayBooks(); // Show all available books
        cout << "Press Enter/Return to continue....\n";
        getch(); // Pauses the program until a key is pressed (for Windows only).
        break;
    }
    case 6: // issue book
    {
        int bookID;
        int userID;

        cout << "Enter Book ID to Issue: ";
        cin >> bookID; // Get book ID to issue
        cout << "Enter User ID: ";
        cin >> userID; // Get user ID who is borrowing

        lib.issueBook(bookID, userID); // Issue book to user
        break;
    }
    case 7: // return book
    {
        int bookID;
        cout << "Enter Book ID to Return: ";
        cin >> bookID;          // Get book ID to return
        lib.returnBook(bookID); // Return book to library
        break;
    }
    case 0: // exit
    {
        break; // Exit the program
    }
    default:
        cout << "Invalid selection. Try again.\n"; // Inform user of invalid input
        getch();                                   // Pauses the program until a key is pressed (for Windows only).
    }
}

void ClearScreen()
{
    HANDLE hStdOut;                  // Handle to the standard output
    CONSOLE_SCREEN_BUFFER_INFO csbi; // Console screen buffer info
    DWORD count;                     // Number of cells written to
    DWORD cellCount;                 // Total number of cells in the console
    COORD homeCoords = {0, 0};       // Home coordinates to move cursor to top left

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to console output
    if (hStdOut == INVALID_HANDLE_VALUE)
        return;

    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) // Get buffer info
        return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y; // Calculate total cell count

    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count)) // Fill console with spaces
        return;

    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) // Reset attributes
        return;

    SetConsoleCursorPosition(hStdOut, homeCoords); // Move cursor to top-left corner
}
