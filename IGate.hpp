#ifndef IGATE_HPP
#define IGATE_HPP

#include "Enum.hpp"

/**
 * Repr�sente une transition dans le r�seau de p�tri.
 * Une transition ne peut �tre connect�e qu'� 2 noeuds.
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
     * @param p Le joueur � tester.
     * @return
     *   true Si le joueur peux passer.
     *   false Si le joueur ne peux pas passer.
     */
    virtual bool canPass(Perso p) = 0;
    /**
     * Demande � la transition de changer d'�tat.
     */
    virtual void changeState() = 0;
};

#endif // IGATE_HPP

