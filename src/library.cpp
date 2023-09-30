#include "../include/library.h" 
#include <functional>

void Library::loadBooks()
{
    DBops::fillContainer(m_booksAll, "SELECT bookID, title, available FROM book;", 3);
    DBops::filterContainer(m_booksAll, m_booksBorrowed, "SELECT bookID FROM borrow;");

    for (auto& book : m_booksAll)
        if (book.title.size() > maxTitleCount)
            maxTitleCount = book.title.size();
}

void Library::reloadBooks()
{
    m_booksAll.clear();
    loadBooks();
}

bool Library::isBorrowable(std::string& bookID)
{
    for (auto& book : m_booksAll)
        if (bookID == book.bookID)
            if (book.available)
                return true;
    return false;
}

void Library::addBorrower(const std::string& memID, std::string& bookID)
{
    DBops::getRowResult("INSERT INTO borrow VALUES('" + memID + "','" + bookID + "');");
    DBops::getRowResult("UPDATE book SET available = 0 WHERE bookID = '" + bookID + "';");
}

void Library::removeBorrower(const std::string& memID, std::string& bookID)
{
    DBops::getRowResult("DELETE FROM borrow WHERE memID = '" + memID + "' AND bookID = '" + bookID + "';");
    DBops::getRowResult("UPDATE book SET available = 1 WHERE bookID = '" + bookID + "';");
}

void Library::addMember(std::string& memID, std::string& uname, std::string& password)
{
    DBops::getRowResult("INSERT INTO member VALUES('" + memID + "','" + uname + "','" + password + "');");
}

std::string Library::newUserID()
{
    std::string nextUserID{};

    int userCount{ std::stoi(DBops::getRowResult("SELECT COUNT(*) FROM member;")) };
    int i{ 1 };

    do
    {
        if (userCount + i < 10)
            nextUserID = "m00" + std::to_string(userCount + 1);
        else if (userCount + i < 100)
            nextUserID = "m0" + std::to_string(userCount + 1);
        else
            nextUserID = "m" + std::to_string(userCount);
        ++i;
    } while (DBops::getRowResult("SELECT memID FROM member WHERE memID = '" + nextUserID + "';") != "");
    return nextUserID;
}

