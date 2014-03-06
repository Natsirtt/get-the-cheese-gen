#ifndef GATE_HPP
#define GATE_HPP

#include "IGate.hpp"

class IGraph;

class Gate : public IGate {
public:
    /**
     * Constructeur d'une transition.
     * @param graph Le graphe dans lequel se situe la transition.
     * @param first Le noeud d'origine.
     * @param second Le noeud destination.
     */
    Gate(IGraph* graph, Id first, Id second);

    virtual ~Gate();

    /**
     * Attribue un id à la transition.
     */
    virtual void setId(Id gid);
    /**
     * Renvoie l'ID de la transition.
     */
    virtual Id getID();
    /**
     * Renvoie l'ID du premier noeud.
     */
    virtual Id getFirstNode();
    /**
     * Renvoie l'ID du second noeud.
     */
    virtual Id getSecondNode();
    /**
     * Teste si un joeur peut passer la transition.
     * @param p Le joueur à tester.
     * @return
     *   true Si le joueur peux passer.
     *   false Si le joueur ne peux pas passer.
     */
    virtual bool canPass(Perso p) {}/*= 0*/;
    /**
     * Demande à la transition de changer d'état.
     */
    virtual void changeState() {}/*= 0*/;

private:
    IGraph* mGraph;
    Id mId;
    Id mFirst;
    Id mSecond;
};

#endif // GATE_HPP

