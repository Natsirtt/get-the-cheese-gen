#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include "INode.hpp"

class IGraph;

class Node : public INode {
public:
    Node(IGraph* graph, NodeType type);

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
private:
    IGraph* mGraph;
    Id mId;
    std::vector<Id> mGates;
    std::map<Perso, std::vector<Id>> mGatesMap;
    NodeType mType;
};

#endif // NODE_HPP

