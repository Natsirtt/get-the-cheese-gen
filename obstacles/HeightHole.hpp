#ifndef HEIGHTHOLE_HPP
#define	HEIGHTHOLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

/**
 * Un "trou" en hauteur, ou une plateforme surélevée : accessible uniquement que par quelqu'un qui saute haut ou qu'on balance en l'air
 */
class HeightHole : public Gate {
public:
    HeightHole(IGraph* graph, Id first, Id second) : Gate(graph, first, second){
    }

    bool canPass(Perso p, Id origin) {
        return ((origin == Gate::getFirstNode()) && ((p & Perso::Acrobate) != Perso::None)) ||
                origin == Gate::getSecondNode();
    }

    bool canPass(Perso p) {
        return (p & Perso::Acrobate) != Perso::None;
    }

    bool canPassWithoutTrigger(Perso p) {
        return (p & Perso::Acrobate) != Perso::None;
    }

    void changeState() {
    }

    bool canChangeState() {
        return false;
    }
    std::string getName() {
        return "HeightHole";
    }
private:
    friend ObstacleChooser;
    HeightHole() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new HeightHole(graph, first, second);
    }
};

#endif	/* HEIGHTHOLE_HPP */

