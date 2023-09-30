#include "../include/io.h"

void IO::clearScreenAndExecute(std::function<void()> fn)
{
    system("clear");
    fn();
    std::cout << '\n';
}

void IO::displayAuthFailureMessage(int attempts)
{
    if (attempts != 1)
        std::cout << "\nPassword does not match username! " << attempts << " attempts remaining!\n";
    else
        std::cout << "\nPassword does not match username! " << attempts << " attempt remaining!\n";
}

void IO::clearInput()
{
    std::cin.ignore(213320, '\n');
    std::cin.clear();
}

std::string IO::printCharSequence(char ch, int times)
{
    for (int i{}; i < times; ++i)
        std::cout << ch;
    return "";
}

bool IO::validLibChoice(char ch)
{
    switch (ch)
    {
    case 'a':
    case 'A':
    case 'b':
    case 'B':
    case 'R':
    case 'r':
    case 'p':
    case 'P':
    case 'n':
    case 'N':
    case 'q':
    case 'Q': return true;
    default: return false;
    }
}

bool IO::validAuthChoice(char ch)
{
    switch (ch)
    {
    case 'l':
    case 'L':
    case 'c':
    case 'C':
    case 'd':
    case 'D':
    case 'q':
    case 'Q': return true;
    default: return false;
    }
}

bool IO::validProfileChoice(char ch)
{
    switch (ch)
    {
    case 'u':
    case 'U':
    case 'p':
    case 'P':
    case 'l':
    case 'L':
    case 'q':
    case 'Q': return true;
    default: return false;
    }
}

void IO::displayInvalidInputErrorMessage()
{
    std::cout << "Invalid input!\n";
}

BookActions IO::charToBookActions(char ch)
{
    switch (ch)
    {
    case 'a':
    case 'A': return BookActions::exitLibrary;
    case 'b':
    case 'B': return BookActions::borrowBook;
    case 'R':
    case 'r': return BookActions::returnBook;
    case 'p':
    case 'P': return BookActions::openProfile;
    case 'n':
    case 'N': return BookActions::nextPage;
    case 'q':
    case 'Q':
    default: return BookActions::exitProgram;
    }
}

AuthActions IO::charToAuthActions(char ch)
{
    switch (ch)
    {
    case 'l':
    case 'L': return AuthActions::logIn;
    case 'c':
    case 'C': return AuthActions::createAccount;
    case 'd':
    case 'D': return AuthActions::deleteAccount;
    case 'q':
    case 'Q':
    default: return AuthActions::exitProgram;
    }
}

ProfileActions IO::charToProfileActions(char ch)
{
    switch (ch)
    {
    case 'u':
    case 'U':  return ProfileActions::changeUname;
    case 'p':
    case 'P':  return ProfileActions::changePass;
    case 'l':
    case 'L':  return ProfileActions::libraryPage;
    case 'q':
    case 'Q':
    default: return ProfileActions::exitProgram;
    }
}
BookActions IO::getChoice_libMenu()
{
    std::cout << "\n> ";
    char ch{};
    std::cin >> ch;

    while (!validLibChoice(ch))
    {
        clearInput();
        displayInvalidInputErrorMessage();
        std::cout << "> ";
        std::cin >> ch;
    }

    clearInput();
    return charToBookActions(ch);

}

AuthActions IO::getChoice_authMenu()
{
    std::cout << "\n> ";
    char ch{};
    std::cin >> ch;

    while (!validAuthChoice(ch))
    {
        clearInput();
        displayInvalidInputErrorMessage();
        std::cout << "> ";
        std::cin >> ch;
    }

    clearInput();
    return charToAuthActions(ch);
}

ProfileActions IO::getChoice_profileMenu()
{
    std::cout << "\n> ";
    char ch{};
    std::cin >> ch;

    while (!validProfileChoice(ch))
    {
        clearInput();
        displayInvalidInputErrorMessage();
        std::cout << "> ";
        std::cin >> ch;
    }

    clearInput();
    return charToProfileActions(ch);
}

std::string IO::getBorrowedBookID()
{
    std::cout << "Enter the id of the book to be borrowed OR enter Q to exit: ";
    std::string bookName{};
    std::getline(std::cin >> std::ws, bookName);
    return bookName;
}

std::string IO::getReturnedBookID()
{
    std::cout << "Enter the id of the book to be returned OR enter Q to exit: ";
    std::string bookName{};
    std::getline(std::cin >> std::ws, bookName);
    return bookName;
}

void IO::getKeyboardInput(const std::string& message)
{
    std::cout << '\n' << message << ' ';
    std::cin.peek();
}

void IO::initialiseLibraryPage(BookList* books, std::size_t maxTitleCnt)
{
    booksAll = books;
    maxTitleCount = maxTitleCnt;
}

void IO::initialiseProfilePage(BorrowList* b_list, const std::string& memberID, const std::string& username, const std::string& password)
{
    booksBorrowed = b_list;
    uname = username;
    memID = memberID;
    pass = password;
}

void IO::showAuthenticationPage()
{
    std::cout << "#####################################\n#                                   #\n#          Bookstore App            #\n#                                   #\n#####################################\n\n";
}


void IO::showLibraryPage()
{
    int idDisplayLength{ 10 };
    int titleDisplayLength{ static_cast<int>(maxTitleCount) + 4 };
    int availableDisplayLength{ 13 };
    int rowLength{ idDisplayLength + titleDisplayLength + availableDisplayLength };

    std::function<void()> printHeader{ [=]() {
        std::cout << printCharSequence('-', (rowLength - 8) / 2)
        << "Bookstore App" << printCharSequence('-', (rowLength - 12) / 2) << '\n'
        << printCharSequence('-', rowLength)
        << "\n| bookID | Title" << printCharSequence(' ', titleDisplayLength - 15) << "(Page " << pageNum << ") "
        << " | Available |\n" << printCharSequence('-', rowLength) << '\n';
    } };

    std::function<void()> printBody{ [&]() {
        int lowerBound{(pageNum - 1) * 4};
        int upperBound{pageNum * 4 - 1};
        int count{0};

    for (auto& book : *booksAll)
    {
        if (count >= lowerBound && count <= upperBound)
        {
        std::cout << "| " << book.bookID << "   | " << book.title
        << printCharSequence(' ', titleDisplayLength - book.title.length() - 1)
        << " | " << (book.available == true ? "Yes       |\n" : "No        |\n");
        }
        ++count;
    }
    } };

    std::function<void()> printTail{ [=]() {
        std::cout << printCharSequence('-', rowLength) << '\n';
    } };

    printHeader();
    printBody();
    printTail();
}

void IO::showProfilePage()
{
    std::size_t rowLength{};
    for (auto book : *booksBorrowed)
        if (book->title.length() > rowLength)
            rowLength = book->title.length();
    rowLength += 15;

    if (rowLength == 15)
        std::cout << printCharSequence('-', rowLength + 6) << '\n'
        << "| UserID: " << printCharSequence(' ', rowLength - 10) << memID + " |\n"
        << "| Username: " << printCharSequence(' ', rowLength - 8 - uname.length()) << uname + " |\n"
        << "| Password: " << printCharSequence(' ', rowLength - 8 - pass.length()) << pass + " |\n"
        << "| Books Borrowed: " << printCharSequence(' ', rowLength - 14) << " |\n"
        << printCharSequence('-', rowLength + 6) << '\n';
    else
    {
        std::cout << printCharSequence('-', rowLength) << '\n'
            << "| UserID: " << printCharSequence(' ', rowLength - 16) << memID + " |\n"
            << "| Username: " << printCharSequence(' ', rowLength - 14 - uname.length()) << uname + " |\n"
            << "| Password: " << printCharSequence(' ', rowLength - 14 - pass.length()) << pass + " |\n"
            << "| Books Borrowed: " << printCharSequence(' ', rowLength - 20) << " |\n| "
            << printCharSequence(' ', rowLength - 3) << "|\n";

        for (auto book : *booksBorrowed)
            std::cout << "| " << book->bookID << "       " << book->title << printCharSequence(' ', rowLength - 15 - book->title.length()) << " |\n";
        std::cout << printCharSequence('-', rowLength) << '\n';
    }
}

void IO::showAuthMenu()
{
    std::cout << "Log In         (L)   Create Account (C)\n"
        << "Delete Account (D)   Quit           (Q)\n\n";
}

void IO::showLibMenu()
{

    std::cout << "Borrow Book         (B)           Return Book  (R)\n"
        << "Authentication Menu (A)           User Profile (P)\n"
        << "Next Page           (N)           Quit         (Q)\n";
}

void IO::showProfileMenu()
{
    std::cout << "Change Username (U)       Change Password (P)\n"
        << "Library Page    (L)       Quit            (Q)\n";
}

void IO::cyclePage_lib()
{
    ++pageNum;
    if (static_cast<unsigned int>(pageNum) > (booksAll->size() / 4) + 1)
        pageNum = 1;
}

void IO::changeUsername(std::string& username) { uname = username; }

void IO::changePassword(std::string& password) { pass = password; }


