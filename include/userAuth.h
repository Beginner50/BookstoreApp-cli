#pragma once
#include "dbops.h"
#include "enumStructs.h"
#include <algorithm>

/*
    Handles all functions related to user authentication or input of credentials:-
    1) Gets username from user
    2) Gets password from user
    3) Gets userID from username and password or returns "Not Found" if authentication fails
*/

namespace UserAuth
{
    std::string getUsername();
    std::string getPassword();
    std::string getUserID(std::string& uname, std::string& pass);
}