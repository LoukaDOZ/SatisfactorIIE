#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../headers/interface.h"
#include "../headers/carte.h"
#include "../headers/structure.h"
#include "../headers/ligneDeProduction.h"
#include "../headers/personnel.h"
#include "../headers/variablesGlobales.h"
//#include "../headers/coordonne.h"
//#include "../headers/cout.h"
//#include "../headers/persoCarte.h"
//#include "../headers/plateau.h"
//#include "../headers/structure.h"
//#include "../headers/machine.h"

/*
* Différentes couleurs de texte possible
*/
typedef enum couleurTexte {
    NOIR,
    ROUGE,
    VERT,
    JAUNE,
    BLEU,
    VIOLET,
    CYAN,
    BLANC
} couleurTexte;

/*
* Transforme un typeRessource en chaîne de caractères lisible pour le joueur
* @param tr : typeRessource à convertir
* @return : Retourne la chaîne de caractères correspondant au typeRessource ou
* "typeRessource inconnu" si le typeRessource est inconnu
*/
char* string_of_ressource_FISA(typeRessource tr) {
    switch (tr) {
        case DD:
            return "DD";
        case E:
            return "E";
        default:
            return "typeRessource inconnu";
    }
}

/*
* Transforme un typeMachine en chaîne de caractères lisible pour le joueur
* @param tm : typeMachine à convertir
* @return : Retourne la chaîne de caractères correspondant au typeRessource ou
* "typeMachine inconnu" si le typeMachine est inconnu
*/
char* string_of_type_machine(typeMachine tm) {
    switch(tm) {
        case TAPIS:
            return "Tapis";
        case COLLECTEUR:
            return "Collecteur";
        case CROIX:
            return "Croix";
        case DECHETTERIE:
            return "Déchetterie";
        case RECYCLAGE:
            return "Recyclage";
        default:
            return "type_machine inconnu";
    }
}

/*
* Transforme un pointCard en chaîne de caractères lisible pour le joueur
* @param pc : pointCard à convertir
* @return : Retourne la chaîne de caractères correspondant au pointCard ou
* "pointCard inconnu" si le typeRessource est inconnu
*/
char* string_of_point_card(pointCard pc) {
    switch(pc) {
        case NORD:
            return "Nord";
        case EST:
            return "Est";
        case SUD:
            return "Sud";
        case OUEST:
            return "Ouest";
        default:
            return "pointCard inconnu";
    }
}

/*
* Change la couleur du texte
* Une fois le texte dans la nouvelle couleur écrit, revenir au blanc de préférence
* @param c : couleur du texte
*/
void definir_couleur_texte(couleurTexte c) {
    switch(c) {
        case NOIR:
            printf("\033[0;30m");
            break;
        case ROUGE:
            printf("\033[0;31m");
            break;
        case VERT:
            printf("\033[0;32m");
            break;
        case JAUNE:
            printf("\033[0;33m");
            break;
        case BLEU:
            printf("\033[0;34m");
            break;
        case VIOLET:
            printf("\033[0;35m");
            break;
        case CYAN:
            printf("\033[0;36m");
            break;
        default:    /* BLANC */
            printf("\033[0;37m");
            break;
    }
}

/*
* Retourne un entier désignant le type d'élément présent aux coordonnés x y
* @param plateau : plateau
* @param x : coordonnée x
* @param y : coordonnée y
* @return 0 si porte, 1 si source, 2 si machine et 3 si vide
*/
typeCase type_contenu_case(carte* plateau, int x, int y) {
    coord coordCase;
    setCoord(&coordCase, x, y, getTaille(plateau));

    if(compareCoord2(getCoordPorte(plateau), &coordCase) == 0) {
        return PORTE;
    } else {
        coord** sources = getCoordSources(plateau);

        for(int i = 0; i < NB_SOURCES_PLATEAU; i++) {
            if(compareCoord2(sources[i], &coordCase) == 0) {
                return SOURCE;
            }
        }
        ligneDeProduction* ldp = findByCoordListLDP(getListeLigneDeProduction(plateau), &coordCase, getTaille(plateau));
        if(ldp != NULL) {
            return LIGNEDEPROD;
        }
    }

    return VIDE;
}

void clear_stdin() {
    while(getchar() != '\n');
}

/*
* Lit un entier censé correspondre au choix d'une réponse
* @param demande : message qui précède la réponse de l'utilisateur
* @param var : pointeur sur la variable qui va recevoir la réponse
*/
void scanf_choix_question(char* demande, int* var) {
    definir_couleur_texte(BLANC);
    printf("%s : ", demande);
    definir_couleur_texte(CYAN);

    scanf("%d", var);
    clear_stdin();
    definir_couleur_texte(BLANC);
}

/*
* Lit une chaîne de caractères
* @param demande : message qui précède la réponse de l'utilisateur
* @param var : pointeur sur la variable qui va recevoir la réponse
*/
void scanf_string(char* demande, char* var) {
    definir_couleur_texte(BLANC);
    printf("%s : ", demande);
    definir_couleur_texte(CYAN);

    scanf("%s", var);
    clear_stdin();
    definir_couleur_texte(BLANC);
}

/*
* Ecrit une question
* @param question : message de la question
*/
void printf_question(char* question) {
    definir_couleur_texte(BLEU);
    printf("%s :\n", question);
    definir_couleur_texte(BLANC);
}

/*
* Ecrit une question demandant à l'utilisateur s'il est d'accord avec l'achat
* @param question : message de la question
* @param cout : cout du l'achat
*/
void printf_confimation_achat(char* question, cout* cout) {
    definir_couleur_texte(BLEU);
    printf("%s pour ", question);
    definir_couleur_texte(JAUNE);
    printf("%d E et %d DD", getCoutE(cout), getCoutDD(cout));
    definir_couleur_texte(BLEU);
    printf(" ?\n");
    definir_couleur_texte(BLANC);
}

/*
* Ecrit un choix à une question
* @param num : numéro que l'utilisateur devra taper pour choisir cette option
* @param nom : nom de l'option
* @pram nb_indentation : nombre d'indentations devant
*/
void printf_option_question(int num, char* nom, unsigned int nb_indentations) {
    for(unsigned int i = 0; i < nb_indentations; i++)
        printf("\t");
    definir_couleur_texte(CYAN);
    printf("%d", num);
    definir_couleur_texte(BLANC);
    printf(" : %s\n", nom);
}

/*
* Ecrit un choix payant à une question
* @param num : numéro que l'utilisateur devra taper pour choisir cette option
* @param nom : nom de l'option
* @param cout : cout du choix
* @pram nb_indentation : nombre d'indentations devant
*/
void printf_option_payante_question(int num, char* nom, char* description, cout* cout, unsigned int nb_indentations) {
    for(unsigned int i = 0; i < nb_indentations; i++)
        printf("\t");
    definir_couleur_texte(CYAN);
    printf("%d", num);
    definir_couleur_texte(BLANC);
    printf(" : %s", nom);
    definir_couleur_texte(JAUNE);
    printf(" (%d E, %d DD)\n", getCoutE(cout), getCoutDD(cout));
    
    for(unsigned int i = 0; i < nb_indentations; i++)
        printf("\t");
    definir_couleur_texte(CYAN);
    printf("Description :");
    definir_couleur_texte(BLANC);
    printf(" %s\n", description);
}

/*
* Affiche un message important à l'utilisateur
* @param type : nom désignant le type de message
* @param message : message
* @param couleur : couleur du message
*/
void printf_message_utilisateur(char* type, char* message, couleurTexte couleur) {
    definir_couleur_texte(couleur);
    printf("\n[Jeu] %s : %s\n\n", type, message);
    definir_couleur_texte(BLANC);
}

/*
* Affiche le succès d'une opération à l'utilisateur
* @param message : message décrivant le succès
*/
void printf_succes(char* message) {
    printf_message_utilisateur("SUCCES", message, VERT);
}

/*
* Affiche l'abandon d'une opération à l'utilisateur
* @param message : message décrivant l'abandon
*/
void printf_abandon(char* message) {
    printf_message_utilisateur("ABANDON", message, JAUNE);
}

/*
* Affiche une erreur à l'utilisateur
* @param message : message décrivant l'erreur
*/
void printf_erreur(char* message) {
    printf_message_utilisateur("ERREUR", message, ROUGE);
}

/*
* Affiche un titre
* @param s : chaîne à afficher
*/
void printf_titre(char* s) {
    definir_couleur_texte(VERT);
    printf("\n-------- %s ---------\n", s);
    definir_couleur_texte(BLANC);
}

/*
* Affiche les informations générales du tour
* @param plateau : plateau
*/
void printf_tour_info(carte* plateau) {
    definir_couleur_texte(VERT);
    printf("\n//////// DEBUT DU TOUR %d ////////\n", getNbTours(plateau));
    definir_couleur_texte(CYAN);
    printf("Nombre de ressources dans la porte : ");
    definir_couleur_texte(BLANC);
    printf("%d\n", getNbRessourcePortail(plateau));
    definir_couleur_texte(CYAN);
    printf("Nombre de déchets dans la porte : ");
    definir_couleur_texte(BLANC);
    printf("%d\n", getNbDechetPortail(plateau));
    definir_couleur_texte(CYAN);

    fise* fise = getInfoFise(plateau);
    fisa* fisa = getInfoFisa(plateau);
    cout* cfe = getProductionFISE(fise);
    cout* cfa = getProductionFISA(fisa);
    int nbfe = getFISE(plateau);
    int nbfa = getFISA(plateau);

    definir_couleur_texte(CYAN);
    printf("Nombre FISE : ");
    definir_couleur_texte(BLANC);
    printf("%d (", nbfe);
    definir_couleur_texte(JAUNE);
    printf("%d E + %d DD", getCoutE(cfe) * nbfe, getCoutDD(cfe) * nbfe);
    definir_couleur_texte(BLANC);
    printf(" / tour)\n");

    definir_couleur_texte(CYAN);
    printf("Nombre FISA : ");
    definir_couleur_texte(BLANC);
    printf("%d (", nbfa);
    definir_couleur_texte(JAUNE);
    printf("%d E ou %d DD", getCoutE(cfa) * nbfa, getCoutDD(cfa) * nbfa);
    definir_couleur_texte(BLANC);
    printf(" / 2 tours)\n");

    definir_couleur_texte(CYAN);
    printf("Type de ressources FISA : ");
    definir_couleur_texte(JAUNE);
    printf("%s\n", string_of_ressource_FISA(getTypeRessourceFISA(plateau)));
    definir_couleur_texte(BLANC);
}

/*
* Affiche la liste des personnels détenus par le joueur
* @param plateau : plateau
*/
void printf_liste_personnels(carte* plateau) {
    listePersonnel* lp = getListePersonnel(plateau);

    if(getNbPersonnelList(lp) > 0) {
        definir_couleur_texte(BLEU);
        personnelCarte* elt = getStartListPersonnel(lp);

        printf("Personnels achetés :\n");
        for(int i = 0; i < getNbPersonnelList(lp); i++) {
            if(i > 0)
                elt = getPersonnelSuivant(elt);

            personnel* p = getPersonnel(elt);

            printf("\t- %s\n", getNomPersonnel(p));
            printf("\t\t-> %s\n", getDescPersonnel(p));
        }
        definir_couleur_texte(BLANC);
    }
}

/*
* Affiche les ressources du joueur
* @param plateau : plateau
*/
void printf_ressources_joueur(carte* plateau) {
    cout* ressources_joueur = getRessourceJoueur(plateau);

definir_couleur_texte(CYAN);
    printf("Vos ressources : ");
    definir_couleur_texte(JAUNE);
    printf("%d E + %d DD\n", getCoutE(ressources_joueur), getCoutDD(ressources_joueur));
    definir_couleur_texte(BLANC);
}

/*
* Affiche un dessin de la carte
* @param plateau : plateau
*/
void printf_carte(carte* plateau) {
    printf("\ny\\x|");
    for(int i = 0; i < getTaille(plateau); i++) {
        printf("%*d |", 2, i);
    }
    printf("\n---+");
    
    for(int i = 0; i < getTaille(plateau); i++) {
        printf("---+");
    }
    printf("\n");

    listeLigneDeProduction* lLDP = getListeLigneDeProduction(plateau);
    for(int i = 0; i < getTaille(plateau); i++) {
        printf("%*d |", 2, i);

        for(int j = 0; j < getTaille(plateau); j++) {
            switch(type_contenu_case(plateau, j, i)) {
                case PORTE :    /* Porte */
                    definir_couleur_texte(VERT);
                    printf("PRT");
                    break;
                case SOURCE :    /* Source */
                    definir_couleur_texte(JAUNE);
                    printf("SRC");
                    break;
                case LIGNEDEPROD :    /* Machine */
                    definir_couleur_texte(CYAN);
                    coord coordCase;
                    setCoord(&coordCase, j, i, getTaille(plateau));
                    switch(getTypeMachine(getMachine(findByCoordListLDP(lLDP, &coordCase, getTaille(plateau))))) {
                        case COLLECTEUR:
                            printf("CLT");
                            break;
                        case TAPIS:
                            printf("TAP");
                            break;
                        case CROIX:
                            printf("CRX");
                            break;
                        case RECYCLAGE:
                            printf("RCG");
                            break;
                        case DECHETTERIE:
                            printf("DCT");
                            break;
                    }
                    break;
                case VIDE :    /* Vide */
                    printf("   ");
                    break;
            }

            definir_couleur_texte(BLANC);
            printf("|");
        }
        printf("\n---+");

        for(int i = 0; i < getTaille(plateau); i++) {
            printf("---+");
        }
        printf("\n");
    }
}

/*
* Ecrit les informations d'une cellule
* @param plateau : plateau
* @param x : position x de la cellule
* @param y : position y de la cellule
*/
void printf_info_cellule(carte* plateau, int x, int y) {
    switch(type_contenu_case(plateau, x, y)) {
        case PORTE :    /* Porte */
            definir_couleur_texte(VERT);
            printf("La case %d %d contient la porte :\n", x, y);

            printf("\tNombre de ressources : ");
            definir_couleur_texte(BLANC);
            printf("%d\n", getNbRessourcePortail(plateau));

            definir_couleur_texte(VERT);
            printf("\tNombre de déchets : ");
            definir_couleur_texte(BLANC);
            printf("%d\n", getNbDechetPortail(plateau));
            break;
        case SOURCE :    /* Source */
            definir_couleur_texte(JAUNE);
            printf("La case %d %d contient une source\n", x, y);
            definir_couleur_texte(BLANC);
            break;
        case LIGNEDEPROD : ;   /* Machine */
            coord coordCase;
            setCoord(&coordCase, x, y, getTaille(plateau));
            ligneDeProduction* ldp = findByCoordListLDP(
                    getListeLigneDeProduction(plateau), &coordCase, getTaille(plateau)
                );
            machine* m = getMachine(ldp);
            typeMachine tp = getTypeMachine(m);

            definir_couleur_texte(CYAN);
            printf("La case %d %d contient une machine :\n", x, y);
            printf("\tMachine : ");
            definir_couleur_texte(BLANC);
            printf("%s\n", string_of_type_machine(getTypeMachine(m)));

            definir_couleur_texte(CYAN);
            printf("\tNiveau : ");
            definir_couleur_texte(BLANC);
            printf("%d\n", getNiveauMachine(ldp));

            definir_couleur_texte(CYAN);
            printf("\tOrientation : ");
            definir_couleur_texte(BLANC);
            printf("%s\n", string_of_point_card(getOrientation(ldp)));

            int nb;
            pointCard* liste;

            getEntreeDynamique(ldp, &liste, &nb);
            if(nb > 0) {
                definir_couleur_texte(CYAN);
                printf("\tEntrées :\n");

                definir_couleur_texte(BLANC);
                for(int i = 0; i < nb; i++)
                    printf("\t\t- %s\n", string_of_point_card(liste[i]));
            }

            getSortieDynamique(ldp, &liste, &nb);
            if(nb > 0) {
                definir_couleur_texte(CYAN);
                printf("\tSorties :\n");

                definir_couleur_texte(BLANC);
                for(int i = 0; i < nb; i++)
                    printf("\t\t- %s\n", string_of_point_card(liste[i]));
            }

            definir_couleur_texte(CYAN);
            if(tp != TAPIS && tp != CROIX) {
                printf("\tStock : ");

                definir_couleur_texte(BLANC);
                if(tp == COLLECTEUR) {
                    printf("%d ressources + %d déchets = %d ", 
                        getStockCurRessource(ldp), getStockCurDechet(ldp), 
                        (getStockCurRessource(ldp) + getStockCurDechet(ldp)));
                } else {
                    printf("%d déchets ", getStockCurDechet(ldp));
                }
                printf("/ %d\n", getStockMax(ldp));

                definir_couleur_texte(CYAN);
                printf("\tCoût d'amélioration : ");
                definir_couleur_texte(JAUNE);
                printf("%d E et %d DD\n", getCoutAmeliorationE(m), getCoutAmeliorationDD(m));

                definir_couleur_texte(CYAN);
                printf("\tStock après amélioration : ");
                definir_couleur_texte(BLANC);
                printf("%d -> %d (+ %d)\n", getStockMax(ldp), 
                    (getStockMax(ldp) + getStockUp(m)), getStockUp(m));
            } else {
                printf("\t(Pas d'amélioration possible)\n");
            }

            definir_couleur_texte(CYAN);
            printf("\tCoût de destruction : ");
            definir_couleur_texte(JAUNE);
            printf("%d E et %d DD\n", getCoutDestructionE(m), getCoutDestructionDD(m));
            
            definir_couleur_texte(BLANC);
            break;
        case VIDE :    /* Vide */
            definir_couleur_texte(BLANC);
            printf("La case %d %d est vide\n", x, y);
            break;
    }
}

/*
* Demande à l'utilisateur de choisir une position x et y entre 0 et la taille du plateau
* et boucle tant qu'il n'a pas choisi ou qu'il n'a pas abandonné
* @param plateau : plateau
* @param x : variable qui accueille la position x
* @param y : variable qui accueille la position y
*/
void boucle_position_x_y(carte* plateau, int* x, int* y) {
    char question[45];

    sprintf(question, "Sélectionnez la position x entre 0 et %d", getTaille(plateau) - 1);
    printf_question(question);
    printf_option_question(-1, "Abandonner et Quitter", 1);

    while(*x < 0 || *x >= getTaille(plateau)) {
        scanf_choix_question("Position x", x);

        if(*x == -1)
            return;
    }

    sprintf(question, "Sélectionnez la position y entre 0 et %d", getTaille(plateau) - 1);
    printf_question(question);
    printf_option_question(-1, "Abandonner et Quitter", 1);

    while(*y < 0 || *y >= getTaille(plateau)) {
        scanf_choix_question("Position y", y);

        if(*y == -1)
            return;
    }
}

/*
* Propose à l'utilisateur de voir en détail les cases du plateau et leur contenu
* et boucle tant qu'il n'a pas choisi ou qu'il n'a pas abandonné
* @param plateau : plateau
*/
void boucle_obtenir_informations_carte(carte* plateau) {
    printf_titre("Obtenir plus d'informations");

    while(1) {
        int x = -1;
        int y = -1;

        printf_question("Sélectionnez une case pour obtenir plus d'informations sur son contenu");
        boucle_position_x_y(plateau, &x, &y);

        if(x == -1 || y == -1) {
            definir_couleur_texte(VERT);
            printf("-------- Fin d'obtention d'informations ---------\n\n");
            definir_couleur_texte(BLANC);
            return;
        }

        printf("=> ");
        printf_info_cellule(plateau, x, y);
    }
}

/*
* Demande à l'utilisateur de répondre Oui ou Non et boucle tant qu'il n'a pas choisi
*/
int boucle_oui_non() {
    printf_option_question(1, "Oui", 1);
    printf_option_question(2, "Non", 1);

    int choix = 0;
    while(choix < 1 || choix > 2)
        scanf_choix_question("Réponse", &choix);

    return (choix % 2);
}

/*
* Demande à l'utilisateur de confirmer une action payante
* @see boucle_oui_non
* @param question : question
* @param cout : cout de l'action si acceptée
*/
int confirmer_action_payante(char* question, cout* cout) {
    printf_confimation_achat(question, cout);
    return boucle_oui_non();
    
}

/*
* Dessine la carte
* @param plateau : pointeur sur la carte et les informations du joueur
*/
void dessiner_carte(carte* plateau) {
    printf_tour_info(plateau);
    printf_liste_personnels(plateau);
    printf_ressources_joueur(plateau);
    printf_carte(plateau);
    boucle_obtenir_informations_carte(plateau);
}

/*
* Demande la carte à l'utilisateur
* @return : Retourne la taille du plateau : 
*   10 : FACILE
*   20 : MOYEN
*   30 : GRAND
*/
int demander_taille_carte() {
    printf_titre("Choisir une taille de plateau");

    printf_question("Sélectionnez une taille de plateau");
    printf_option_question(1, "Facile (10x10)", 1);
    printf_option_question(2, "Moyen (20x20)", 1);
    printf_option_question(3, "Grand (30x30)", 1);

    int taille = 0;
    while(taille < 1 || taille > 3)
        scanf_choix_question("Taille du plateau", &taille);

    return taille * 10;
}

/*
* Demande à l'utilisateur de choisir une action à faire
* @return : Retourne structure actionJoueur de l'action choisie
*/
actionJoueur demander_action_suivante() {
    printf_titre("Choisir une action à réaliser");

    printf_question("Sélectionnez une action");
    printf_option_question(1, "Ajout d'une machine", 1);
    printf_option_question(2, "Amélioration d'une machine", 1);
    printf_option_question(3, "Suppression d'une machine", 1);
    printf_option_question(4, "Achat d'un personnel", 1);
    printf_option_question(5, "Recruter un FISE", 1);
    printf_option_question(6, "Recruter un FISA", 1);
    printf_option_question(7, "Changer le type des ressources produites par les FISA", 1);
    printf_option_question(8, "Terminer le tour", 1);
    printf_option_question(9, "Quitter la partie", 1);

    int action = 0;
    while(action < 1 || action > 9)
        scanf_choix_question("Action", &action);

    switch (action) {
        case 1 : 
            return AJOUT_MACHINE;
        case 2 :
            return AMELIORATION_MACHINE;
        case 3 :
            return SUPPRESSION_MACHINE;
        case 4 :
            return ACHAT_PERSONNEL;
        case 5 :
            return RECRUTER_FISE;
        case 6 :
            return RECRUTER_FISA;
        case 7 :
            return CHANGER_TYPE_RESSOURCE_FISA;
        case 9 :
            return QUITTER;
        default :
            return PASSER;
    }
}

/*
* Créé un type nouvelleMachine pour l'échec ou l'abandon de l'ajout de machine
* @see nouvelleMachine
* @see demander_ajout_machine
*/
nouvelleMachine generer_nouvelle_machine_abandon() {
    nouvelleMachine nm;
    nm.succes = 0;

    return nm;
}

/*
* Demande à l'utilisateur de placer une nouvelle machine
* @param plateau : pointeur sur la carte et les informations du joueur
* @param machines : liste des machines disponibles
* @param taille_liste_machines : nombre d'éléments de l'argument 'machines'
* @return : Retourne un type nouvelle_machine avec les informations obtenues, 
* un type nouvelleMachine non initialisé, avec l'attibut succes à 0,
* si taille_liste_machines <= 0 oi si le joueur annule la demande
*/
nouvelleMachine demander_ajout_machine(carte* plateau, machine** machines, int taille_liste_machines) {
    if(taille_liste_machines <= 0)
        return generer_nouvelle_machine_abandon();

    printf_titre("Ajouter une machine");

    int machine;
    int x;
    int y;
    int orientation;
    while(1) {
        machine = 0;
        orientation = 0;

        printf_question("Sélectionnez une machine");
        printf_option_question(-1, "Abandonner et Quitter", 1);
        for(int i = 0; i < taille_liste_machines; i++) {
            cout cout = getCoutConstruction(machines[i]);

            printf_option_payante_question(i + 1, 
                string_of_type_machine(getTypeMachine(machines[i])),
                getDescMachine(machines[i]), &cout, 1);
        }
        
        while(machine < 1 || machine > taille_liste_machines) {
            scanf_choix_question("Machine", &machine);

            if(machine == -1)
                return generer_nouvelle_machine_abandon();
        }

        while(1) {
            x = -1;
            y = -1;

            printf_carte(plateau);
            boucle_obtenir_informations_carte(plateau);

            printf_question("Sélectionnez la case où placer la nouvelle machine");
            boucle_position_x_y(plateau, &x, &y);

            if(x == -1 || y == -1)
                return generer_nouvelle_machine_abandon();

            if(type_contenu_case(plateau, x, y) == 2)
                break;
        }

        printf_question("Sélectionnez l'orientation de la machine");
        printf_option_question(-1, "Abandonner et Quitter", 1);
        printf_option_question(1, "Nord", 1);
        printf_option_question(2, "Est", 1);
        printf_option_question(3, "Sud", 1);
        printf_option_question(4, "Ouest", 1);

        while(orientation < 1 || orientation > 4) {
            scanf_choix_question("Orientation", &orientation);

            if(orientation == -1)
                return generer_nouvelle_machine_abandon();
        }

        cout c = getCoutConstruction(machines[machine - 1]);
        if(confirmer_action_payante("Etes-vous sûr de vouloir ajouter la machine", &c))
            break;
    }

    nouvelleMachine nm;
    nm.succes = 1;
    nm.x = x;
    nm.y = y;
    nm.machine = machines[machine - 1];
    if(orientation == 1) {
        nm.orientation = NORD;
    } else if(orientation == 2) {
        nm.orientation = EST;
    } else if(orientation == 3) {
        nm.orientation = SUD;
    } else {
        nm.orientation = OUEST;
    }

    return nm;
}

/*
* Demande à l'utilisateur de selectionner une machine pour l'améliorer ou la détruire
* @param plateau : pointeur sur la carte et les informations du joueur
* @param action : améliorer ou supprimer machine
* @see Voir structure actionJoueur
* @return : Retourne la ligneDeProduction de la machine choisie par le joueur, NULL si l'action
* donnée en argument n'est ni AMELIORATION_MACHINE, ni SUPPRESSION_MACHINE ou que le joueur
* annule la demande
*/
ligneDeProduction* demander_selection_machine(carte* plateau, actionJoueur action) {
    if(action != AMELIORATION_MACHINE && action != SUPPRESSION_MACHINE)
        return NULL;

    char* action_s = (action == AMELIORATION_MACHINE ? "améliorer" : "supprimer");

    printf_titre("Sélectionner une machine");

    int x;
    int y;
    while(1) {
        x = -1;
        y = -1;

        printf_carte(plateau);
        boucle_obtenir_informations_carte(plateau);

        printf_question("Sélectionnez la case où se trouve machine");
        boucle_position_x_y(plateau, &x, &y);

        if(x == -1 || y == -1)
            return NULL;

        if(type_contenu_case(plateau, x, y) != LIGNEDEPROD)
            continue;

        coord coordCase;
        setCoord(&coordCase, x, y, getTaille(plateau));
        machine* m = getMachine(findByCoordListLDP(
            getListeLigneDeProduction(plateau), &coordCase, getTaille(plateau)));

        if(action == AMELIORATION_MACHINE) {
            if(getTypeMachine(m) == TAPIS || getTypeMachine(m) == CROIX)
                continue;
        }

        cout cout;
        char question[80];

        if(action == AMELIORATION_MACHINE)
            cout = getCoutAmelioration(m);
        else
            cout = getCoutDestruction(m);

        sprintf(question, "Etes-vous sûr de vouloir %s la machine en position %d %d", 
            action_s, x, y);
        if(confirmer_action_payante(question, &cout))
            break;
    }

    coord coordCase;
    setCoord(&coordCase, x, y, getTaille(plateau));
    return findByCoordListLDP(getListeLigneDeProduction(plateau), &coordCase, getTaille(plateau));
}

/*
* Demande à l'utilisateur de choisir un nouveau membre du personnel à acheter
* @param plateau : pointeur sur la carte et les informations du joueur
* @param personnels : liste de tous les personnels disponibles dans le jeu
* @param taille_liste_personnels : nombre d'éléments de l'argument 'machines'
* @return : Retourne le personnel choisi par le joueur, NULL si taille_liste_personnels <= 0
* ou si le joueur annule la demande
*/
personnel* demander_achat_personnel(carte* plateau, personnel** personnels, int taille_liste_personnels) {
    if(taille_liste_personnels <= 0)
        return NULL;

    printf_titre("Acheter un personnel");
    printf_liste_personnels(plateau);
    
    int perso;
    while(1) {
        perso = 0;
        
        printf_question("Sélectionnez le personnel à acheter");
        printf_option_question(-1, "Abandonner et Quitter", 1);
        for(int i = 0; i < taille_liste_personnels; i++) {
            printf_option_payante_question(i + 1, getNomPersonnel(personnels[i]), 
                getDescPersonnel(personnels[i]), getCoutAchat(personnels[i]), 1);
        }

        scanf_choix_question("Personnel", &perso);

        if(perso == -1)
            return NULL;

        if(perso < 1 || perso > taille_liste_personnels)
            continue;

        cout* cout = getCoutAchat(personnels[perso - 1]);
        char question[80];

        sprintf(question, "Etes-vous sûr de vouloir acheter %s", getNomPersonnel(personnels[perso - 1]));
        if(confirmer_action_payante(question, cout))
            break;
    }
    return personnels[perso - 1];
}

/*
* Demander à l'utilisateur de confirmer son achat d'un FISE
* @param : plateau : plateau
* @return : 0 pour false, 1 pour true
*/
int confirmer_recruter_FISE(carte* plateau) {
    fise* fise = getInfoFise(plateau);
    cout* c = getProductionFISE(fise);

    printf_titre("Acheter un FISE");
    printf("Les FISE produisent ");
    definir_couleur_texte(JAUNE);
    printf("%d E %d DD", getCoutE(c), getCoutDD(c));
    definir_couleur_texte(BLANC);
    printf(" / tour\n");

    return confirmer_action_payante("Etes-vous sûr de vouloir acheter un FISE", 
        getCoutFISE(fise));
}

/*
* Demander à l'utilisateur de confirmer son achat d'un FISA
* @param : plateau : plateau
* @return : 0 pour false, 1 pour true
*/
int confirmer_recruter_FISA(carte* plateau) {
    fisa* fisa = getInfoFisa(plateau);
    cout* c = getProductionFISA(fisa);

    printf_titre("Acheter un FISA");
    printf("Les FISA produisent ");
    definir_couleur_texte(JAUNE);
    printf("%d E ou %d DD", getCoutE(c), getCoutDD(c));
    definir_couleur_texte(BLANC);
    printf(" / 2 tour\n");

    return confirmer_action_payante("Etes-vous sûr de vouloir acheter un FISA", 
        getCoutFISA(fisa));
}

/*
* Demande à l'utilisateur de choisir un type partie
* Remplissage des paramètres :
*   - type SOLO : rien
*   - type CREER_PARTIE : adresse uniquement
*   - type REJOINDRE_PARTIE : adresse et port
* @param adresse : récepteur de l'adresse
* @param port : récepteur du port
* @return : le type de partie
*/
typePartie demander_type_partie(char* adresse, int* port) {
    printf_titre("Choisir un type de partie");

    printf_question("Sélectionnez ce que vous voulez faire");
    printf_option_question(1, "Jouer seul", 1);
    printf_option_question(2, "Créer une partie multijoueur", 1);
    printf_option_question(3, "Rejoindre une partie multijoueur", 1);

    int choix = 0;
    while(choix < 1 || choix > 3)
        scanf_choix_question("Choix", &choix);

    if(choix == 1)
        return SOLO;
    else {
        if(choix == 3) {
            printf_question("Entrez une adresse IP");

            sprintf(adresse, "%s", "");
            while(strlen(adresse) == 0)
                scanf_string("Adresse IP", adresse);
        } else {
            sprintf(adresse, "127.0.0.1");
        }

        printf_question("Entrez un port");

        *port = -1;
        while(*port < 1)
            scanf_choix_question("Port", port);

        if(choix == 3)
            return REJOINDRE_PARTIE;
        
        return CREER_PARTIE;
    }
}

/*
* Affiche, à l'utilisateur, un message de fin de partie
* @param victoire : type victoire
* @param scoreJoueur : ressources restantes du joueur
* @param scoreAdverse : ressources restantes de l'adversaire
*/
void printf_fin_partie(typeFinPartie type_fin, int joueur, int adversaire) {
    definir_couleur_texte(VERT);
    printf("\n//////// PARTIE TERMINEE ////////\n");

    switch(type_fin) {
        case DEFAITE :
            definir_couleur_texte(BLANC);
            printf("------------ ");
            definir_couleur_texte(ROUGE);
            printf("Défaite");
            definir_couleur_texte(BLANC);
            printf(" ------------\n");
            break;
        case VICTOIRE :
            definir_couleur_texte(BLANC);
            printf("----------- ");
            definir_couleur_texte(VERT);
            printf("Victoire");
            definir_couleur_texte(BLANC);
            printf(" ------------\n");
            break;
        case VICTOIRE_PAR_DECONNEXION :
            definir_couleur_texte(BLANC);
            printf("--- ");
            definir_couleur_texte(VERT);
            printf("Victoire par déconnexion");
            definir_couleur_texte(BLANC);
            printf(" ----\n");
            break;
    }

    definir_couleur_texte(BLANC);
    printf("\nVos ressources manquantes : ");
    definir_couleur_texte(JAUNE);
    printf("%d\n", joueur);

    definir_couleur_texte(BLANC);
    printf("Ressources manquantes de votre adversaire : ");
    definir_couleur_texte(JAUNE);
    printf("%d\n", adversaire);
}

/*
* Affiche, à l'utilisateur, un message de fin de partie, pour une partie solo
* @param victoire : type victoire
* @param scoreJoueur : ressources restantes du joueur
*/
void printf_fin_partie_solo(typeFinPartie type_fin, int joueur) {
    definir_couleur_texte(VERT);
    printf("\n//////// PARTIE TERMINEE ////////\n");

    switch(type_fin) {
        case DEFAITE :
            definir_couleur_texte(BLANC);
            printf("------------ ");
            definir_couleur_texte(ROUGE);
            printf("Défaite");
            definir_couleur_texte(BLANC);
            printf(" ------------\n");
            break;
        case VICTOIRE :
            definir_couleur_texte(BLANC);
            printf("----------- ");
            definir_couleur_texte(VERT);
            printf("Victoire");
            definir_couleur_texte(BLANC);
            printf(" ------------\n");
            break;
        default :
            definir_couleur_texte(BLANC);
            printf("------ ");
            definir_couleur_texte(VERT);
            printf("Victoire inconnue");
            definir_couleur_texte(BLANC);
            printf(" --------\n");
    }

    definir_couleur_texte(BLANC);
    printf("\nVos ressources manquantes : ");
    definir_couleur_texte(JAUNE);
    printf("%d\n", joueur);
}

/*
* Affiche, à l'utilisateur, ses ressources restantes pour gagner et celles de l'adversaire
* @param joueur : ressources restantes du joueur
* @param adversaire : ressources restantes de l'adversaire
*/
void printf_ressource_restantes(int joueur, int adversaire) {
    definir_couleur_texte(BLANC);
    printf("Vos ressources manquantes : ");
    definir_couleur_texte(JAUNE);
    printf("%d\n", joueur);

    definir_couleur_texte(BLANC);
    printf("Ressources manquantes de votre adversaire : ");
    definir_couleur_texte(JAUNE);
    printf("%d\n", adversaire);
}