#ifndef _Request_h
#define _Request_h

#include <string>
#include <map>
#include "platform.h"
#include <microhttpd.h>

class Request {
 public:
  class Connection_wrap {
  private:
    MDH_Connection * connection;
    std::string _method;
  public:
    //Connection_wrap (MDH_Connection*, std::string&);
    Connection_wrap (MDH_Connection*, std::string&);
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
  Request ();
  std::string handle(std::string, std::string, std::string, MHD_Connection*);
 private:
  std::map<std::string, Handle> routes;
};

#endif
