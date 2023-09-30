#include "../include/userAuth.h"
#include "../include/enumStructs.h"


namespace Utils
{
    bool validInput(const std::string& inStr)
    {
        if (std::find(inStr.begin(), inStr.end(), '\'') != std::end(inStr))
            return false;
        return true;
    }
}

namespace UserAuth
{
    std::string getUsername()
    {
        std::string uname{};
        std::cout << "Enter your username: ";
        std::getline(std::cin >> std::ws, uname);

        while (!Utils::validInput(uname))
        {
            std::cout << "Username cannot contain (')!\n\nEnter your username correctly: ";
            std::getline(std::cin >> std::ws, uname);
        }

        return uname;
    }

    std::string getPassword()
    {
        std::cout << "Enter your password: ";
        std::string pass{};
        std::getline(std::cin, pass);

        while (!Utils::validInput(pass))
        {
            std::cout << "Password cannot contain (')!\n\nEnter your password correctly: ";
            std::getline(std::cin >> std::ws, pass);
        }

        return pass;
    }

    std::string getUserID(std::string& uname, std::string& pass)
    {
        return DBops::getRowResult("SELECT memID FROM member WHERE uname = '" + uname + "' AND pass = '" + pass + "';");
    }


}
