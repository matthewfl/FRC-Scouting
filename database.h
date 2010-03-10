#ifndef _database_h
#define _database_h

#include <sqlite3.h>

class Database {
 private:
  sqlite3 * db;
};

#endif
