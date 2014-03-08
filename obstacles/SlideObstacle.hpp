#ifndef SLIDEOBSTACLE_HPP
#define	SLIDEOBSTACLE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class SlideObstacle : public Gate {
public:
    /*SlideObstacle() : Gate() {
    }*/

    SlideObstacle(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    bool canPass(Perso p) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
    }

    bool canChangeState() {
        return false;
    }
    std::string getName() {
        return "SlideObstacle";
    }
private:
    friend ObstacleChooser;
    SlideObstacle() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new SlideObstacle(graph, first, second);
    }
};

#endif	/* SLIDEOBSTACLE_HPP */

