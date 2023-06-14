#include <iostream>

#include <database.h>

void run_database()
{
    sqlite3* database;
    int resource = sqlite3_open("../../database/purge_count.db", &database);

    if (resource != SQLITE_OK)
        std::cout << "Error!" << std::endl;
    else
        std::cout << "Opened!" << std::endl;
}