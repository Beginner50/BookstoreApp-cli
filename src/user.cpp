#include "../include/user.h"

bool User::logIn()
{
    m_username = UserAuth::getUsername();
    m_password = UserAuth::getPassword();
    m_id = UserAuth::getUserID(m_username, m_password);
    if (m_id == "")
        return false;

    getBooksBorrowed(libConsulted.m_booksAll, m_id);
    return true;
}

bool User::createAccount()
{
    m_username = UserAuth::getUsername();
    m_password = UserAuth::getPassword();
    m_id = libConsulted.newUserID();
    libConsulted.addMember(m_id, m_username, m_password);
    return true;
}

const std::string& User::getUsername() { return m_username; }
const std::string& User::getPassword() { return m_password; }
const std::string& User::getID() { return m_id; }
BorrowList* User::getBorrowList() { return &m_booksBorrowed; }

void User::getBooksBorrowed(BookList& bookList, std::string& memID)
{
    DBops::filterContainer(bookList, m_booksBorrowed, "SELECT bookID FROM borrow WHERE memID = '" + memID + "';");
}

void User::addBook(const std::string& bookID)
{
    for (auto& book : libConsulted.m_booksAll)
        if (book.bookID == bookID)
        {
            m_booksBorrowed.push_back(&book);
            break;
        }
}

void User::removeBook(const std::string& bookID)
{
    for (auto book : m_booksBorrowed)
        if (book->bookID == bookID)
        {
            m_booksBorrowed.remove(book);
            break;
        }
}

bool User::hasBorrowed(const std::string& bookID)
{
    for (auto book : m_booksBorrowed)
    {
        if (book->bookID == bookID)
            return true;
    }
    return false;
}

void User::displayBorrowedBooks()
{
    std::cout << "Borrowed Books: ";
    for (auto book : m_booksBorrowed)
        std::cout << book->bookID << ' ';
    std::cout << "\n\n";
}