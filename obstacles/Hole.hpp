#ifndef HOLE_HPP
#define	HOLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class Hole : public Gate {
public:
    Hole(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return true;
    }

    bool canPass(Perso p) {
        return true;
    }

    void changeState() {
    }

    bool canChangeState() {
        return false;
    }
private:
    Hole() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new Hole(graph, first, second);
    }
};

#endif	/* HOLE_HPP */
