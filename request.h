#ifndef _Request_h
#define _Request_h

#include <string>
#include <map>


class Request {
 public:
  class Handle {
  public:
    Handle(std::string);
    std::string run();
    virtual void process () {}
    void write(std::string);
  };
  Request ();
  bool addMap (std::string, Request::Handle);
  std::string handle(std::string, std::string, std::string);
 private:
  std::map<std::string, Handle> routes;
};

#endif
