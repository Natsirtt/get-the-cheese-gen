#ifndef IGRAPH_HPP
#define IGRAPH_HPP

#include "Enum.hpp"

class INode;
class IGate;

/**
 * R�pr�sente un r�seau de p�tri.
 * Tous les noeuds et transitions sont acc�d�s par le biais d'un ID.
 */
class IGraph {
public:
    virtual ~IGraph() {};

    /**
     * Teste la validit� d'un graphe.
     */
    virtual bool isValid() = 0;
    /**
     * Renvoie un noeud en fonction de son id.
     * @param nid L'id du noeud � r�cup�rer.
     * @return Une r�f�rence sur le noeud.
     * NOTE : La r�f�rence peut �tre invalid�e par
     *          la modification du graphe (ajout de noeud, etc...)
     */
    virtual INode& getNode(Id nid) = 0;
    /**
     * Renvoie une transition en fonction de son id.
     * @param nid L'id de la transition � r�cup�rer.
     * @return Une r�f�rence sur la transition.
     * NOTE : La r�f�rence peut �tre invalid�e par
     *          la modification du graphe (ajout de transitions, etc...)
     */
    virtual IGate& getGate(Id gid) = 0;
    /**
     * Ajoute un noeud au graphe.
     * @param node Le noeud � ajouter.
     * @return l'ID du noeud ajout�.
     * NOTE : Ne plus se servir du noeud une fois ajout�
     *          (R�cup�rer une r�f�rence avec getNode(..) plutot).
     */
    virtual Id addNode(INode&& node);
    /**
     * Ajoute une transition au graphe.
     * @param gate La transition � ajouter un graphe.
     * @return l'ID de la transition ajout�e.
     * NOTE : Ne plus se servir de la transition une fois ajout�
     *          (R�cup�rer une r�f�rence avec getGate(..) plutot).
     */
    virtual Id addGate(IGate&& gate);
};

#endif // IGRAPH_HPP

