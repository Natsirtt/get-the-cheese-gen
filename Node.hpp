#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include "INode.hpp"

class IGraph;

class Node : public INode {
public:
    Node(IGraph* graph, NodeType type, int depth);

    virtual ~Node();
    /**
     * Attribue un id au noeud.
     */
    virtual void setId(Id nid);
    /**
     * Renvoie l'ID du noeud.
     */
    virtual Id getID();
    /**
     * Renvoie les transitions accessiblent pour un joueur.
     * @param p Le joueur pour lequel on veux les transitions.
     * @return La liste des Id des transitions accessiblent.
     */
    virtual std::vector<Id> getTransitions(Perso p);
    /**
     * Renvoie les transitions accessiblent par ce noeud.
     * @return La liste des Id des transitions accessiblent.
     */
    virtual std::vector<Id> getTransitions();
    /**
     * Ajoute une transition au noeud.
     */
    virtual void addTransition(Id gid);
    /**
     * Renvoie le type du noeud.
     */
    virtual NodeType getType();
    /**
     * Renvoie la profondeur du noeud.
     */
    virtual int getDepth();
    /**
     * Marque le noeud comme étant sur le chamin pour aller à la fin.
     */
    virtual void setOnEndPath(bool endPath);
    /**
     * Test si le noeud est marqué comme étant sur le chemin de fin.
     */
    virtual bool isOnEndPath();
    /**
     * Remplace un obstacle par un nouvel obstacle.
     * @param oldGate l'id de l'ancien obstacle.
     * @param newGate l'id du nouvel obstacle.
     */
    virtual void changeGate(Id oldGate, Id newGate);
    /**
     * Lie ce noeud avec un obstacle.
     */
    virtual void linkGate(Id gid);
    /**
     * Renvoie l'obstacle lié.
     * @return ID_ERROR si aucun obstacle n'est lié.
     */
    virtual Id getLinkedGate();
private:
    IGraph* mGraph;
    Id mId;
    std::vector<Id> mGates;
    NodeType mType;
    int mDepth;
    bool mIsOnEndPath;

    Id mGate;
};

#endif // NODE_HPP

