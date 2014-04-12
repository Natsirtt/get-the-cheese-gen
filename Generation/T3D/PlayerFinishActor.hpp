#ifndef PLAYERFINISHACTOR_H
#define PLAYERFINISHACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"

#include <string>
#include <vector>

class PlayerFinishActor : public IActor {
    public:
        PlayerFinishActor(Vector location);
        PlayerFinishActor(double xLocation, double yLocation, double zLocation);
        virtual ~PlayerFinishActor() {};

        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
    protected:
    private:
        Vector mLocation;
        const std::string mBaseName = "PlayerFinish";
};

#endif // BRUSHACTOR_H

