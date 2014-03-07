#ifndef LASER_HPP
#define	LASER_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class Laser : public Gate {
    Laser() : Gate() {
    }
    
    Laser(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second) {
    }
    
    bool canPass(Perso p, Id origin) {
        //Non blocant, seulement pour embêter le joueur
        return true;
    }
    
    void changeState() {
        //rien
    }

};

#endif	/* LASER_HPP */

