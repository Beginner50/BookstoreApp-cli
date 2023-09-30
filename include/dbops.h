#pragma once
#include <sqlite3.h>
#include <string_view>
#include "enumStructs.h"


// Highly unsafe sqlite3 interface wrapper
/*
    Handles database connection and can perform queries
*/
class DBops
{
private:
    inline static sqlite3* db_ = nullptr;

public:
    static void initialise();
    static void closeConnection();

    static std::string getRowResult(const std::string& query, int totalColumns = 1);

    static void fillContainer(BookList& bookArr, const std::string& query, int totalColumns = 1);
    static void filterContainer(BookList& inContainer, BorrowList& outContainer, const std::string& query);
};