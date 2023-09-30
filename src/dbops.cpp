#include "../include/dbops.h"

void DBops::initialise()
{
    sqlite3_open("/home/prashant/Desktop/projects/bookstore/db/bookstoreDB.db", &db_);
}

void DBops::closeConnection() {
    sqlite3_close(db_);
    db_ = nullptr;
}

// Works like an iterator
std::string DBops::getRowResult(const std::string& query, int totalColumns)
{
    static std::string prevQuery{};
    static sqlite3_stmt* stmt{};
    static int rc{};
    static bool finalised{ false };
    std::string result{};

    if (prevQuery != query)
    {
        rc = sqlite3_prepare(db_, query.c_str(), -1, &stmt, NULL);
        prevQuery = query;
        finalised = false;
    }

    if (finalised)
        return "";

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        for (int col{}; col < totalColumns; col++)
        {
            result += reinterpret_cast<const char*>(sqlite3_column_text(stmt, col));
            result += "%";
        }
        if (totalColumns == 1)
            result = result.substr(0, result.size() - 1);
    }
    else if (result == "")
    {
        sqlite3_finalize(stmt);
        finalised = true;
    }

    return result;
}

void DBops::fillContainer(BookList& bookArr, const std::string& query, int totalColumns)
{
    while (true)
    {
        std::string result{ getRowResult(query, totalColumns) };
        if (result == "")
            break;

        int attrCounter{};
        Book tempBook{};

        for (char ch : result)
        {
            if (ch == '%')
            {
                ++attrCounter;
                continue;
            }
            else if (attrCounter == 0)
                tempBook.bookID += ch;
            else if (attrCounter == 1)
                tempBook.title += ch;
            else if (attrCounter == 2)
                tempBook.available = ch == '1' ? true : false;
        }
        bookArr.push_back(tempBook);
    }
}

void DBops::filterContainer(BookList& inContainer, BorrowList& outContainer, const std::string& query)
{
    while (true)
    {
        std::string filterCondition{ getRowResult(query) };
        if (filterCondition == "")
            break;

        for (auto& content : inContainer)
            if (content.bookID == filterCondition)
            {
                outContainer.push_back(&content);
                break;
            }
    }
}