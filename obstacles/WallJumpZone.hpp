#ifndef WALLJUMPZONE_HPP
#define	WALLJUMPZONE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"


class WallJumpZone : public Gate {
public:
    WallJumpZone(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    bool canPass(Perso p) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    bool canPassWithoutTrigger(Perso p) {
        return (p & Perso::Yamakasi) != Perso::None;
    }

    void changeState() {
    }

    bool canChangeState() {
        return false;
    }
    std::string getName() {
        return "WallJump";
    }
private:
    friend ObstacleChooser;
    WallJumpZone() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new WallJumpZone(graph, first, second);
    }
};

#endif	/* WALLJUMPZONE_HPP */

