#ifndef TRIGGERACTOR_H
#define TRIGGERACTOR_H

#include "IActor.hpp"
#include "../Utils/Vector.hpp"
#include "NameFactory.hpp"

#include <string>
#include <vector>

class TriggerActor : public IActor {
    public:
        TriggerActor(Vector location, std::string triggerableName);
        TriggerActor(double xLocation, double yLocation, double zLocation, std::string triggerableName);
        TriggerActor(Grid *g, std::string triggerableName);
        virtual ~TriggerActor() {};

        virtual std::string getT3D(int indentLevel, NameFactory *nameFactory);
        virtual void writeT3D(std::ofstream& output, int indentLevel, NameFactory *nameFactory, Vector gridPosition, Vector gridTranslation);
    protected:
    private:
        Vector mLocation;
        std::string mTriggerableName;
        const std::string mBaseName = "TERTrigger";
};

#endif // BRUSHACTOR_H

