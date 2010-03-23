#include "request.h"
#include <string>
#include <map>
#include <vector>

#include <iostream>





using namespace std;



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
Request::Connection_wrap::Connection_wrap(struct MHD_Connection *con, string& met) { _method = met; connection = con;}
Request::Connection_wrap::Connection_wrap (Request::Connection_wrap& w): connection(w.connection), _method(w._method) {}
Request::Connection_wrap::Connection_wrap () {}
string Request::Connection_wrap::method () { return _method; }
string Request::Connection_wrap::operator [] (string query) {
  const char * ret = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, query.c_str());
  return !ret ? "" : string(ret);
}

namespace {
#define Page(name, content)						\
  class name##_page : public Request::Handle {				\
  public:								\
  Request::Connection_wrap connection;					\
  Request * parent;							\
  string load (string s) {					\
    return parent->static_pages[s];					\
  }									\
  name##_page (Request::Connection_wrap & w, Request * p) : connection(w), parent(p) {} \
  void process () {							\
    content;								\
  }									\
  };									\

  
#include "Pages.cpp"

#undef Page
} // un-named

string Request::handle (string method, string url, string post_data, MHD_Connection* connection, char** rType) {
  cout << "requesting page: " << url << endl;
  struct MHD_Connection & con_ = *connection;
  string met = method;
  Request::Connection_wrap con(&con_, met);
  *rType = "text/html";


  if(url == "/") {
    Home_page page(con, this);
    return page.run();
  }else if(url == "/js") {
    *rType = "application/javascript";
    js_page page(con, this);
    return page.run();
  }else if(url == "/style") {
    *rType = "text/plain";
    style_page page(con, this);
    return page.run();
  }

  // else
  Debug_page page(con, this);
  return page.run();
  
}

namespace {
#include "web_page/webPage.h"
}



Request::Request () {

  // set up static pages
  static_pages["home"] = WebHomePage;
  static_pages["myJs"] = WebJSCodeMy;
  static_pages["jquery"] = WebJsCodeJquery;
  static_pages["css"] = WebCSS;
}
