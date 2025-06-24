# Module map/

### map_load.c

Nom de la fonction : check_file_extension
Description :
    Vérifie si le fichier fourni a l'extension .ber valide.
    Fonction statique utilisée par map_load.

Paramètres :
    • file (char *) : Chemin du fichier à vérifier

Valeur de retour :
    Retourne 1 si l'extension est .ber, 0 sinon.

Remarques :
    - Utilise ft_strrchr pour trouver le dernier point
    - Vérifie que l'extension fait exactement 4 caractères
    - Compare avec ".ber" en utilisant ft_strncmp

### map_validate.c

Nom de la fonction : validate_map
Description :
    Vérifie que la carte respecte toutes les règles du jeu.

Paramètres :
    • map (t_map *) : Pointeur vers la structure contenant la carte

Valeur de retour :
    Retourne MAP_OK si la carte est valide, sinon retourne un code d'erreur.

Remarques :
    - Vérifie le format rectangulaire
    - Vérifie la présence des murs
    - Vérifie la validité des éléments
    - Vérifie l'existence d'un chemin valide


### map_validate_utils.c

Nom de la fonction : count_elements
Description :
    Compte le nombre de chaque élément requis dans la carte (P, E, C).

Paramètres :
    • map (t_map *) : Pointeur vers la structure de la carte
    • p (int *) : Pointeur pour le nombre de positions de départ
    • e (int *) : Pointeur pour le nombre de sorties
    • c (int *) : Pointeur pour le nombre de collectibles

Valeur de retour :
    Aucune (void)

Remarques :
    - Parcourt la carte entière
    - Met à jour les compteurs via les pointeurs


Nom de la fonction : validate_count
Description :
    Vérifie que le nombre d'éléments dans la carte est valide.

Paramètres :
    • p (int) : Nombre de positions de départ
    • e (int) : Nombre de sorties
    • c (int) : Nombre de collectibles

Valeur de retour :
    Retourne 1 si les nombres sont valides, sinon retourne un code d'erreur.

Remarques :
    - Vérifie qu'il y a exactement un P et un E
    - Vérifie qu'il y a au moins un C
    - Affiche les messages d'erreur appropriés


### map_path.c

Nom de la fonction : find_player
Description :
    Trouve les coordonnées du joueur (P) dans la carte.

Paramètres :
    • map (t_map *) : Pointeur vers la structure de la carte

Valeur de retour :
    Retourne une structure t_pos contenant les coordonnées du joueur.

Remarques :
    - Retourne {-1, -1} si le joueur n'est pas trouvé
    - Fonction statique utilisée pour le pathfinding


Nom de la fonction : check_path
Description :
    Vérifie qu'il existe un chemin valide vers tous les collectibles et la sortie.

Paramètres :
    • map (t_map *) : Pointeur vers la structure de la carte

Valeur de retour :
    Retourne 1 si un chemin valide existe, 0 sinon.

Remarques :
    - Crée une copie de la carte pour le flood fill
    - Vérifie l'accessibilité de tous les collectibles
    - Libère la mémoire en cas d'erreur


## Module utils/

### memory_management.c

Nom de la fonction : free_char_tab
Description :
    Libère la mémoire allouée pour un tableau de chaînes de caractères.

Paramètres :
    • tab (char **) : Tableau de chaînes à libérer

Valeur de retour :
    Aucune (void)

Remarques :
    - Gère le cas où tab est NULL
    - Libère chaque chaîne puis le tableau lui-même