#ifndef DEATHZONE_HPP
#define	DEATHZONE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class DeathZone : public Gate {
public:
    /*DeathZone() : Gate() {
    }*/

    DeathZone(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        //Non blocant, seulement pour embêter le joueur
        return true;
    }

    void changeState() {
        //rien
    }

};

#endif	/* DEATHZONE_HPP */

