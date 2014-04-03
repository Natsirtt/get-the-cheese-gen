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
    virtual Id getOtherNode(Id n);
    /**
     * Teste si un joueur peut passer la transition.
     * @param p Le joueur � tester.
     * @param origin l'id du noeud d'origin du joueur. Doit être égale à first ou second
     * @return
     *   true Si le joueur peux passer.
     *   false Si le joueur ne peux pas passer.
     */
    virtual bool canPass(Perso p, Id origin) = 0;
    /**
     * Teste si un joeur peut passer la transition.
     * On considère que le joueur passe de 'first' vers 'second'.
     * @param p Le joueur à tester.
     * @return
     *   true Si le joueur peux passer.
     *   false Si le joueur ne peux pas passer.
     */
    virtual bool canPass(Perso p) = 0;
    /**
     * Teste si le joueur peut passer la transition sans avoir à activer de levier.
     * @param p Le joueur à tester.
     */
    virtual bool canPassWithoutTrigger(Perso p) = 0;
    /**
     * Demande � la transition de changer d'�tat.
     */
    virtual void changeState() = 0;
    /**
     * Spécifie si la transition peut changer d'état.
     */
    virtual bool canChangeState() = 0;
    /**
     * Renvoie le nom de cet obstacle.
     */
    virtual std::string getName();
    /**
     * Modifie le noeud d'origine de la transition.
     */
    virtual void changeFirst(Id newFirst);
    /**
     * Renvoie la représentation de l'obstacle.
     */
    virtual Area getArea();

protected:
    friend ObstacleChooser;
    Gate() : mGraph{nullptr}, mId{0}, mFirst{0}, mSecond{0} {};
    virtual IGate* allocate(IGraph* graph, Id first, Id second) = 0;

private:
    IGraph* mGraph;
    Id mId;
    Id mFirst;
    Id mSecond;
};

#endif // GATE_HPP

