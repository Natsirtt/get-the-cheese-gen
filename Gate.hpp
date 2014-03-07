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
     * Attribue un id � la transition.
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
     * Renvoie l'ID du noeud de la transition qui n'est pas celui passé en paramètre. 
     */
    virtual Id getOtherNode(INode n);

    /**
     * Teste si un joueur peut passer la transition.
     * @param p Le joueur � tester.
     * @param origin l'id du noeud d'origin du joueur. Doit être égale à first ou second
     * @return
     *   true Si le joueur peux passer.
     *   false Si le joueur ne peux pas passer.
     */

    virtual bool canPass(Perso p, Id origin) {return false;}/*= 0*/;
    
    /**
     * Demande � la transition de changer d'�tat.
     */
    virtual void changeState() {}/*= 0*/;

private:
    IGraph* mGraph;
    Id mId;
    Id mFirst;
    Id mSecond;
};

#endif // GATE_HPP

