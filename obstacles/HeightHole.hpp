#ifndef HEIGHTHOLE_HPP
#define	HEIGHTHOLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class HeightHole : public Gate {
public:
    /*HeightHole() : Gate() {
    }*/

    HeightHole(IGraph* graph, Id first, Id second) : Gate(graph, first, second){
    }

    bool canPass(Perso p, Id origin) {
        return ((origin == Gate::getFirstNode()) && ((p & Perso::Acrobate) != Perso::None)) ||
                origin == Gate::getSecondNode();
    }

    void changeState() {
    }
};

#endif	/* HEIGHTHOLE_HPP */

