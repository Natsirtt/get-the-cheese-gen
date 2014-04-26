### Fonctionnement du générateur de niveaux ###

--- Informations générales ---

Le générateur de niveaux permet de générer des réseaux de pétri de manière
pseudo-aléatoire, représentés sous la forme de réseaux de pétri (ou réseau
place/transition).
Un réseau de pétri est un graphe biparti composé de deux types de noeuds
différents (les places et les transitions), et dont aucun arc du graphe ne relie
deux noeuds de même type.
Le graphe choisi de créer des embranchements ou de terminer des branches (ou le
graphe) selon certaines probabilités.
Le générateur représente une salle dite "safe" (qui ne présente pas de danger
pour le joueur) par une place, et un obstacle (souvent une salle présentant un
danger ou un blocage pour le joueur) par une transition.

Une place est représentée par un petit carré blanc, et chacune est numérotée.
Une transition est représentée par un gros carré blanc.

De plus, des transitions spéciales appellées "Activator" correspondent à des
interrupteurs, ouvrant l'accès à des salles spéciales appellées "Door". Chaque
association d'un Activator à une Door est représenté par un segment de couleur
vert entre ces deux derniers. Cette représentation est purement informelle
et ne correspond à aucune notion mathématique au niveau du réseau de pétri
sous-jacent.
Il est à noter que l'algorithme de génrération du graphe s'assure qu'une
association Acivator/Door ne bloque jamais le niveau (pas d'Activator
placé derrière sa propre Door, ni d'exclusion mutuelles de deux assications).

--- Utilisation ---

Lors de l'execution du programme, un niveau se génére.
Est alors présenté le réseau de pétri représentant le niveau.
De plus, le programme propose une Interface Utilisateur (UI) sommaire ainsi
que de raccourcis clavier.

* Interface Utilisateur

Cinq boutons et une liste d'items composent l'interface utilisateur.

La liste d'item affiche chaque fichier trouvé dans le dossier d'exécution
du programme et ayant une extention ".gra". Cette extention correspond
au format de sauvegarde d'un réseau de pétri par le programme, permettant
la sauvegarde et le chargement de réseau même après arrêt de l'exécution
et lancement d'une nouvelle instance du programme.

Le premier bouton accessible, "Charger", s'utilise de concert avec la liste
de sélection. Une fois un niveau sélectionné dans la liste (il sera alors
encadré en blanc), cliquer sur le bouton "Charger" permettra de charger en
mémoire le niveau précédement sauvegarder.
Attention ! Tout chargement de niveau entraîne la perte du graphe actuellement
en consultation.

Le deuxième bouton accessible, "Sauvegarder", permet de sauvegarder dans un
fichier ".gra" le graphe actuellement en consultation. Le programme enregistrera
le graphe dans un fichier qui sera nommé GrapheN.gra où N est le numéro suivant
disponible pour le nommage du fichier.

Le troisième bouton, "Supprimer", fonctionne lui aussi avec la liste
de sélection de niveaux. Une fois un niveau sélectionné (encadré en blanc),
cliquer sur le bouton "Supprimer" supprimera définitivement et sans plus de
cérémonie le fichier ".gra", représentant un niveau, sélectionné.

Le quatrième bouton, "Regénérer", va relancer l'algorithme de génération aléatoire
afin de générer un nouveau niveau. Attention, appuyer sur ce bouton implique
la perte du niveau en court de visualisation ci celui-ci n'a pas été sauvegardé !

Le cinquième et dernier bouton, "Exporter", permet de lancer l'algorithme
transformant le graphe en un graphe 3D, effectuant des tests d'intégrité sur
celui-ci et enfin, si tout s'est bien passé, exportant au format T3D (format
de description d'un niveau dans l'Unreal Development Kit) le niveau ainsi généré.
Le fichier est toujours "result.t3d". Si le fichier existait précédement, il est
écrasé, attention aux pertes de données !

* Raccourcis clavier

Deux touches du clavier permettent d'effectuer les deux actions les plus
importantes du programme rapidement.

La touche "espace" est un raccourci pour le bouton "Regénérer".

La touche "g" est un raccourci pour le bouton "Exporter".

