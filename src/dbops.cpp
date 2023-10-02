#include "../include/dbops.h"

void DBops::initialise()
{
    sqlite3_open("../db/bookstoreDB.db", &db_);
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

BookList_coreAttr DBops::fillBooksCoreAttr(const std::string& query, int totalColumns)
{
    BookList_coreAttr bookArr{};

    while (true)
    {
        std::string result{ getRowResult(query, totalColumns) };
        if (result == "")
            break;

        int attrCounter{};
        Book_coreAttr tempBook{};

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

        }
        bookArr.push_back(tempBook);
    }
    return bookArr;
}

BookList_mutAttr DBops::fillBooksMutAttr(const std::string& query, int totalColumns)
{
    BookList_mutAttr bookArr{};

    while (true)
    {
        std::string result{ getRowResult(query, totalColumns) };
        if (result == "")
            break;

        int attrCounter{};
        Book_mutAttr tempBook{};

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
                tempBook.available = (ch == '1' ? true : false);
        }
        bookArr.push_back(tempBook);
    }
    return bookArr;
}


BorrowList DBops::filterBooksCoreAttr(BookList_coreAttr& booksAll_coreAttr, const std::string& query)
{
    BorrowList borrowList{};

    while (true)
    {
        std::string filterCondition{ getRowResult(query) };
        if (filterCondition == "")
            break;

        for (auto& content : booksAll_coreAttr)
            if (content.bookID == filterCondition)
            {
                borrowList.push_back(&content);
                break;
            }
    }
    return borrowList;
}