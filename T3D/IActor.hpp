#ifndef IACTOR_HPP
#define IACTOR_HPP

#include <string>

#include "NameFactory.hpp"

class IActor {
public:
    virtual ~IActor() {}

    virtual std::string getT3D(int indentLevel, NameFactory *nameFactory) = 0;
protected:

private:
};

#endif // IACTOR_HPP
