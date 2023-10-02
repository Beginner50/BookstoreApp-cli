#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>

enum class BookActions
{
    borrowBook,
    returnBook,
    exitLibrary,
    openProfile,
    nextPage
};

enum class AuthActions
{
    logIn,
    createAccount,
    deleteAccount,
    exitProgram
};

enum class ProfileActions
{
    changeUname,
    changePass,
    libraryPage
};

/*
    Book only stores immutable sections of a book object as represented in the database
*/
struct Book_coreAttr
{
    std::string bookID{};
    std::string title{};
};

struct Book_mutAttr
{
    std::string bookID{};
    bool available{};
};

using BookList_coreAttr = std::vector<Book_coreAttr>;
using BookList_mutAttr = std::vector<Book_mutAttr>;

using BorrowList = std::list<Book_coreAttr*>;