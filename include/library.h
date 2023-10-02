#pragma once 
#include "dbops.h"

class User;
class Library
{
private:
    BookList_coreAttr m_booksAll_coreAttr{};
    BookList_mutAttr m_booksAll_mutAttr{};

    BorrowList m_booksBorrowed{};

    std::size_t maxTitleCount{};

public:
    Library() { loadBooks(); }

    void loadBooks();

    void addMember(std::string& memID, std::string& uname, std::string& password);

    bool isBorrowable(std::string& bookID);
    void addBorrower(const std::string& memID, std::string& bookID);
    void removeBorrower(const std::string& memID, std::string& bookID);

    void renderAvailable(std::string& bookTitle);
    void renderUnavailable(std::string& bookTitle);

    BookList_coreAttr* getBooksAll_coreAttr() { return &m_booksAll_coreAttr; }
    BookList_mutAttr* getBooksAll_mutAttr() { return &m_booksAll_mutAttr; }

    std::size_t getMaxTitleCount() { return maxTitleCount; }

    friend User;
    std::string newUserID();
};
