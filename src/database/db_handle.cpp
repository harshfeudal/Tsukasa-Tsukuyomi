#include <database.h>

int database_open(sqlite3* database, std::string database_name)
{
    std::string path = fmt::format("../../database/{}.db", database_name);
    return sqlite3_open(path.c_str(), &database);
}