#include "request.h"
#include <string>

using namespace std;


string Request::Handle::run () {
  return "";
}

void Request::Handle::write(string text) {
  
}

Request::Handle::Handle (string in) {
  
}

string Request::handle (string method, string url, string post_data) {
  return method;
}


bool Request::addMap(string path, Handle handle) {
  
  return false;
}

Request::Request () {
}
