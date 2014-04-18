#ifndef DOORACTOR_H
#define DOORACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"

#include <string>
#include <vector>

class DoorActor : public IActor {
    public:
        DoorActor(Vector location);
        DoorActor(double xLocation, double yLocation, double zLocation);
        DoorActor(Grid *g);
        virtual ~DoorActor() {};

        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation);

        std::string getName(NameFactory *nameFactory = nullptr);
    protected:
    private:
        Vector mLocation;
        std::string mName;
        const std::string mBaseName = "TERDoor";
};

#endif // BRUSHACTOR_H

