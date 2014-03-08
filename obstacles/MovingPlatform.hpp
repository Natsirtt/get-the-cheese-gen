#ifndef MOVINGPLATFORM_HPP
#define	MOVINGPLATFORM_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

class MovingPlatform : public Gate {
public:
    MovingPlatform(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
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
    friend ObstacleChooser;
    MovingPlatform() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new MovingPlatform(graph, first, second);
    }
};

#endif	/* MOVINGPLATFORM_HPP */

