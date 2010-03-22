#include <iostream>
#include <fstream>
using namespace std;

int main (int argc, char *argv[]) {
  char i;
  if(argc < 4) {
    cout << argv[0] << "var_name from to\n";
    return 1;
  }
  ifstream from(argv[2], ifstream::in | ifstream::binary);
  ofstream to(argv[3], ofstream::out);
  to << "char *" << argv[1] << " =  \n\"";
  while(from.good()) {
    from.get(i);
    switch(i) {
    case '\"':
      to << "\\\"";
      break;
    case '\n':
      to << "\\n";
      break;
    case '\r':
      to << "\\r";
      break;
    case '\\':
      to << "\\\\";
      break;
    default:
      if (i <= 127)
	to << i;
      else
	to << "\\" << (int)i;
    }
  }
  to  << "\" ;";
  return 0;
}
