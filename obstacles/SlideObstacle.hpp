#ifndef SLIDEOBSTACLE_HPP
#define	SLIDEOBSTACLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class SlideObstacle : public Gate {
    SlideObstacle() : Gate() {
    }
    
    SlideObstacle(IGraph *graph, Id first, Id second) : Gate(graph, Id first, Id second) {
    }
    
    bool canPass(Perso p, Id origin) {
        if (p == Perso.Yamakasi) {
            return true;
        }
        return false;
    }
    
    void changeState() {
        //rien
    }
};

#endif	/* SLIDEOBSTACLE_HPP */

