#ifndef _Request_h
#define _Request_h

#include <string>
#include <map>
#include "platform.h"
#include <microhttpd.h>
#include "database.h"

class Request {
 public:
  class Connection_wrap {
  private:
    struct MHD_Connection * connection;
    std::string _method;
  public:
    //Connection_wrap (MDH_Connection*, std::string&);
    Connection_wrap (struct MHD_Connection*, std::string&);
    Connection_wrap (Connection_wrap&);
    Connection_wrap ();
    std::string method();
    std::string operator [] (std::string);
    
  };
  class Handle {
  private:
    std::string _print;
  public:
    //Handle(Connection_wrap);
    Handle();
    std::string run();
    virtual void process () {}
    void write(std::string);
  };
  Database * db;
  std::map<std::string, char*> static_pages;
  Request (Database*);
  std::string handle(std::string, std::string, std::string, MHD_Connection*, char**);
 private:
  std::map<std::string, Handle> routes;
};

#endif
