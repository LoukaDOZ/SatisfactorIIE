#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#include "../headers/carte.h"
#include "../headers/interface.h"
#include "../headers/client.h"
#include "../headers/serveur.h"

int main(void) {
    srand(time(NULL)); 
    char adresse[128];
    int port = -1;
    typePartie type_partie = demander_type_partie(adresse, &port);

    pid_t pid = -1;
    int client_socket = -1;
    if(type_partie != SOLO) {
        if(type_partie == CREER_PARTIE) {
            pid = fork();

            if (pid == -1) {
                perror("fork");
                return EXIT_FAILURE;
            } else if (pid == 0) {
                lancer_serveur(port);
                return EXIT_SUCCESS;
            }

            printf_succes("Lancement du serveur");
            sleep(3);
        }

        printf_succes("Connexion au serveur");
        client_socket = lancer_client(adresse, port);
    }
    
    int tailleCarte = 0;
    if(type_partie == REJOINDRE_PARTIE) {
        /*err ? = */lire_message_serveur(client_socket, &tailleCarte);
    } else {
        tailleCarte = demander_taille_carte();

        if(type_partie == CREER_PARTIE) {
            /*err ? = */envoyer_message_serveur(client_socket, tailleCarte);
            printf_succes("En attente de joueur");
        }
    }

    /* Création de la carte sur laquelle le joueur jouera sa partie */
    carte* plateau = creationCarte(tailleCarte);

    /* Initialisation du personnel */
    int taille_liste_personnel;
    personnel **liste_personnel;
    init_personnel(&liste_personnel, &taille_liste_personnel);

    /* Initialisation des machines */
    int taille_liste_machines;
    machine** liste_machines;
    init_machines(&liste_machines, &taille_liste_machines);
    int quitter = 0;
    int ressourcesAdversaire = 0;
    typeFinPartie tfp = DEFAITE;
    /* Boucle principale du jeu dans laquelle se déroule la partie */

    coord cc1;
    coord cc2;
    coord cc3;
    coord cc4;
    coord cc5;
    coord cc6;
    coord cc7;
    setCoord(&cc1, 1, 0, getTaille(plateau));
    setCoord(&cc2, 2, 0, getTaille(plateau));
    setCoord(&cc3, 2, 1, getTaille(plateau));
    setCoord(&cc4, 2, 2, getTaille(plateau));
    setCoord(&cc5, 1, 2, getTaille(plateau));
    setCoord(&cc6, 1, 1, getTaille(plateau));
    setCoord(&cc7, 3, 0, getTaille(plateau));
    
    achatMachine(
        getListeLigneDeProduction(plateau),
        liste_machines[0],
        &cc1, 
        EST, 
        getRessourceJoueur(plateau),
        plateau
    );
    achatMachine(
        getListeLigneDeProduction(plateau),
        liste_machines[1],
        &cc2, 
        EST, 
        getRessourceJoueur(plateau),
        plateau
    );
    achatMachine(
        getListeLigneDeProduction(plateau),
        liste_machines[2],
        &cc3, 
        NORD, 
        getRessourceJoueur(plateau),
        plateau
    );
    achatMachine(
        getListeLigneDeProduction(plateau),
        liste_machines[3],
        &cc4, 
        NORD, 
        getRessourceJoueur(plateau),
        plateau
    );
    achatMachine(
        getListeLigneDeProduction(plateau),
        liste_machines[4],
        &cc5, 
        EST, 
        getRessourceJoueur(plateau),
        plateau
    );
    achatMachine(
        getListeLigneDeProduction(plateau),
        liste_machines[0],
        &cc6, 
        NORD, 
        getRessourceJoueur(plateau),
        plateau
    );
    achatMachine(
        getListeLigneDeProduction(plateau),
        liste_machines[1],
        &cc7, 
        EST, 
        getRessourceJoueur(plateau),
        plateau
    );
    
    while(1) {
        if(quitter) {
            tfp = DEFAITE;
            break;
        } else if(type_partie != SOLO) {
            int retour_serveur;
            /*err ? = */envoyer_message_serveur(client_socket, 
                RESSOURCES_FIN_PARTIE - getNbRessourcePortail(plateau));
            /*err ? = */lire_message_client(client_socket, &retour_serveur);

            if(retour_serveur < 0) {
                switch(retour_serveur) {
                    case -1 :
                        tfp = DEFAITE;
                        break;
                    case -2 : 
                        tfp = VICTOIRE;
                        break;
                    case -3 : 
                        tfp = VICTOIRE_PAR_DECONNEXION;
                        break;
                }

                break;
            } else
                ressourcesAdversaire = retour_serveur;
        } else if(getNbRessourcePortail(plateau) >= RESSOURCES_FIN_PARTIE) {
            tfp = VICTOIRE;
            break;
        }

        int continuer = 1;
        /* Boucle de tour, demande à l'utilisateur ce qu'il souhaite faire tant qu'il n'a pas demandé à passer au tour suivant */
        while(continuer && !quitter) {
            /* Avant de demander au joueur de faire un choix, la carte (à jour) lui est présentée */
            dessiner_carte(plateau);
            if(type_partie != SOLO)
                printf_ressource_restantes(RESSOURCES_FIN_PARTIE - getNbRessourcePortail(plateau),
                    ressourcesAdversaire);

            nouvelleMachine machine;
            switch(demander_action_suivante()) {
                /* Si le joueur demande à avoir machine en plus, une nouvelle est créée et est ajoutée */
                case AJOUT_MACHINE: ;
                    machine = demander_ajout_machine(plateau, liste_machines, taille_liste_machines);
                    if (machine.succes == 1) {
                        coord *coord = malloc(sizeof(coord));
                        coord->x = machine.x;
                        coord->y = machine.y;
                        listeLigneDeProduction *listeLDP = getListeLigneDeProduction(plateau);
                        cout *ressourceJoueur = getRessourceJoueur(plateau);
                        int retour_achat_machine = achatMachine(listeLDP, machine.machine, coord, machine.orientation, ressourceJoueur, plateau);
                        if (retour_achat_machine == 0) {
                            printf_succes("Machine ajoutée !");
                        } else if(retour_achat_machine == 1) {
                            printf_erreur("Impossible de construire une machine ici");
                        } else if(retour_achat_machine == 2) {
                            printf_erreur("Vous n'avez pas assez d'argent");
                        }
                    } else {
                        printf_abandon("Annulation de l'ajout de la machine...");
                    }
                    break;

                    /* Si le joueur demande à améliorer une machine, elle est améliorée */
                case AMELIORATION_MACHINE: ;
                    ligneDeProduction *selection_machine = demander_selection_machine(plateau, AMELIORATION_MACHINE);
                    if (selection_machine != NULL) {
                        int retour_amelioration_machine = amelioreMachine(selection_machine, plateau->ressourceJoueur);
                        if (retour_amelioration_machine == 0) {
                            printf_succes("Machine améliorée !");
                        } else if(retour_amelioration_machine == 1) {
                            printf_erreur("Pas de machine à améliorer ici");
                        } else if(retour_amelioration_machine == 2) {
                            printf_erreur("Vous n'avez pas assez d'argent");
                        }
                    } else {
                        printf_abandon("Annulation de l'amélioration de la machine...");
                    }
                    break;

                /* Si le joueur demande à détruire une machine, elle est supprimée */
                case SUPPRESSION_MACHINE: ;
                    ligneDeProduction *selection_machine2 = demander_selection_machine(plateau, SUPPRESSION_MACHINE);
                    if (selection_machine != NULL) {
                        int retour_destruction_machine = detruireMachine(getListeLigneDeProduction(plateau), selection_machine2, plateau->ressourceJoueur, &plateau->nbRessourcePortail);
                        if (retour_destruction_machine == 0) {
                            printf_succes("Machine détruite !");
                        } else if(retour_destruction_machine == 1) {
                            printf_erreur("Pas de machine à détruire ici");
                        } else if(retour_destruction_machine == 2) {
                            printf_erreur("Vous n'avez pas assez d'argent");
                        }
                    } else {
                        printf_abandon("Annulation de la destruction de la machine...");
                    }
                    break;

                /* Si le joueur demande à recruter du personnel, un nouveau personnel est recruté */
                case ACHAT_PERSONNEL: ;
                    personnel *perso = demander_achat_personnel(plateau, liste_personnel, taille_liste_personnel);
                    if (perso != NULL) {
                        if (recruterPersonnel(plateau, perso, liste_machines, taille_liste_machines, liste_personnel, taille_liste_personnel)) {
                            printf_succes("Personnel recruté !");
                        } else {
                            printf_erreur("Vous n'avez pas assez d'argent");
                        }
                    } else {
                        printf_abandon("Annulation achat personnel...");
                    }
                    
                    break;

                /* Si le joueur demande à recruter un FISE, un nouveau FISE est recruté */
                case RECRUTER_FISE: ;
                    if (confirmer_recruter_FISE(plateau)) {
                        if(recruterFISE(plateau, 1)) {
                            printf_succes("FISE recruté !");
                        } else {
                            printf_erreur("Vous n'avez pas assez d'argent");
                        }
                    } else {
                        printf_abandon("Annulation achat FISE...");
                    }
                    break;

                /* Si le joueur demande à recruter un FISA, un nouveau FISA est recruté */
                case RECRUTER_FISA: ;
                    if (confirmer_recruter_FISA(plateau)) {
                        if(recruterFISA(plateau, 1)) {
                            printf_succes("FISA recruté !");
                        } else {
                            printf_erreur("Vous n'avez pas assez d'argent");
                        }
                    } else {
                        printf_abandon("Annulation achat FISA...");
                    }
                    break;

                /* Si le joueur demande à modifier le type de ressource produit par les FIPA, celui-ci est changé */
                case CHANGER_TYPE_RESSOURCE_FISA: ;
                    changementTypeRessource(plateau);
                    printf_succes("Type de ressource produite changé !");
                    break;

                /* Si le joueur souhaite passer au tour suivant, la fin du tour actuel est marquée */
                case PASSER: ;
                    continuer = 0;
                    printf_succes("Fin du tour !");
                    break;
                case QUITTER: ;
                    quitter = 1;
            }
        }

        if(!quitter) {
            /* Fonction déclenchant le déroulement du tour */
            terminerTour(plateau);
        }
    }

    if(type_partie != SOLO) {
        printf_fin_partie(tfp, RESSOURCES_FIN_PARTIE - getNbRessourcePortail(plateau),
            ressourcesAdversaire);
        close_socket_client(client_socket);

        if(type_partie == CREER_PARTIE) {
            int status;

            wait(&status);
            if (status == -1)
                perror("Err wait()");
        }
    } else
        printf_fin_partie_solo(tfp, RESSOURCES_FIN_PARTIE - getNbRessourcePortail(plateau));

    /* Fonction libérant la mémoire utilisée par une partie à la fin de celle-ci */
    libererMemoireCarte(plateau);
    return EXIT_SUCCESS;
}
