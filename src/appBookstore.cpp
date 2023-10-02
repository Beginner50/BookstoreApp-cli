#include "../include/enumStructs.h"
#include "../include/user.h"
#include "../include/dbops.h"
#include "../include/library.h"
#include "../include/io.h"
#define AUTHENTICATION_FAILURE 5
#define AUTHENTICATION_SUCCESS 6

int authenticate(User& user)
{
    int attempts{ 3 };

    while (!user.logIn())
    {
        if (attempts == 0)
            return AUTHENTICATION_FAILURE;
        IO::displayAuthFailureMessage(attempts--);
    }
    return AUTHENTICATION_SUCCESS;
}


int main()
{
    DBops::initialise();

    Library library{};
    User user{ library };

    bool authenticationStage{ true };
    bool profileMenuStage{ false };

    IO::initialiseLibraryPage(library.getBooksAll_coreAttr(), library.getBooksAll_mutAttr(), library.getMaxTitleCount());
    while (true)
    {
        // Authentication stage
        if (authenticationStage)
        {
            IO::clearScreenAndExecute(IO::showAuthenticationPage);
            IO::showAuthMenu();

            auto choice{ IO::getChoice_authMenu() };

            IO::clearScreenAndExecute(IO::showAuthenticationPage);
            if (choice == AuthActions::logIn)
            {
                if (authenticate(user) == AUTHENTICATION_FAILURE)
                {
                    std::cout << "\nAuthentication Failure!\n";
                    IO::getKeyboardInput("Press any key to continue...");
                    continue;
                }
                authenticationStage = false;

                IO::initialiseProfilePage(user.getBorrowList(), user.getID(), user.getUsername(), user.getPassword());
            }
            else if (choice == AuthActions::createAccount)
            {
                if (user.createAccount())
                    std::cout << "Account creation successful!\n";
                IO::getKeyboardInput("Press any key to continue...");
                continue;
            }
            else if (choice == AuthActions::deleteAccount)
            {
                if (user.deleteAccount())
                {
                    std::cout << "Account deletion successful!\n";
                    user.removeAllBooks();
                }
                else
                    std::cout << "Username does not match password!\nAccount deletion not authorised!\n";
                IO::getKeyboardInput("Press any key to continue...");
                continue;
            }
            else if (choice == AuthActions::exitProgram)
                break;
        }

        // Profile Menu Stage (After Library Stage)
        if (profileMenuStage)
        {
            IO::clearScreenAndExecute(IO::showProfilePage);
            IO::showProfileMenu();

            auto choice{ IO::getChoice_profileMenu() };

            if (choice == ProfileActions::changeUname)
            {
                std::string newUname{ user.changeAndGetUsername() };
                IO::changeUsername(newUname);
                continue;
            }
            else if (choice == ProfileActions::changePass)
            {
                std::string newPass{ user.changeAndGetPassword() };
                IO::changePassword(newPass);
                continue;
            }
            else if (choice == ProfileActions::libraryPage)
            {
                profileMenuStage = false;
                continue;
            }
        }

        // Library stage
        IO::clearScreenAndExecute(IO::showLibraryPage);
        IO::showLibMenu();

        auto choice{ IO::getChoice_libMenu() };

        if (choice == BookActions::borrowBook)
        {
            std::string bookID{};
            while (std::tolower(bookID[0]) != 'q')
            {
                IO::clearScreenAndExecute(IO::showLibraryPage);
                bookID = IO::getBorrowedBookID();

                if (std::tolower(bookID[0]) == 'q')
                    break;
                else if (library.isBorrowable(bookID))
                {
                    library.addBorrower(user.getID(), bookID);
                    user.addBook(bookID);
                }
                else
                {
                    std::cout << "This book cannot be borrowed!\n";
                    IO::getKeyboardInput("Press any key to continue...");
                }
            }
        }
        else if (choice == BookActions::returnBook)
        {
            std::string bookID{};
            while (std::tolower(bookID[0]) != 'q')
            {
                IO::clearScreenAndExecute(IO::showLibraryPage);
                user.displayBorrowedBooks();

                bookID = IO::getReturnedBookID();

                if (std::tolower(bookID[0]) == 'q')
                    break;
                else if (user.hasBorrowed(bookID))
                {
                    library.removeBorrower(user.getID(), bookID);
                    user.removeBook(bookID);
                }
                else
                {
                    std::cout << "You have not borrowed this book (" + bookID + ")!\n";
                    IO::getKeyboardInput("Press any key to continue...");
                }
            }
        }
        else if (choice == BookActions::nextPage)
        {
            IO::cyclePage_lib();
            continue;
        }
        else if (choice == BookActions::openProfile)
        {
            profileMenuStage = true;
            continue;
        }
        else if (choice == BookActions::exitLibrary)
        {
            authenticationStage = true;
            continue;
        }

        IO::getKeyboardInput("Press any key to continue...");
        system("clear");
    }

    DBops::closeConnection();
    return 0;
}