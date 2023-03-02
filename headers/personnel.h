#ifndef PERSONNEL_H
#define PERSONNEL_H

#include "variablesGlobales.h"
#include "cout.h"
#include "stdlib.h"

typedef struct personnel personnel;

/**
 * Structure personnel
 *
 * @attr {int} num - Un entier qui permettra notamment d'identifier le personnel et d'appliquer son effet.
 * @attr {char*} nom - Nom du personnel
 * @attr {char*} description - Description de l'effet du personnel
 * @attr {cout*} action - Représente les valeurs pour une action (Par exemple pour Fetia Bannour 10E et 1DD)
 * @attr {cout*} min_action - Représente les valeurs minimum pour l'action du personnel (Par exemple pour Fetia Bannour 10E et 1DD)
 * @attr {cout*} cout_engagement - Représente les couts (en DD et E) d'achat
 *
 */
struct personnel{
  int num;
  char* nom;
  char* description;
  cout* action;
  cout* min_action;
  cout* cout_engagement;
};

/********** Num **********/

/**
 * Modifie le numéro du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le numéro
 * @param {num} - Nouveau numéro
 * 
 */
void setNumPersonnel(personnel* perso, int num);

/**
 * Renvois le numéro de @param {perso}
 *
 * @param {perso} - Personnel dont on veut connaitre le numéro
 * @return {int} - Numéro
 */
int getNumPersonnel(personnel* perso);

/********** Nom **********/

/**
 * Modifie le nom du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le nom
 * @param {nom} - Nouveau nom
 * 
 */
void setNomPersonnel(personnel* perso, char* nom);

/**
 * Renvois le nom de @param {perso}
 *
 * @param {perso} - Personnel dont on veut connaitre le nom
 * @return {char*} - Nom
 */
char* getNomPersonnel(personnel* perso);

/********** Description **********/

/**
 * Modifie la description du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier la description
 * @param {num} - Nouvelle description
 * 
 */
void setDescPersonnel(personnel* perso, char* desc);

/**
 * Renvois la description de @param {perso}
 *
 * @param {perso} - Personnel dont on veut connaitre la description
 * @return {char*} - Description
 */
char* getDescPersonnel(personnel* perso);

/********** Cout **********/

/**
 * Renvois la valeur des action de @param {perso}
 *
 * @param {perso} - Personnel dont on veut connaitre la valeur des actions
 * @return {cout*} - Valeurs
 */
cout* getCoutAction(personnel* perso);

/**
 * Modifie le cout d'action en DD du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le coût d'action
 * @param {val} - Nouveau coût en DD
 * 
 */
void setCoutActionDD(personnel* perso, int val);

/**
 * Modifie le cout d'action en E du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le coût d'action
 * @param {val} - Nouveau coût en E
 * 
 */
void setCoutActionE(personnel* perso, int val);

/**
 * Renvois la valeur minimal des actions de @param {perso}
 *
 * @param {perso} - Personnel dont on veut connaitre la valeur minimal des actions
 * @return {cout*} - Valeurs
 */
cout* getCoutActionMin(personnel* perso);

/**
 * Modifie le cout d'action minimal en DD du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le coût d'action minimal
 * @param {val} - Nouveau coût en DD
 * 
 */
void setCoutActionMinDD(personnel* perso, int val);

/**
 * Modifie le cout d'action minimal en E du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le coût d'action minimal
 * @param {val} - Nouveau coût en E
 * 
 */
void setCoutActionMinE(personnel* perso, int val);

/**
 * Renvois le coût d'achat de @param {perso}
 *
 * @param {perso} - Personnel dont on veut connaitre le coût d'achat
 * @return {cout*} - Coût d'achat
 */
cout* getCoutAchat(personnel* perso);

/**
 * Modifie le cout d'achat en DD du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le coût d'achat
 * @param {val} - Nouveau coût en DD
 * 
 */
void setCoutAchatDD(personnel* perso, int val);

/**
 * Modifie le cout d'achat en E du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le coût d'achat
 * @param {val} - Nouveau coût en E
 * 
 */
void setCoutAchatE(personnel* perso, int val);

/**
 * Modifie le cout d'achat du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le coût d'achat
 * @param {val} - Nouveau coût d'achat
 * 
 */
void setCoutAchat(personnel* perso, cout* cout);

/**
 * Modifie le cout d'achat du @param {perso}
 *
 * @param {perso} - Personnel dont on veut modifier le coût d'achat
 * @param {coutDD} - Nouveau coût d'achat en DD
 * @param {coutE} - Nouveau coût d'achat en E
 * 
 */
void setCoutAchat2(personnel* perso, int coutDD, int coutE);

/**
 * Modifie le cout d'achat du @param {perso} en fonction des paramêtres (avec un minimum)
 *
 * @param {perso} - Personnel dont on veut actualiser le coût d'achat
 * @param {redDD} - Baisse coût d'achat en DD
 * @param {redE} - Baisse coût d'achat en E
 * @param {minDD} - Minimum coût d'achat en DD
 * @param {minE} - Minimum coût d'achat en E
 * 
 */
void updateCoutAchat(personnel* perso, int redDD, int redE, int minDD, int minE);

/********** Achat Personnel **********/

/**
 * Permet de mettre à jour l'argent du joueur après l'achat du personnel @param {perso}
 *
 * @param {perso} - Personnel acheté
 * @param {argent} - Argent du joueur
 * @return {int} - 1 la mise à jour à pu être effectué, 0 sinon (pas assez de ressources)
 */
int achatPersonnel(personnel* perso, cout* argent);

/********** Fonction main **********/

/**
 * Cette fonction permet d'ajouter à une liste passé en paramêtre, l'ensemble des personnel disponible dans le jeux.
 * Le second argument récupère la taille de cette liste
 *
 * @param {liste_personnel} - Une liste de personnel (initialement vide)
 * @param {taille_liste_personnel} - taille de la liste @param {liste_personnel}
 *
 */
void init_personnel(personnel*** liste_personnel, int* taille_liste_personnel);

#endif
