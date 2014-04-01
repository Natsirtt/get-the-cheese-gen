#ifndef NAMEFACTORY_H
#define NAMEFACTORY_H

#include <string>
#include <map>

class NameFactory
{
    public:
        NameFactory();
        std::string getName(std::string key);
        virtual ~NameFactory() {};
    protected:
    private:
        std::map<std::string, long long> mCounts;
};

#endif // NAMEFACTORY_H
