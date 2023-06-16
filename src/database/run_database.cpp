#include <database.h>

void run_database(sqlite3* database)
{
    database_open(database, "purge_counter");
}