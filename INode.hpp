#ifndef INODE_HPP
#define INODE_HPP

#include <vector>

#include "Enum.hpp"

/**
 * Repr�sente un noeud dans le r�seau de p�tri.
 * Un noeud peut �tre connect� � d'autres noeuds par le biais de transitions.
 */
class INode {
public:
    virtual ~INode() {};
    /**
     * Attribue un id au noeud.
     */
    virtual void setId(Id nid) = 0;
    /**
     * Renvoie l'ID du noeud.
     */
    virtual Id getID() = 0;
    /**
     * Renvoie les transitions accessiblent pour un joueur.
     * @param p Le joueur pour lequel on veux les transitions.
     * @return La liste des Id des transitions accessiblent.
     */
    virtual std::vector<Id> getTransitions(Perso p) = 0;
    /**
     * Renvoie les transitions accessiblent par ce noeud.
     * @return La liste des Id des transitions accessiblent.
     */
    virtual std::vector<Id> getTransitions() = 0;
    /**
     * Ajoute une transition au noeud.
     */
    virtual void addTransition(Id gid) = 0;
    /**
     * Renvoie le type du noeud.
     */
    virtual NodeType getType() = 0;
};

#endif // INODE_HPP
