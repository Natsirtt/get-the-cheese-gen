#ifndef PLAYERFINISHACTOR_H
#define PLAYERFINISHACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"
#include "../3D/Grid.hpp"

#include <string>
#include <vector>

class PlayerFinishActor : public IActor {
    public:
        PlayerFinishActor(Vector location);
        PlayerFinishActor(double xLocation, double yLocation, double zLocation);
        PlayerFinishActor(Grid *g);
        virtual ~PlayerFinishActor() {};

        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition);

    protected:
    private:
        Vector mLocation;
        const std::string mBaseName = "PlayerFinish";
};

#endif // BRUSHACTOR_H

