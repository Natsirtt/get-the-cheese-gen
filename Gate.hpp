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
    virtual bool canPass(Perso p, Id origin) {return false;}/*= 0*/; // TODO supprimer une fois les obstacles et la génération complétés
    /**
     * Teste si un joeur peut passer la transition.
     * On considère que le joueur passe de 'first' vers 'second'.
     * @param p Le joueur à tester.
     * @return
     *   true Si le joueur peux passer.
     *   false Si le joueur ne peux pas passer.
     */
    virtual bool canPass(Perso p) {return false;}/*= 0*/; // TODO supprimer une fois les obstacles et la génération complétés
    /**
     * Demande � la transition de changer d'�tat.
     */
    virtual void changeState() {}/*= 0*/; // TODO supprimer une fois les obstacles et la génération complétés
    /**
     * Spécifie si la transition peut changer d'état.
     */
    virtual bool canChangeState() {return false;}/*= 0*/; // TODO supprimer une fois les obstacles et la génération complétés

protected:
    Gate() : mGraph{nullptr}, mId{0}, mFirst{0}, mSecond{0} {};
    virtual IGate* allocate(IGraph* graph, Id first, Id second) {return nullptr;} /*= 0*/;

private:
    IGraph* mGraph;
    Id mId;
    Id mFirst;
    Id mSecond;
};

#endif // GATE_HPP

