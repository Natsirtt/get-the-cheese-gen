#ifndef DEATHZONE_HPP
#define	DEATHZONE_HPP

#include "../Gate.hpp"
#include "../IGraph.hpp"
#include "../Enum.hpp"

/**
 * Un trou fatal au joueur, ou de la lave etc... c'est la même chose qu'un Trap mais un Trap est caché pour tendre un piège au joueur
 */
class DeathZone : public Gate {
public:
    DeathZone(IGraph* graph, Id first, Id second) : Gate(graph, first, second) {
    }

    bool canPass(Perso p, Id origin) {
        //Non blocant, seulement pour embêter le joueur
        return true;
    }

    bool canPass(Perso p) {
        return true;
    }

    bool canPassWithoutTrigger(Perso p) {
        return true;
    }

    void changeState() {
        //RIEN
    }

    bool canChangeState() {
        return false;
    }
    std::string getName() {
        return "DeathZone";
    }
private:
    friend ObstacleChooser;
    DeathZone() : Gate() {
    }

    IGate* allocate(IGraph* graph, Id first, Id second) {
        return new DeathZone(graph, first, second);
    }
};

#endif	/* DEATHZONE_HPP */

