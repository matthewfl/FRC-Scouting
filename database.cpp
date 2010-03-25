#include "database.h"
#include <iostream>
#include <vector>
#include <string>

#include <stdlib.h>

using namespace std;




static int SqlCallBack(void * passed, int argc, char **argv, char **azColName) {
  vector<vector<string> > * p = reinterpret_cast<vector<vector<string> >* >(passed);
  vector<string> data;
  for(int i=0; i < argc; i++) {
    data.push_back(string(argv[i]));
  }
  p->push_back(data);
  return 0;
}

vector<vector<string> > Database::query(string q) {
  vector<vector<string> > ret;
  char *error=0;
  if(SQLITE_OK != sqlite3_exec(db, q.c_str(), SqlCallBack, (void*)(&ret), &error)) {
    cerr <<"Sql error: " << error << endl;
    sqlite3_free(error);
  }
  return ret;
}


Database::Database () {
  if(sqlite3_open("frc_data.db", &db)) {
      cerr << "error: opening database\n";
      sqlite3_close(db);
      exit(1);
    }
  query("CREATE TABLE IF NOT EXISTS match (number INTEGER, red1 INTEGER, red2 INTEGER, red3 INTEGER, blue1 INTEGER, blue2 INTEGER, blue3 INTEGER);");
  query("CREATE TABLE IF NOT EXISTS team (name TEXT, number INTEGER, rank INTEGER);");
  query("CREATE TABLE IF NOT EXISTS teamMatch (team INTEGER, pos INTEGER, match INTEGER, autoAtemp INTEGER, autoMade INTEGER, telAtemp INTEGER, telMade INTEGER, hangAtemp INTEGER, hangMade INTEGER, pen TEXT, notes TEXT);");
}
