#ifndef MOVINGPLATFORM_HPP
#define	MOVINGPLATFORM_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class Crusher : public Gate {
public:

    MovingPlatform() : Gate() {
    }

    MovingPlatform(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second) {
    }

    bool canPass(Perso p, Id origin) {
        return true;
    }

    void changeState() {
        //rien
    }

};

#endif	/* MOVINGPLATFORM_HPP */

