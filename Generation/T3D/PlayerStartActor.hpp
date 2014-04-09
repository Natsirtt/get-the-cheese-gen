#ifndef PLAYERSTARTACTOR_H
#define PLAYERSTARTACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"

#include <string>
#include <vector>

class PlayerStartActor : public IActor {
    public:
        PlayerStartActor(Vector location);
        PlayerStartActor(double xLocation, double yLocation, double zLocation);
        virtual ~PlayerStartActor() {};

        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
    protected:
    private:
        Vector mLocation;
        const std::string mBaseName = "PlayerStart";
};

#endif // BRUSHACTOR_H

