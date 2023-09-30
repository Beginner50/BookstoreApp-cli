#include "userAuth.h"
#include "library.h"

/*
    Stores all relevant information about the user
*/
class User
{
public:
    User(Library& lib) : libConsulted{ lib } {}

    bool logIn();
    bool createAccount();

    const std::string& getUsername();
    const std::string& getPassword();
    const std::string& getID();
    BorrowList* getBorrowList();

    void getBooksBorrowed(BookList& bookList, std::string& m_id);

    void addBook(const std::string& bookID);
    void removeBook(const std::string& bookID);

    bool hasBorrowed(const std::string& bookID);
    void displayBorrowedBooks();


private:
    Library& libConsulted;

    std::string m_id{};
    std::string m_username{};
    std::string m_password{};
    BorrowList m_booksBorrowed{};

};
