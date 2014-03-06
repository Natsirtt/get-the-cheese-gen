#ifndef IGATE_HPP
#define IGATE_HPP

#include "Enum.hpp"

/**
 * Représente une transition dans le réseau de pétri.
 * Une transition ne peut être connectée qu'à 2 noeuds.
 */
class IGate {
public:
    virtual ~IGate() {};

    /**
     * Renvoie l'ID de la transition.
     */
    virtual Id getID() = 0;
    /**
     * Renvoie l'ID du premier noeud.
     */
    virtual Id getFirstNode() = 0;
    /**
     * Renvoie l'ID du second noeud.
     */
    virtual Id getSecondNode() = 0;
    /**
     * Teste si un joeur peut passer la transition.
     * @param p Le joueur à tester.
     * @return
     *   true Si le joueur peux passer.
     *   false Si le joueur ne peux pas passer.
     */
    virtual bool canPass(Perso p) = 0;
    /**
     * Demande à la transition de changer d'état.
     */
    virtual void changeState() = 0;
};

#endif // IGATE_HPP

