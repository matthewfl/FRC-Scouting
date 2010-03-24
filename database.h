#ifndef _database_h
#define _database_h

#include "sqlite/sqlite3.h"
#include <vector>
#include <string>

class Database {
 private:
  sqlite3 * db;
 public:
  std::vector<std::vector<std::string> > query(std::string);
  Database ();
};

#endif
