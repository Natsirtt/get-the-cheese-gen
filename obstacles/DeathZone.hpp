#ifndef DEATHZONE_HPP
#define	DEATHZONE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class DeathZone : public Gate {
public:
    DeathZone(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        //Non blocant, seulement pour embêter le joueur
        return true;
    }

    void changeState() {
        //rien
    }
private:
    DeathZone() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new DeathZone(graph, first, second);
    }
};

#endif	/* DEATHZONE_HPP */

