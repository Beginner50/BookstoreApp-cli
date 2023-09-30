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

struct Book
{
    std::string bookID{};
    std::string title{};
    bool available{};
};

using BookList = std::vector<Book>;
using BorrowList = std::list<Book*>;