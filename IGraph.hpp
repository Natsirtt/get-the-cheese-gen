#ifndef IGRAPH_HPP
#define IGRAPH_HPP

#include "Enum.hpp"

class INode;
class IGate;

/**
 * Réprésente un réseau de pétri.
 * Tous les noeuds et transitions sont accédés par le biais d'un ID.
 */
class IGraph {
public:
    virtual ~IGraph() {};

    /**
     * Vide le graphe.
     */
    virtual void clear() = 0;

    /**
     * Teste la validité d'un graphe.
     */
    virtual bool isValid() = 0;
    /**
     * Renvoie un noeud en fonction de son id.
     * @param nid L'id du noeud à récupérer.
     * @return Une référence sur le noeud.
     * NOTE : La référence peut être invalidée par
     *          la modification du graphe (ajout de noeud, etc...)
     */
    virtual INode* getNode(Id nid) = 0;
    /**
     * Renvoie une transition en fonction de son id.
     * @param nid L'id de la transition à récupérer.
     * @return Une référence sur la transition.
     * NOTE : La référence peut être invalidée par
     *          la modification du graphe (ajout de transitions, etc...)
     */
    virtual IGate* getGate(Id gid) = 0;
    /**
     * Ajoute un noeud au graphe.
     * @param node Le noeud à ajouter.
     * @return l'ID du noeud ajouté.
     * NOTE : Ne plus se servir du noeud une fois ajouté
     *          (Récupérer une référence avec getNode(..) plutot).
     */
    virtual Id addNode(INode* node) = 0;
    /**
     * Ajoute une transition au graphe.
     * @param gate La transition à ajouter un graphe.
     * @return l'ID de la transition ajoutée.
     * NOTE : Ne plus se servir de la transition une fois ajouté
     *          (Récupérer une référence avec getGate(..) plutot).
     */
    virtual Id addGate(IGate* gate) = 0;
    /**
     * Teste si un id de noeud est valide.
     * @param nid L'id du noeud à tester.
     * @return true si l'id est valide.
     */
    virtual bool isValidNode(Id nid) = 0;
    /**
     * Teste si un id de transition est valide.
     * @param gid L'id de la transition à tester.
     * @return true si l'id est valide.
     */
    virtual bool isValidGate(Id gid) = 0;
    /**
     * Renvoie le nombre de noeuds dans le graphe.
     */
    virtual unsigned int getNodeCount() = 0;
    /**
     * Renvoie le nombre de transition dans le graphe.
     */
    virtual unsigned int getGateCount() = 0;
};

#endif // IGRAPH_HPP

