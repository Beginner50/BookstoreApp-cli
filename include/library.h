#pragma once 
#include "dbops.h"

class User;
class Library
{
private:
    BookList m_booksAll{};
    BorrowList m_booksBorrowed{};

    std::size_t maxTitleCount{};

public:
    Library() { loadBooks(); }

    void loadBooks();
    void reloadBooks();

    void addMember(std::string& memID, std::string& uname, std::string& password);

    bool isBorrowable(std::string& bookID);
    void addBorrower(const std::string& memID, std::string& bookID);
    void removeBorrower(const std::string& memID, std::string& bookID);

    void renderAvailable(std::string& bookTitle);
    void renderUnavailable(std::string& bookTitle);

    BookList* getAllBooks() { return &m_booksAll; }
    std::size_t getMaxTitleCount() { return maxTitleCount; }

    friend User;
    std::string newUserID();
};
