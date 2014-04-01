#include "NameFactory.hpp"

#include <stdexcept>
#include <sstream>

NameFactory::NameFactory() {
}

std::string NameFactory::getName(std::string key) {
    long long c = mCounts[key];
    mCounts[key] = c + 1;
    std::stringstream stream;
    stream << key << "_" << c;
    return stream.str();
}
