#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "IGraph.hpp"

class Graph : public IGraph {
public:
    Graph();

    virtual ~Graph();
    /**
     * Vide le graphe.
     */
    virtual void clear();
    /**
     * Teste la validit� d'un graphe.
     */
    virtual bool isValid();
    /**
     * Renvoie un noeud en fonction de son id.
     * @param nid L'id du noeud � r�cup�rer.
     * @return Une r�f�rence sur le noeud.
     */
    virtual INode* getNode(Id nid);
    /**
     * Renvoie une transition en fonction de son id.
     * @param nid L'id de la transition � r�cup�rer.
     * @return Une r�f�rence sur la transition.
     */
    virtual IGate* getGate(Id gid);
    /**
     * Ajoute un noeud au graphe.
     * @param node Le noeud � ajouter.
     * @return l'ID du noeud ajout�.
     */
    virtual Id addNode(INode* node);
    /**
     * Ajoute une transition au graphe.
     * @param gate La transition � ajouter un graphe.
     * @return l'ID de la transition ajout�e.
     */
    virtual Id addGate(IGate* gate);
    /**
     * Teste si un id de noeud est valide.
     * @param nid L'id du noeud � tester.
     * @return true si l'id est valide.
     */
    virtual bool isValidNode(Id nid);
    /**
     * Teste si un id de transition est valide.
     * @param gid L'id de la transition � tester.
     * @return true si l'id est valide.
     */
    virtual bool isValidGate(Id gid);
    /**
     * Renvoie le nombre de noeuds dans le graphe.
     */
    virtual unsigned int getNodeCount();
    /**
     * Renvoie le nombre de transition dans le graphe.
     */
    virtual unsigned int getGateCount();

private:
    std::vector<INode*> mNodes;
    std::vector<IGate*> mGates;
};

#endif // GRAPH_HPP

