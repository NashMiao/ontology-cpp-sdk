#ifndef STRUCT_H
#define STRUCT_H

#include <boost/any.hpp>
#include <list>

class Struct {
private:
  std::list<boost::any> List;

public:
  Struct add(std::list<boost::any> objs) {
    std::list<boost::any>::iterator it;
    for (it = objs.begin(); it != objs.end(); it++) {
      List.push_back(*it);
    }
    return *this;
  }

  std::list<boost::any>& getList(){
    return List;
  }
};
#endif