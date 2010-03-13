#include "database.h"
#include <iostream>
#include <vector>
#include <string>

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
