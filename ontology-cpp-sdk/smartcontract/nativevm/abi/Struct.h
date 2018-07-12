#ifndef STRUCT_H
#define STRUCT_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <list>

#include <boost/any.hpp>

class Struct {
private:
  std::list<boost::any> List;

public:
  Struct() {}
  Struct(std::list<boost::any> _list) : List(_list) {}
  Struct add(const std::list<boost::any> &objs) {
    std::list<boost::any>::const_iterator cit;
    List.insert(List.end(), objs.begin(), objs.end());
    return *this;
  }

  std::list<boost::any> getList() { return List; }
};
#endif