#pragma once
#include "enumStructs.h"
#include <iostream>
#include <functional>

namespace IO
{
    void getKeyboardInput(const std::string& message);
    void clearScreenAndExecute(std::function<void()> fn);
    std::string printCharSequence(char ch, int times);
    void displayAuthFailureMessage(int attempts);

    void initialiseLibraryPage(BookList* books, std::size_t maxTitleCnt);
    void initialiseProfilePage(BorrowList* b_list, const std::string& memberID, const std::string& username, const std::string& password);

    void showAuthenticationPage();
    void showLibraryPage();
    void showProfilePage();

    void showAuthMenu();
    void showLibMenu();
    void showProfileMenu();

    BookActions getChoice_libMenu();
    AuthActions getChoice_authMenu();
    ProfileActions getChoice_profileMenu();

    void cyclePage_lib();

    std::string getBorrowedBookID();
    std::string getReturnedBookID();

    // Scoped variables (If you are asking why it's not a static class, shut up)
    inline BookList* booksAll{ nullptr };
    inline BorrowList* booksBorrowed{ nullptr };

    inline int pageNum{ 1 };
    inline std::size_t maxTitleCount{};

    inline std::string uname{};
    inline std::string memID{};
    inline std::string pass{};
}

