## Détails des Modules et Fichiers

### 1. `src/`

Ce dossier contient l'ensemble du code source du projet organisé en sous-modules spécialisés :

- **main.c**  
  Point d'entrée du programme. Il initialise le jeu, charge la carte et lance la boucle principale.

#### a. Module **engine/**

- **game_setup.c**

  - Configuration et initialisation des données de jeu.
  - Localise la position de spawn du joueur (`locate_character_spawn`).
  - Calcule le nombre total d'objets collectables (`calculate_item_total`).
  - Configure les données de niveau (`setup_level_data`).

- **system_manager.c**
  - Gestion du système et orchestration générale.
  - Gère les échecs d'initialisation (`handle_init_failure`).
  - Configure le système graphique (`configure_graphics_system`).
  - Initialise l'état de jeu (`initialize_game_state`).
  - Crée l'instance de jeu principale (`create_game_instance`).

#### b. Module **render/**

- **render_init.c**

  - Initialise le contexte graphique avec MiniLibX.
  - Crée la fenêtre et charge les textures/sprites nécessaires.

- **render_utils.c**
  - Fournit des fonctions supplémentaires pour manipuler les images.
  - Responsable du rendu visuel de tous les éléments du jeu.

#### c. Module **map/** - Architecture Modulaire Avancée

Le module map a été entièrement refactorisé selon une architecture modulaire respectant la norme 42 (max 5 fonctions par fichier, max 25 lignes par fonction) :

- **map_file_handler.c** (139 lignes, 5 fonctions)

  - **Responsabilité** : Gestion des fichiers et chargement des cartes
  - `verify_level_extension()` : Vérifie l'extension .ber
  - `calculate_level_height()` : Compte les lignes du fichier
  - `calculate_row_width()` : Calcule la largeur des lignes
  - `prepare_level_structure()` : Initialise la structure de carte
  - `load_game_level()` : Charge complètement un niveau depuis un fichier

- **map_structure_validator.c** (90 lignes, 3 fonctions)

  - **Responsabilité** : Validation de la structure géométrique
  - `verify_rectangular_shape()` : Vérifie la forme rectangulaire
  - `verify_boundary_walls()` : Vérifie l'intégrité des murs de bordure
  - `validate_map_structure()` : Orchestration de la validation structurelle

- **map_element_validator.c** (118 lignes, 5 fonctions)

  - **Responsabilité** : Validation des éléments de jeu
  - `is_valid_char()` : Vérifie la validité des caractères
  - `tally_game_elements()` : Compte chaque type d'élément
  - `verify_element_quantities()` : Valide les quantités requises
  - `verify_game_elements()` : Validation complète des éléments

- **map_connectivity_analyzer.c** (142 lignes, 4 fonctions)

  - **Responsabilité** : Analyse de connectivité et pathfinding
  - `duplicate_level_grid()` : Crée une copie de la carte
  - `mark_accessible_areas()` : Algorithme de flood-fill récursif
  - `locate_player_spawn()` : Trouve la position du joueur
  - `analyze_level_connectivity()` : Analyse complète de connectivité

- **map_accessibility_checker.c** (81 lignes, 2 fonctions)

  - **Responsabilité** : Vérification d'accessibilité des éléments
  - `verify_collectibles_accessibility()` : Vérifie l'accessibilité des collectibles
  - `verify_exit_accessibility()` : Vérifie l'accessibilité de la sortie

- **map_error_manager.c** (46 lignes, 1 fonction)

  - **Responsabilité** : Gestion centralisée des erreurs
  - `display_validation_error()` : Affiche les messages d'erreur spécifiques

- **map_render_engine.c** (77 lignes, 2 fonctions)

  - **Responsabilité** : Moteur de rendu de la carte
  - `draw_single_tile()` : Dessine une tuile spécifique
  - `display_complete_level()` : Effectue le rendu complet de la carte

- **map_main_validator.c** (35 lignes, 1 fonction)
  - **Responsabilité** : Orchestration générale des validations
  - `perform_complete_validation()` : Point d'entrée principal pour toutes les validations

#### d. Module **player/**

- **player_controller.c**
  - Gère les déplacements du joueur en réponse aux entrées clavier.
  - Vérifie que le mouvement est permis (pas de collision avec un mur).
  - Gère la logique de collecte des objets.
  - Met à jour la carte et le compteur de mouvement.

#### e. Module **utils/**

- **resource_manager.c**
  - Gère l'allocation et la libération de mémoire afin d'éviter les fuites.
  - Assure le nettoyage complet des ressources lors de la fermeture du programme.
  - Centralise la gestion des erreurs : affichage de messages explicites et arrêt du programme proprement en cas de problème.

### 2. `include/`

Ce dossier regroupe tous les fichiers d'en-tête (.h) qui déclarent les fonctions, structures et constantes utilisées par les différents modules.

- **so_long.h**

  - Fichier d'inclusion central qui inclut tous les autres headers.
  - Contient les includes système, les structures principales et les prototypes de fonctions.
  - Permet d'avoir un point d'inclusion unique pour tous les fichiers sources.

- **game.h**

  - Prototypes des fonctions du module engine (game_setup.c, system_manager.c).
  - Structures et constantes liées à l'initialisation du jeu.

- **map.h** - Header Restructuré

  - **Map File Handler** : Déclarations pour le chargement de fichiers
  - **Map Structure Validator** : Prototypes de validation structurelle
  - **Map Element Validator** : Fonctions de validation des éléments
  - **Map Connectivity Analyzer** : Analyse de connectivité
  - **Map Accessibility Checker** : Vérifications d'accessibilité
  - **Map Error Manager** : Gestion des erreurs
  - **Map Render Engine** : Moteur de rendu
  - **Map Main Validator** : Orchestration principale
  - **Utility Functions** : Fonctions utilitaires

- **player.h, graphics.h, utils.h**
  - Ces headers contiennent respectivement les prototypes de fonctions et structures spécifiques à chaque module.

### 3. `external/`

Ce dossier regroupe toutes les dépendances externes du projet :

- **libft/**

  - Contient la bibliothèque _libft_, utilisée pour compléter les fonctions standards en C (manipulation de chaînes de caractères, listes, etc.).
  - Elle est compilée et liée lors de la compilation du projet via le Makefile.

- **minilibx_mms_20200219/**

  - Version de MiniLibX pour macOS.
  - Bibliothèque graphique utilisée pour créer la fenêtre et gérer l'affichage.

- **minilibx-linux/**
  - Version de MiniLibX pour Linux.
  - Alternative à la version macOS pour la compatibilité multi-plateforme.

### 4. `asset/`

Ce dossier stocke toutes les ressources externes utilisées par le jeu :

- **images/**

  - Contient les fichiers XPM utilisés comme textures pour les différents éléments du jeu.

- **sounds/**

  - Ressources audio (si applicable).

- **Fichiers XPM à la racine :**
  - `collect.xpm` : Texture pour les objets à collecter
  - `exit.xpm` : Texture pour la sortie
  - `floor.xpm` : Texture pour le sol
  - `player.xpm` : Texture pour le joueur
  - `wall.xpm` : Texture pour les murs

### 5. `maps/`

Ce dossier contient les fichiers de cartes au format .ber :

- **valid/**

  - Cartes valides utilisées pour le jeu normal.
  - Exemples : `basic.ber`, `complex.ber`, `maze.ber`, `minimal.ber`

- **error/**
  - Cartes invalides utilisées pour tester la validation.
  - Exemples : `empty.ber`, `no_exit.ber`, `no_player.ber`, etc.

### 6. `docs/`

- **architecture.md**

  - Ce document qui décrit l'architecture du projet.

- **doc.md**
  - Documentation supplémentaire du projet.

### 7. Fichiers à la Racine

- **Makefile** - Mis à Jour pour la Nouvelle Architecture

  - Fichier de compilation automatique avec détection automatique du système d'exploitation.
  - **Sources mises à jour** :
    - `src/engine/game_setup.c`
    - `src/engine/system_manager.c`
    - `src/map/map_file_handler.c`
    - `src/map/map_structure_validator.c`
    - `src/map/map_element_validator.c`
    - `src/map/map_connectivity_analyzer.c`
    - `src/map/map_accessibility_checker.c`
    - `src/map/map_error_manager.c`
    - `src/map/map_render_engine.c`
    - `src/map/map_main_validator.c`
  - Gère la compilation des fichiers sources, la création des exécutables et la gestion des bibliothèques externes.
  - Inclut les règles `all`, `clean`, `fclean` et `re`.
  - Supporte macOS (avec minilibx_mms_20200219) et Linux (avec minilibx-linux).

- **so_long**

  - Exécutable compilé du jeu.

- **map.ber**

  - Fichier de carte par défaut pour les tests.

- **libmlx.dylib**
  - Bibliothèque MiniLibX copiée pour l'exécution sur macOS.

## Architecture Logicielle Refactorisée

### Flux de Données Modernisé

1. **Initialisation** :

   - `main.c` → `engine/system_manager.c::create_game_instance()`
   - `engine/game_setup.c::setup_level_data()` → `render/render_init.c`

2. **Chargement et Validation de Carte** :

   - `map/map_file_handler.c::load_game_level()`
   - `map/map_main_validator.c::perform_complete_validation()`
     - `map/map_structure_validator.c::validate_map_structure()`
     - `map/map_element_validator.c::verify_game_elements()`
     - `map/map_connectivity_analyzer.c::analyze_level_connectivity()`

3. **Rendu** :

   - `map/map_render_engine.c::display_complete_level()` → `render/render_utils.c`

4. **Interactions** :

   - `player/player_controller.c` → Mise à jour de l'état → Nouveau rendu

5. **Nettoyage** :
   - `utils/resource_manager.c`

### Gestion des Erreurs Centralisée

Le module `map/map_error_manager.c` centralise tous les messages d'erreur avec des codes spécifiques :

- `ERR_NO_PLAYER` : "Map must have exactly one starting point (P)"
- `ERR_MULTI_PLAYER` : "Map has multiple starting points"
- `ERR_NO_EXIT` : "Map must have exactly one exit (E)"
- `ERR_MULTI_EXIT` : "Map has multiple exits"
- `ERR_NO_COLLECT` : "Map must have at least one collectible (C)"
- `ERR_INVALID_CHAR` : "Map contains invalid character"
- `ERR_NOT_RECTANGLE` : "Map must be rectangular"
- `ERR_NO_WALLS` : "Map must be surrounded by walls"
- `ERR_MAP_TOO_SMALL` : "Map is too small"
- `ERR_NO_PATH` : "Map has no valid path"
- `ERR_MEMORY` : "Memory allocation failed"

### Conformité Norme 42

L'architecture respecte strictement la norme 42 :

- ✅ **Maximum 25 lignes par fonction**
- ✅ **Maximum 5 fonctions par fichier**
- ✅ **Documentation JSDoc complète en français**
- ✅ **Séparation claire des responsabilités**
- ✅ **Noms de fonctions descriptifs en français**
- ✅ **Headers organisés par module**

### Compatibilité Multi-Plateforme

Le Makefile détecte automatiquement le système d'exploitation et utilise la version appropriée de MiniLibX :

- macOS : `external/minilibx_mms_20200219/`
- Linux : `external/minilibx-linux/`

## Avantages de la Nouvelle Architecture

### 1. **Modularité Maximale**

- Chaque fichier a une responsabilité unique et bien définie
- Facilite la maintenance et les modifications ciblées
- Permet l'extension facile de nouvelles fonctionnalités

### 2. **Respect Strict de la Norme 42**

- Conformité totale aux règles de codage
- Code professionnel et standardisé
- Facilite la relecture et l'évaluation

### 3. **Séparation des Préoccupations**

- **Chargement** : `map_file_handler.c`
- **Validation structurelle** : `map_structure_validator.c`
- **Validation des éléments** : `map_element_validator.c`
- **Analyse de connectivité** : `map_connectivity_analyzer.c`
- **Vérification d'accessibilité** : `map_accessibility_checker.c`
- **Gestion d'erreurs** : `map_error_manager.c`
- **Rendu** : `map_render_engine.c`
- **Orchestration** : `map_main_validator.c`

### 4. **Documentation Professionnelle**

- Commentaires JSDoc complets en français
- Description détaillée de chaque fonction
- Paramètres et valeurs de retour documentés

### 5. **Testabilité Améliorée**

- Chaque module peut être testé indépendamment
- Fonctions spécialisées facilitent les tests unitaires
- Gestion d'erreur centralisée et cohérente

## Conclusion

L'architecture refactorisée du projet **so_long** représente une amélioration majeure :

- **src/** organisé en 8 modules map spécialisés + modules engine divisés
- **include/map.h** restructuré avec organisation par responsabilité
- **Makefile** adapté à la nouvelle structure
- **Conformité 100%** à la norme 42
- **Architecture modulaire** facilitant maintenance et extension
- **Documentation complète** en français avec JSDoc

Cette organisation modulaire avancée garantit un code maintenable, extensible et parfaitement conforme aux standards de l'École 42.
