#include "request.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

namespace {
#include "web_page/webPage.h"
}

string Request::Handle::run () {
  process();
  return _print;
}

void Request::Handle::write(string text) {
  _print += text;
}

//Request::Handle::Handle (Request::Connection_wrap w) : connection(w)  {}
Request::Handle::Handle () {}

//Request::Connection_wrap::Connection_wrap (MDH_Connection* con, string &met) {}//: connection(con), _method(met) {}
Request::Connection_wrap::Connection_wrap(MDH_Connection *con, string& met) {method = met; connection = con;}
Request::Connection_wrap::Connection_wrap (Request::Connection_wrap& w): connection(w.connection), _method(w._method) {}
Request::Connection_wrap::Connection_wrap () {}
string Request::Connection_wrap::method () {
  return _method;
}  

namespace {
#define Page(name, content)					\
  class name##_page : public Request::Handle {			\
  public:							\
  Request::Connection_wrap connection;				\
  name##_page (Request::Connection_wrap & w) : connection(w) {}	\
  void process () {						\
    content;							\
  }								\
  };								\

  
Page(Debug, {
    write("debug page\n");
  });
#undef Page
} // un-named

string Request::handle (string method, string url, string post_data, MHD_Connection* connection) {
  MHD_Connection & con_ = *connection;
  string met = method;
  Request::Connection_wrap con(&con_, met);
  Debug_page page(con);
  return page.run();
  return "";
}



Request::Request () {
}
