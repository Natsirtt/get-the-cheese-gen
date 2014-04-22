#ifndef TURRET_HPP
#define	TURRET_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

/**
 * Une zone couvete par le rayon d'action d'une tourelle de défense pouvant tuer
 * Toute personne ne courant pas vite.
 */
class Turret : public Gate {
private:
    bool mStateOn;

public:
    Turret(IGraph* graph, Id first, Id second) : Gate(graph, first, second), mStateOn{true} {
    }

    bool canPass(Perso p, Id origin) {
        return (mStateOn && ((p & Perso::Yamakasi) != Perso::None)) || !mStateOn;
    }

    bool canPass(Perso p) {
        return (mStateOn && ((p & Perso::Yamakasi) != Perso::None)) || !mStateOn;
    }

    bool canPassWithoutTrigger(Perso p) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
        mStateOn = !mStateOn;
    }

    bool canChangeState() {
        return mStateOn;
    }
    std::string getName() {
        return "Turret";
    }
    Area getArea() {
        return AreaManager::get().getRandomArea(std::string("TurretRoom"));
        //return Area("Area/Turret.area");
    }
private:
    friend ObstacleChooser;
    Turret() : Gate(), mStateOn{true} {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new Turret(graph, first, second);
    }
};

#endif	/* TURRET_HPP */

