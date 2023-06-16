#pragma once

#include <filesystem>

#include <sqlite3/sqlite3.h>
#include <spdlog/spdlog.h>
#include <dpp/dpp.h>

void run_database(sqlite3* database);

int database_open(sqlite3* database, std::string database_name);

void purge_counter(sqlite3* database);