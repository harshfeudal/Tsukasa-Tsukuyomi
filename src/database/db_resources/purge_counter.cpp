#include <database.h>

void purge_counter(sqlite3* database)
{
    int rc = database_open(database, "purge_counter");

    std::string sql = "CREATE TABLE PURGE_COUNTER("     \
                      "MESSAGE_ID TEXT NOT NULL,"       \
                      "PURGE_COUNT INTEGER NOT NULL);";

    rc = sqlite3_exec(database, sql.c_str(), NULL, 0, NULL);
}