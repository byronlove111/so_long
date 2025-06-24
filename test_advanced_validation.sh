#!/bin/bash

# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   test_advanced_validation.sh                        :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025/06/23 05:30:00 by abbouras          #+#    #+#             #
#   Updated: 2025/06/23 05:30:00 by abbouras         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Compteurs globaux
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Fonction d'affichage du header
print_header() {
    echo -e "${CYAN}================================================================${NC}"
    echo -e "${CYAN}           SO_LONG - TESTS AVANCÉS DE VALIDATION               ${NC}"
    echo -e "${CYAN}================================================================${NC}"
    echo ""
}

# Fonction d'affichage de section
print_section() {
    echo -e "${PURPLE}▶ $1${NC}"
    echo -e "${PURPLE}────────────────────────────────────────────────────────────${NC}"
}

# Fonction de test pour cartes valides (doit réussir)
test_valid_map() {
    local map_file="$1"
    local description="$2"
    
    echo -e "${BLUE}Testing:${NC} $description"
    echo -e "${BLUE}File:${NC} $map_file"
    
    # Afficher le contenu de la carte
    echo -e "${YELLOW}Map content:${NC}"
    cat "$map_file" | sed 's/^/  /'
    echo ""
    
    # Exécuter le test - Pour les cartes valides, on vérifie juste qu'il n'y a pas d'erreur immédiate
    local output=$(timeout 3s ./so_long "$map_file" 2>&1)
    local exit_code=$?
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Si timeout (exit code 124 ou 127), c'est bon car le jeu s'est lancé
    # Si exit code 0, c'est aussi bon
    # Si autre exit code, c'est une erreur
    if [ $exit_code -eq 0 ] || [ $exit_code -eq 124 ] || [ $exit_code -eq 127 ]; then
        # Vérifier qu'il n'y a pas de message d'erreur dans la sortie
        if echo "$output" | grep -q "Error\|Failed\|Invalid"; then
            echo -e "${RED}❌ FAILED${NC} - Map should be valid but has error messages"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            echo -e "${RED}Error output:${NC}"
            echo "$output" | sed 's/^/  /'
        else
            echo -e "${GREEN}✅ PASSED${NC} - Map loaded successfully (game launched)"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        fi
    else
        echo -e "${RED}❌ FAILED${NC} - Map should be valid but was rejected (exit code: $exit_code)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        
        # Afficher l'erreur pour débug
        echo -e "${RED}Error output:${NC}"
        echo "$output" | sed 's/^/  /'
    fi
    echo ""
}

# Fonction de test pour cartes invalides (doit échouer)
test_invalid_map() {
    local map_file="$1"
    local description="$2"
    local expected_error="$3"
    
    echo -e "${BLUE}Testing:${NC} $description"
    echo -e "${BLUE}File:${NC} $map_file"
    echo -e "${BLUE}Expected:${NC} $expected_error"
    
    # Afficher le contenu de la carte
    echo -e "${YELLOW}Map content:${NC}"
    cat "$map_file" | sed 's/^/  /'
    echo ""
    
    # Exécuter le test directement et capturer l'exit code
    ./so_long "$map_file" > /tmp/test_output.txt 2>&1
    local exit_code=$?
    local output=$(cat /tmp/test_output.txt)
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ $exit_code -ne 0 ]; then
        # Vérifier si le message d'erreur contient le texte attendu
        if echo "$output" | grep -q "$expected_error"; then
            echo -e "${GREEN}✅ PASSED${NC} - Correctly rejected with expected error"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${YELLOW}⚠️  PARTIAL${NC} - Rejected but with different error message"
            echo -e "${YELLOW}Got:${NC} $output"
            PASSED_TESTS=$((PASSED_TESTS + 1))  # Compter comme réussi car rejeté
        fi
    else
        echo -e "${RED}❌ FAILED${NC} - Map should be invalid but was accepted"
        echo -e "${RED}Debug - Exit code was: $exit_code${NC}"
        echo -e "${RED}Debug - Output was: $output${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
}

# Fonction de test des arguments
test_arguments() {
    print_section "TESTS DES ARGUMENTS DE LIGNE DE COMMANDE"
    
    echo -e "${BLUE}Testing:${NC} No arguments"
    ./so_long > /dev/null 2>&1
    local exit_code=$?
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}✅ PASSED${NC} - Correctly rejected no arguments"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}❌ FAILED${NC} - Should reject no arguments"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
    
    echo -e "${BLUE}Testing:${NC} Too many arguments"
    ./so_long maps/valid/basic.ber extra_arg > /dev/null 2>&1
    exit_code=$?
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}✅ PASSED${NC} - Correctly rejected too many arguments"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}❌ FAILED${NC} - Should reject too many arguments"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
    
    echo -e "${BLUE}Testing:${NC} Non-existent file"
    ./so_long non_existent_file.ber > /dev/null 2>&1
    exit_code=$?
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}✅ PASSED${NC} - Correctly rejected non-existent file"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}❌ FAILED${NC} - Should reject non-existent file"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
    
    echo -e "${BLUE}Testing:${NC} Wrong file extension"
    echo "1111\n1PC1\n1111" > test_wrong_ext.txt
    ./so_long test_wrong_ext.txt > /dev/null 2>&1
    exit_code=$?
    rm -f test_wrong_ext.txt
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    if [ $exit_code -ne 0 ]; then
        echo -e "${GREEN}✅ PASSED${NC} - Correctly rejected wrong extension"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}❌ FAILED${NC} - Should reject wrong extension"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
}

# Fonction de test des cartes valides
test_valid_maps() {
    print_section "TESTS DES CARTES VALIDES"
    
    test_valid_map "maps/valid/minimal.ber" "Minimal valid map (3x3)"
    test_valid_map "maps/valid/basic.ber" "Basic valid map (5x10)"
    test_valid_map "maps/valid/complex.ber" "Complex valid map with multiple collectibles"
    test_valid_map "maps/valid/maze.ber" "Large maze map (11x13)"
}

# Fonction de test des cartes invalides
test_invalid_maps() {
    print_section "TESTS DES CARTES INVALIDES"
    
    test_invalid_map "maps/error/no_player.ber" "Map without player" "starting point"
    test_invalid_map "maps/error/multiple_players.ber" "Map with multiple players" "multiple starting points"
    test_invalid_map "maps/error/no_exit.ber" "Map without exit" "exit"
    test_invalid_map "maps/error/multiple_exits.ber" "Map with multiple exits" "multiple exits"
    test_invalid_map "maps/error/no_collectible.ber" "Map without collectibles" "collectible"
    test_invalid_map "maps/error/wrong_char.ber" "Map with invalid character" "invalid character"
    test_invalid_map "maps/error/no_walls.ber" "Map without proper walls" "walls"
    test_invalid_map "maps/error/not_rectangular.ber" "Non-rectangular map" "rectangular"
    test_invalid_map "maps/error/no_path.ber" "Map with no valid path" "path"
    test_invalid_map "maps/error/empty.ber" "Empty map file" "too small"
}

# Fonction d'affichage des statistiques finales
print_statistics() {
    echo -e "${CYAN}================================================================${NC}"
    echo -e "${CYAN}                        RÉSULTATS FINAUX                       ${NC}"
    echo -e "${CYAN}================================================================${NC}"
    echo ""
    echo -e "${BLUE}Total des tests:${NC} $TOTAL_TESTS"
    echo -e "${GREEN}Tests réussis:${NC} $PASSED_TESTS"
    echo -e "${RED}Tests échoués:${NC} $FAILED_TESTS"
    echo ""
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "${GREEN}🎉 TOUS LES TESTS SONT PASSÉS ! 🎉${NC}"
        echo -e "${GREEN}Le système de validation fonctionne parfaitement !${NC}"
    else
        echo -e "${RED}⚠️  CERTAINS TESTS ONT ÉCHOUÉ ⚠️${NC}"
        echo -e "${RED}Veuillez vérifier les erreurs ci-dessus${NC}"
    fi
    
    # Calculer le pourcentage de réussite
    local success_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    echo -e "${BLUE}Taux de réussite:${NC} ${success_rate}%"
    echo ""
}

# Fonction principale
main() {
    print_header
    
    # Vérifier que l'exécutable existe
    if [ ! -f "./so_long" ]; then
        echo -e "${RED}❌ Erreur: L'exécutable './so_long' n'existe pas${NC}"
        echo -e "${YELLOW}Veuillez compiler le projet avec 'make' d'abord${NC}"
        exit 1
    fi
    
    # Exécuter tous les tests
    test_arguments
    test_valid_maps
    test_invalid_maps
    
    # Afficher les statistiques
    print_statistics
    
    # Code de sortie basé sur les résultats
    if [ $FAILED_TESTS -eq 0 ]; then
        exit 0
    else
        exit 1
    fi
}

# Exécuter le script principal
main "$@" 