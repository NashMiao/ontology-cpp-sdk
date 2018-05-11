#ifndef IDENTIFY_H
#define IDENTIFY_H

#include <string>
#include <list>

class Identity
{
    std::string label = "";
    std::string ontid = "";
    bool isDefault = false;
    bool lock = false;
    std::list<Control> controls;
    Object extra;
};
#endif // !IDENTIFY_H