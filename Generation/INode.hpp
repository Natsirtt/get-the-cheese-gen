#ifndef INODE_HPP
#define INODE_HPP

#include <vector>

#include "Enum.hpp"
#include "3D/Area.hpp"

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
    /**
     * Renvoie la profondeur du noeud.
     */
    virtual int getDepth() = 0;
    /**
     * Marque le noeud comme �tant sur le chamin pour aller � la fin.
     */
    virtual void setOnEndPath(bool endPath) = 0;
    /**
     * Test si le noeud est marqu� comme �tant sur le chemin de fin.
     */
    virtual bool isOnEndPath() = 0;
    /**
     * Supprime une transition.
     * @param gate l'id de la transition � supprimer.
     */
    virtual void deleteGate(Id gate) = 0;
    /**
     * Remplace un obstacle par un nouvel obstacle.
     * @param oldGate l'id de l'ancien obstacle.
     * @param newGate l'id du nouvel obstacle.
     */
    virtual void changeGate(Id oldGate, Id newGate) = 0;
    /**
     * Lie ce noeud avec un obstacle.
     */
    virtual void linkGate(Id gid) = 0;
    /**
     * Renvoie l'obstacle li�.
     * @return ID_ERROR si aucun obstacle n'est li�.
     */
    virtual Id getLinkedGate() = 0;
    /**
     * Renvoie la repr�sentation de l'obstacle.
     */
    virtual Area getArea() = 0;
};

#endif // INODE_HPP

