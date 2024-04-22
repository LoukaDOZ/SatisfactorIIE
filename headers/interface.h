#ifndef INTERFACE_H
#define INTERFACE_H

#include "machine.h"
#include "carte.h"
#include "ligneDeProduction.h"
#include "personnel.h"

/*
* Action du joueur
* @see demander_action_suivante()
*/
typedef enum actionJoueur {
    AJOUT_MACHINE,
    AMELIORATION_MACHINE,
    SUPPRESSION_MACHINE,
    ACHAT_PERSONNEL,
    RECRUTER_FISE,
    RECRUTER_FISA,
    CHANGER_TYPE_RESSOURCE_FISA,
    PASSER,
    QUITTER
} actionJoueur;

/*
* Choix de type de partie
*/
typedef enum typePartie {
  SOLO,
  CREER_PARTIE,
  REJOINDRE_PARTIE
} typePartie;

/*
* Différentes fins de partie
*/
typedef enum typeFinPartie {
  VICTOIRE,
  VICTOIRE_PAR_DECONNEXION,
  DEFAITE
} typeFinPartie;

/*
* Type retourné lors de l'ajout d'une machine
* Contient les informations transmises par le joueur
* @attr x : Position x la machine
* @attr y : Position y la machine
* @attr machine : Machine
* @attr orientation : Orientation
*/
typedef struct nouvelleMachine {
    int succes; /* 1 si la demande a été complétée, 0 sinon */
    int x; /* Position x la machine */
    int y; /* Position y la machine */
    machine* machine; /* Machine */
    enum pointCard orientation; /* Orientation */
} nouvelleMachine;

/*
* Affiche le succès d'une opération à l'utilisateur
* @param message : message décrivant le succès
*/
void printf_succes(char* message);

/*
* Affiche l'abandon d'une opération à l'utilisateur
* @param message : message décrivant l'abandon
*/
void printf_abandon(char* message);

/*
* Affiche une erreur à l'utilisateur
* @param message : message décrivant l'erreur
*/
void printf_erreur(char* message);

/*
* Dessine la carte
* @param plateau : pointeur sur la carte et les informations du joueur
*/
void dessiner_carte(carte* plateau);

/*
* Demande la carte à l'utilisateur
* @return Retourne la taille de la carte : 
*   10 : FACILE
*   20 : MOYENNE
*   30 : GRANDE
*/
int demander_taille_carte();

/*
* Demande à l'utilisateur de choisir une action à faire
* @return Retourne structure actionJoueur de l'action choisie
*/
actionJoueur demander_action_suivante();

/*
* Demande à l'utilisateur de placer une nouvelle machine
* @param plateau : pointeur sur la carte et les informations du joueur
* @param machines : liste des machines disponibles
* @param taille_liste_machines : nombre d'éléments de l'argument 'machines'
* @return Retourne un type nouvelle_machine avec les informations obtenues
*/
nouvelleMachine demander_ajout_machine(carte* plateau, machine** machines, int taille_liste_machines);

/*
* Demande à l'utilisateur de selectionner une machine pour l'améliorer ou la détruire
* @param plateau : pointeur sur la carte et les informations du joueur
* @param action : améliorer ou supprimer machine
* @see Voir structure actionJoueur
* @return Retourne la ligneDeProduction de la machine choisie par le joueur
*/
ligneDeProduction* demander_selection_machine(carte* plateau, actionJoueur action);

/*
* Demande à l'utilisateur de choisir un nouveau membre du personnel à acheter
* @param plateau : pointeur sur la carte et les informations du joueur
* @param personnels : liste de tous les personnels disponibles dans le jeu
* @param taille_liste_personnels : nombre d'éléments de l'argument 'machines'
* @return Retourne le personnel choisi par le joueur
*/
personnel* demander_achat_personnel(carte* plateau, personnel** personnels, int taille_liste_personnels);

/*
* Demander à l'utilisateur de confirmer son achat d'un FISE
* @param : plateau : plateau
* @return : 0 pour false, 1 pour true
*/
int confirmer_recruter_FISE(carte* plateau);

/*
* Demander à l'utilisateur de confirmer son achat d'un FISA
* @param : plateau : plateau
* @return : 0 pour false, 1 pour true
*/
int confirmer_recruter_FISA(carte* plateau);

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
typePartie demander_type_partie(char* adresse, int* port);

/*
* Affiche, à l'utilisateur, un message de fin de partie
* @param victoire : type victoire
* @param scoreJoueur : ressources restantes du joueur
* @param scoreAdverse : ressources restantes de l'adversaire
*/
void printf_fin_partie(typeFinPartie type_fin, int joueur, int adversaire);

/*
* Affiche, à l'utilisateur, un message de fin de partie, pour une partie solo
* @param victoire : type victoire
* @param scoreJoueur : ressources restantes du joueur
*/
void printf_fin_partie_solo(typeFinPartie type_fin, int joueur);

/*
* Affiche, à l'utilisateur, ses ressources restantes pour gagner et celles de l'adversaire
* @param joueur : ressources restantes du joueur
* @param adversaire : ressources restantes de l'adversaire
*/
void printf_ressource_restantes(int joueur, int adversaire);

#endif
