# Phase 1

## API Graphique Vulkan

 Pour programmer notre engin physique, nous avons choisi d'utiliseer l'API graphique Vulkan. Etant donné la grande complexité de cette bibliothèque graphique, nous avons choisi de partir d'un engin graphique conçu pas à pas dans un tutoriel :

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

 C'est pour ces diversers raisons que nous n'avons pas encore pu intégrer le moteur graphique Vulkan à l'intérieur du projet.

 ## Classe de Vecteur3D

 Afin d'écrire notre classe de vecteur3D nous nous sommes appuié sur le cours.
 Nous avons choisi de surcharger les opérations '=', '+', '*', '-', '+=' et '-=' pour améliorer la lisibilité de la classe (plutôt que d'avoir à écrire de longs noms de méthodes pour les calculs de base).
 Par ailleurs, puisque les opérations de produit scalaire et vectoriel peuvent être ambigue ( '.' ou '*' ou 'x'), nous les avons implémentées dans des méthodes de classe.
 La principale difficulté rencontrée a été la sur utilisation de pointeurs que nous avons ensuite remplacés par des références.

 ## Classe de Particules

 Pour préparer la suite du projet, notre classe CPeParticule hérite d'une classe CPeMovable qu'elle peut être déplacée.
 La classe mère possède ainsi une référence sur une instance de la classe CPeTransform qui contient la position, l'orientation et la taille de l'objet.
 Pour l'instant (avec les particules) seule la position est utilisée.
 Le constructeur de la classe a été surchargé pour permettre de choisir ou non le 'damping' de la particule.

 ## Intégrateur

 En suivant les indications  du cours nous avons implémenté deux intégrateurs selon le niveau de précision souhaité (avec ou sans t**2).
 Une fois encore pour préparer la suite du projet, le prototype d'une fonction de somme de forces a été écrit. Son implémentation renvoie pour l'instant un vecteur (0., 0., 0.) pour être fonctionnel avec le calcul de l'accélaration.
 L'accélération dépend actuellement seulement du vecteur gravité.
 La seule erreur rencontrée fut la confusion entre une instance et ça référence. Elle a été remarqué car cela produisait des valeurs incohérentes en test.