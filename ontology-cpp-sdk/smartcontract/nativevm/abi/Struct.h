#ifndef STRUCT_H
#define STRUCT_H

#include <boost/any.hpp>
#include <list>

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