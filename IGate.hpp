#ifndef IGATE_HPP
#define IGATE_HPP

#include <string>
#include "Enum.hpp"

class IGraph;
class ObstacleChooser;

/**
 * Représente une transition dans le réseau de pétri.
 * Une transition ne peut être connectée qu'à 2 noeuds.
 */
class IGate {
public:
    virtual ~IGate() {};

    /**
     * Attribue un id à la transition.
     */
    virtual void setId(Id nid) = 0;
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
     * Renvoie l'ID du noeud de la transition qui n'est pas celui passé en paramètre.
     */
    virtual Id getOtherNode(Id n) = 0;
    /**
     * Teste si un joeur peut passer la transition.
     * @param p Le joueur à tester.
     * @param origin Le noeud d'origine du joueur
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
     * Demande à la transition de changer d'état.
     */
    virtual void changeState() = 0;
    /**
     * Spécifie si la transition peut changer d'état.
     */
    virtual bool canChangeState() = 0;
    /**
     * Renvoie le nom de cet obstacle.
     */
    virtual std::string getName() = 0;
    /**
     * Modifie le noeud d'origine de la transition.
     */
    virtual void changeFirst(Id newFirst) = 0;


protected:
    friend ObstacleChooser;
    virtual IGate* allocate(IGraph* graph, Id first, Id second) = 0;
};

#endif // IGATE_HPP

