#include "../include/library.h" 
#include <functional>

void Library::loadBooks()
{
    /*
        Problem Analysis: Conflict between BookList and BorrowList

        Before discussing the problem at hand, the functions of BookList and BorrowList
        should be clarified first.

        BookList :- Stores an array of books

        BorrowList :- Stores POINTERS to books in a certain booklist
                      This implies that upon clearing the list, the book
                      objects are not deleted; hence, essentially making
                      the list serve its purpose as a reference list to the booklist

        The problem:
        The problem arises when BookList supports the move assignment; the reason for
        which will be made clear after a bit of introspection: Essentially, the same
        pointers stored by the borrowlist are those used by the booklist (internally)
        to locate each books allocated on the heap.

        Therefore, clearing the list or even copying another booklist should produce
        no effect on the overall behaviour since the pointers are preserved each time.

        An analogy would be to think of the booklist as a set of robotic hands that are each
        capable of holding an object of the same type and each booklist can support only
        one type of robotic hands. The borrowlist on the other hand is a subset of the
        booklist/ keep track of a subset of hands. Therefore, if another booklist were to
        be created, it would use another unique set of hands. You can see the problem
        with the move assignment now: if the move assignment were to be used, then the set
        of robotic hands would change from one type to another. And if the borrowlist were
        to remain the same, it would keep track of the previous booklist state and thus
        produce undefined behaviour.

        Solutions:
        There are some solutions on how to go about with this:
        1) Restructure how books are stored and represented by the program
           (Make it such that mutable aspects of a book are stored independently of booklist
            and borrowlist)
           Pros: Makes it so that booklist is immutable, thus avoiding such complications
           Cons: Time consuming, entails structural changes
        2) Update borrowlist for each updated instance of booklist
           Pros: Easy to implement
           Cons: Limits the scalability of the application, highly inefficient method
        3) Leave the program as it is
           Pros: No steps required
           Cons: Same as the above except a little bit more efficient

    */

    m_booksAll_coreAttr = DBops::fillBooksCoreAttr("SELECT bookID, title FROM book;", 2);
    m_booksAll_mutAttr = DBops::fillBooksMutAttr("SELECT bookID, available FROM book;", 2);
    m_booksBorrowed = DBops::filterBooksCoreAttr(m_booksAll_coreAttr, "SELECT bookID FROM borrow;");

    for (auto& book : m_booksAll_coreAttr)
        if (book.title.size() > maxTitleCount)
            maxTitleCount = book.title.size();
}

bool Library::isBorrowable(std::string& bookID)
{
    for (auto& book : m_booksAll_mutAttr)
        if (bookID == book.bookID)
        {
            if (book.available)
                return true;
            else
                break;
        }
    return false;
}

void Library::addBorrower(const std::string& memID, std::string& bookID)
{
    DBops::getRowResult("INSERT INTO borrow VALUES('" + memID + "','" + bookID + "');");
    DBops::getRowResult("UPDATE book SET available = 0 WHERE bookID = '" + bookID + "';");
    for (auto& book : m_booksAll_mutAttr)
        if (book.bookID == bookID)
        {
            book.available = false;
            break;
        }
}

void Library::removeBorrower(const std::string& memID, std::string& bookID)
{
    DBops::getRowResult("DELETE FROM borrow WHERE memID = '" + memID + "' AND bookID = '" + bookID + "';");
    DBops::getRowResult("UPDATE book SET available = 1 WHERE bookID = '" + bookID + "';");
    for (auto& book : m_booksAll_mutAttr)
        if (book.bookID == bookID)
        {
            book.available = true;
            break;
        }
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

