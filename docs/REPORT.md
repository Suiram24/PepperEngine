# Phase 1

## Architecture du projet

Afin de rendre le projet modulable, réutilisable, et facile à maintenir, il a été décidé de séparer les différent composant du moteur en différentes librairies internes, en limitant au strict minimum les dépendances.   
Un coding standard, améliorable en continue, a également été crée dans ce but de maintenabilité.    
Les schéma de l'architecture (brouillons, puis mise au propre quand ce sera fait) sont disponibles dans docs/graphs et sont consultables avec le logiciel draw.io.

![Schéma des dépendances des librairies, avec le moteur dépendant de PeRender et PePhysic, cette dernière dépendant de PeMaths](image.png)

Il a été décidé d'utiliser CMake car nous avions peu d'expérience dessus et que le maitriser est une compétence appréciable.

La première étape a donc été de créer le projet à partir de l'exemple ImGui GLFW + Vulkan (voir la section vulkan ci dessous) et du 
**[tutoriel officiel CMake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)** .

La mejeure partie du code a été déplacée dans la librairie PeRender, et les fonctions graphiques sont facilement accessibles à travers le singleton CPeRenderer, mais caché derrière une couche d'abstraction.

## API Graphique Vulkan

 Pour programmer notre engin physique, nous avons choisi d'utiliser l'API graphique Vulkan étant donnée sa grande compatibilité et son importance dans l'industrie du jeu vidéo actuellement. Etant donné la grande complexité de cette bibliothèque graphique, nous avons choisi de partir d'un engin graphique conçu pas à pas dans un tutoriel :

 > **[Vulkan Tutorial](https://vulkan-tutorial.com/)**
 >
 > par [Alexander Overvoorde](https://www.linkedin.com/in/overv/?originalSubdomain=nl)

 Afin de nous aider à intégrer ImGUI avec Vulkan, nous avons utilisé le tutoriel ci-dessous :

 > **[Vulkan ImGUI](https://frguthmann.github.io/posts/vulkan_imgui/)**
 >
 > par [François Guthmann](https://www.linkedin.com/in/frguthmann/?originalSubdomain=fr)

 La partie graphique avec Vulkan est particulièrement complexe. Nous n'avions pour la plupart que quelques connaissances sommaires en pipeline de rendu et l'utilisation de Vulkan n'a pas rendu les choses aisées. Nous avons eu d'énorme difficulté à lier le tutoriel d'Alexander Overvoorde avec l'exemple fourni par ImGUI. 
 
 En effet, Le fonctionnement de Vulkan avec ImGUI diffère de celui avec openGL et nécessite d'intégrer directement imGUI dans la pipeline de rendu de Vulkan.

 D'autant plus que la réalisation du tutoriel Vulkan nous a demandé un temps considérable étant donné que ce dernier est particulièrement long.

 C'est pour ces diversers raisons que nous n'avons pas encore pu intégrer le rendu 3D de Vulkan à l'intérieur du projet.

 ## Classe de Vecteur3D

 Afin d'écrire notre classe de vecteur3D nous nous sommes appuyés sur le cours.
 Nous avons choisi de surcharger les opérations '=', '+', '*', '-', '+=' et '-=' pour améliorer la lisibilité de la classe (plutôt que d'avoir à écrire de longs noms de méthodes pour les calculs de base).
 Par ailleurs, puisque les opérations de produit scalaire et vectoriel peuvent être ambigües ( '.' ou '*' ou 'x'), nous les avons implémentées dans des méthodes de classe.
 La principale difficulté rencontrée a été la sur-utilisation de pointeurs que nous avons ensuite remplacés par des références.

 ## Classe de Particules

 Pour préparer la suite du projet, notre classe CPeParticule hérite d'une classe CPeMovable indiquant qu'elle peut être déplacée physiquement.
 La classe mère possède ainsi une référence sur une instance de la classe CPeTransform qui contient la position, l'orientation et la taille de l'objet.
 Pour l'instant (avec les particules) seule la position est utilisée.
 Le constructeur de la classe a été surchargé pour permettre de choisir ou non le 'damping' de la particule.

 ## Intégrateur

 En suivant les indications  du cours nous avons implémenté deux intégrateurs selon le niveau de précision souhaité (avec ou sans t**2).
 Une fois encore pour préparer la suite du projet, le prototype d'une fonction de somme de forces a été écrite. Son implémentation renvoie pour l'instant un vecteur (0., 0., 0.) pour être fonctionnel avec le calcul de l'accélaration.
 L'accélération dépend actuellement seulement du vecteur gravité.
 La seule erreur rencontrée fut la confusion entre une instance et sa référence. Elle a été remarquée car cela produisait des valeurs incohérentes en test.

 ## Démonstration (jeu de tir)

 Afin de démontrer le fonctionnement de la librairie de physique, nous avons réalisé un jeu de démonstration très simple, ou il faut ajusté l'angle et la force d'un tir pour envoyer un ballon sur une cible.
 Le rendu 3D avec vulkan n'étant pas encore disponible, il a été décidé de réaliser un aperçu rapide avec ImGui pour ne pas perdre de temps.   
 L'utilisation de texture avec ImGui nécessitant plus de temps (implémentation de stb par exemple), nous avons simplement dessiné le parcours de la balle à chaque lancer en utilisant les AddLines de ImGui.
