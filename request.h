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
    void process ()=0;
  };
  Request ();
  addMap (std::string, Handle);
 private:
  std::map<std::string, Handle> routes;
};

#endif
