#pragma once
#include "enumStructs.h"
#include <iostream>
#include <functional>

class IO
{
public:
    static void getKeyboardInput(const std::string& message);
    static void clearScreenAndExecute(std::function<void()> fn);
    static std::string printCharSequence(char ch, int times);
    static void displayAuthFailureMessage(int attempts);

    static void initialiseLibraryPage(BookList_coreAttr* books_coreAttr, BookList_mutAttr* books_mutAttr, std::size_t maxTitleCnt);
    static void initialiseProfilePage(BorrowList* b_list, const std::string& memberID, const std::string& username, const std::string& password);

    static void showAuthenticationPage();
    static void showLibraryPage();
    static void showProfilePage();

    static void showAuthMenu();
    static void showLibMenu();
    static void showProfileMenu();

    static BookActions getChoice_libMenu();
    static AuthActions getChoice_authMenu();
    static ProfileActions getChoice_profileMenu();

    static void cyclePage_lib();

    static std::string getBorrowedBookID();
    static std::string getReturnedBookID();

    static void changeUsername(std::string& uname);
    static void changePassword(std::string& pass);

private:
    static void clearInput();

    static bool validLibChoice(char ch);
    static bool validAuthChoice(char ch);
    static bool validProfileChoice(char ch);

    static void displayInvalidInputErrorMessage();

    static BookActions charToBookActions(char ch);
    static AuthActions charToAuthActions(char ch);
    static ProfileActions charToProfileActions(char ch);

    static inline BookList_coreAttr* booksAll_coreAttr{ nullptr };
    static inline BookList_mutAttr* booksAll_mutAttr{ nullptr };

    static inline BorrowList* booksBorrowed{ nullptr };

    static inline int pageNum{ 1 };
    static inline std::size_t maxTitleCount{};

    static inline std::string uname{};
    static inline std::string memID{};
    static inline std::string pass{};
};

