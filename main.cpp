#define NOMINMAX
#include <iostream>     // For standard I/O operations
#include <windows.h>    // For Windows-specific console functions
#include <conio.h>      // For getch() to capture keyboard input
#include "libclass.hpp" // Custom header for the Library class and related functionality
#include <fstream>
#include <limits>
#include <string>

using namespace std; // Allows use of standard names without ' '

bool initialize(Library &lib, ifstream &iBooksFile, ifstream &iUsersFile);
void displayMenu();                                                                                                                          // Displays the main menu
void performSelection(int &selection, Library &lib, ofstream &oBooksFile, ofstream &oUsersFile, ifstream &iBooksFile, ifstream &iUsersFile); // Handles user selection based on menu input
void ClearScreen();                                                                                                                          // Clears the console screen
bool checkNum(string &idNum);
void refresh(ofstream &file , int state);

int main()
{

    Library lib1; // Create a Library object
    ofstream oBooksFile("libBook.txt", ios::app);
    ofstream oUsersFile("libUser.txt", ios::app);
    ifstream iBooksFile("libBook.txt");
    ifstream iUsersFile("libUser.txt");

    int user_selection; // Variable to store user's menu selection

    initialize(lib1, iBooksFile, iUsersFile);

    do
    {
        ClearScreen();                                                                          // Clear the screen before displaying the menu
        displayMenu();                                                                          // Show the menu options
        cout << "Option: ";
        cin >> user_selection;                                                                  // Get user input
        while (!cin.good()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            user_selection = -1;
        }
        performSelection(user_selection, lib1, oBooksFile, oUsersFile, iBooksFile, iUsersFile); // Call function to handle the selection
    } while (user_selection != 0); // Repeat until user chooses to exit

    oBooksFile.close();
    oUsersFile.close();
    iBooksFile.close();
    iUsersFile.close();
    return 0; // End of program
}

bool initialize(Library &lib, ifstream &iBooksFile, ifstream &iUsersFile) //read data from file and write to users and books vector.
{
    lib.initBooks(iBooksFile);
    lib.initUsers(iUsersFile);

    return 0;
}

void displayMenu()
{
    // Display the available options in the menu
    cout << "----LIBRARY MANAGEMENT SYSTEM V1.1----" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Remove Book" << endl;

    cout << "3. Add User" << endl;
    cout << "4. Remove User" << endl;
    cout << "5. Display All Users" << endl;

    cout << "6. Display All Books" << endl;
    cout << "7. Issue Book" << endl;
    cout << "8. Return Book" << endl;

    cout << "0. Exit" << endl;
}

bool checkNum(string &idNum) //Returns False if all chars in string are digits, Returns True if any char is not a digit
{
    for (auto &i : idNum)
    {
        if (!isdigit(i))
        {
            return true;
        }
    }
    return false;
}

void refresh(ofstream &file , int state){ //Refresh File to allow printing in "real time" rather than on close. state = 0 for oBooksFile, state = 1 for oUsersFile
    if(file.is_open() && state == 0){
        file.close();
        file.open("libBook.txt", ios::app);
    }else if(file.is_open() && state == 1){
        file.close();
        file.open("libUser.txt", ios::app);
    }
}

void performSelection(int &selection, Library &lib, ofstream &oBooksFile, ofstream &oUsersFile, ifstream &iBooksFile, ifstream &iUsersFile)
{
    switch (selection)
    {
    case 1: // add book
    {
        string bookID;
        string bookName;
        string bookAuthor;

        cout << "Enter Book ID: ";
        cin >> bookID; // Get the book ID from user

        if (checkNum(bookID))
        {
            cout << "Enter a valid ID number." << endl;
            cout << "Press Enter to Continue...";
            _getch();
            break;
        }
        cout << "Enter Book Name: ";
        cin.ignore();           // Clears the input buffer to ensure getline reads properly.
        getline(cin, bookName); // Get the book title
        cout << "Enter Book Author: ";
        getline(cin, bookAuthor); // Get the author's name

        if (lib.addBook(stoi(bookID), bookName, bookAuthor, oBooksFile))
        { // Add book to library
            ClearScreen();
            cout << "{Error}Duplicate Book ID.";
            _getch();
        }
        refresh(oBooksFile, 0);
        break;
    }
    case 2: // remove book
    {
        int bookID;
        cout << "Enter Book ID to Remove: ";
        cin >> bookID;                      // Get the book ID to remove
        lib.removeBook(bookID, oBooksFile); // Remove book from library
        break;
    }
    case 3: // add user
    {
        string userName;
        string userID;

        cout << "Enter UserID: ";
        cin >> userID;

         if(checkNum(userID)){
            cout << "Enter a valid ID number." << endl;
            cout << "Press Enter to Continue...";
            _getch();
            break;
        }
        
        cout << "Enter name (first last): ";
        cin.ignore();           // Clears the input buffer to ensure getline reads properly.
        getline(cin, userName); // Get full name

        if (lib.addUser(userName, stoi(userID), oUsersFile))
        { // Add user to library
            ClearScreen();
            cout << "{Error}Duplicate User ID.";
            _getch();
        }
        refresh(oUsersFile , 1);
        break;
    }
    case 4: //remove User
    {
        int userID;
        cout << "Enter User ID to remove: ";
        cin >> userID;

        ClearScreen();
        lib.removeUser(userID, oUsersFile);
        _getch();
        break;
    }
    case 5: // display all users
    {
        ClearScreen();                // Clear console for better readability
        lib.displayUsers(iUsersFile); // Show all registered users
        cout << "Press Enter/Return to continue....\n";
        _getch(); // Pauses the program until a key is pressed (for Windows only).
        break;
    }
    case 6: // display books
    {
        ClearScreen();                // Clear console for better readability
        lib.displayBooks(iBooksFile); // Show all available books
        cout << "Press Enter/Return to continue....\n";
        _getch(); // Pauses the program until a key is pressed (for Windows only).
        break;
    }
    case 7: // issue book
    {
        int bookID;
        int userID;

        cout << "Enter Book ID to Issue: ";
        cin >> bookID; // Get book ID to issue
        cout << "Enter User ID: ";
        cin >> userID; // Get user ID who is borrowing

        ClearScreen();
        lib.issueBook(bookID, userID,oBooksFile); // Issue book to user
        _getch(); // Pauses the program until a key is pressed (for Windows only).
        break;
    }
    case 8: // return book
    {
        int bookID;
        cout << "Enter Book ID to Return: ";
        cin >> bookID;          // Get book ID to return
        ClearScreen();
        lib.returnBook(bookID,oBooksFile); // Return book to library
        _getch();
        break;
    }
    case 0: // exit
    {
        ClearScreen();
        break; // Exit the program
    }
    default:
        ClearScreen();
        cout << "Invalid selection. Try again.\n"; // Inform user of invalid input
        _getch();                                   // Pauses the program until a key is pressed (for Windows only).
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
