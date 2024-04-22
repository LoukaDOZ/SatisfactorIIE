#ifndef LIGNEDEPRODUCTION_H
#define LIGNEDEPRODUCTION_H

#include "machine.h"
#include "cout.h"
#include "coordonne.h"

typedef struct ligneDeProduction ligneDeProduction;


/**
 * Cette structure représente la ligne de production
 *
 * @attr {pointCard} orientation - l'orientation de la machine
 * @attr {machine} machine - la machine en question
 * @attr {coord} coordCarte - coordonnée sur la carte
 * @attr {int} stockMax - le stock maximal de la machine
 * @attr {int} stockCourrantDechet - Le stock courant de dechet
 * @attr {int} stockCourrantRessource - Le stock courant de ressource
 * @attr {int} niveauMachine - Le niveau de la machine
 *
 */
struct ligneDeProduction
{
  ligneDeProduction* suivant;

  ligneDeProduction* ldpNord;
  ligneDeProduction* ldpEst;
  ligneDeProduction* ldpSud;
  ligneDeProduction* ldpOuest;

  pointCard orientation;
  machine* machine;
  coord* coordCarte;
  int stockMax;
  int stockCourrantDechet;
  int stockCourrantRessource;
  int niveauMachine;
};

/********** Machine suivante **********/

/**
 * Renvois la LDP suivante du @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - LDP dont on veut la suivante
 * @return {ligneDeProduction*} - LDP suivante
 */
ligneDeProduction* getLDPSuivante(ligneDeProduction* ligneDeProduction);

/**
 * Modifie la LDP suivante du @param {ldp}
 *
 * @param {ldp} - LDP à modifier
 * @param {suivant} - Nouvelle LDP suivante
 * 
 */
void setLDPSuivante(ligneDeProduction* ldp, ligneDeProduction* suivant);

/********** Machines Voisines **********/

/**
 * Renvois la LDP au Nord du @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - LDP dont on veut le voisin au Nord
 * @return {ligneDeProduction*} - LDP au Nord
 */
ligneDeProduction* getLDPNord(ligneDeProduction* ligneDeProduction);

/**
 * Modifie la LDP voisin Nord du @param {ligneDeProduction1}
 *
 * @param {ligneDeProduction1} - LDP à modifier
 * @param {ligneDeProduction2} - Nouvelle LDP Nord
 * 
 */
void setLDPNord(ligneDeProduction* ligneDeProduction1, ligneDeProduction* ligneDeProduction2);

/**
 * Renvois la LDP au Est du @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - LDP dont on veut le voisin au Est
 * @return {ligneDeProduction*} - LDP au Est
 */
ligneDeProduction* getLDPEst(ligneDeProduction* ligneDeProduction);

/**
 * Modifie la LDP voisin Est du @param {ligneDeProduction1}
 *
 * @param {ligneDeProduction1} - LDP à modifier
 * @param {ligneDeProduction2} - Nouvelle LDP Est
 * 
 */
void setLDPEst(ligneDeProduction* ligneDeProduction1, ligneDeProduction* ligneDeProduction2);

/**
 * Renvois la LDP au Sud du @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - LDP dont on veut le voisin au Sud
 * @return {ligneDeProduction*} - LDP au Sud
 */
ligneDeProduction* getLDPSud(ligneDeProduction* ligneDeProduction);

/**
 * Modifie la LDP voisin Sud du @param {ligneDeProduction1}
 *
 * @param {ligneDeProduction1} - LDP à modifier
 * @param {ligneDeProduction2} - Nouvelle LDP Sud
 * 
 */
void setLDPSud(ligneDeProduction* ligneDeProduction1, ligneDeProduction* ligneDeProduction2);

/**
 * Renvois la LDP au Ouest du @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - LDP dont on veut le voisin au Ouest
 * @return {ligneDeProduction*} - LDP au Ouest
 */
ligneDeProduction* getLDPOuest(ligneDeProduction* ligneDeProduction);

/**
 * Modifie la LDP voisin Ouest du @param {ligneDeProduction1}
 *
 * @param {ligneDeProduction1} - LDP à modifier
 * @param {ligneDeProduction2} - Nouvelle LDP Ouest
 * 
 */
void setLDPOuest(ligneDeProduction* ligneDeProduction1, ligneDeProduction* ligneDeProduction2);

/********** Orientation **********/

/**
 * Renvois l'orientation de la machine de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - ligneDeProduction dont on veut connaitre l'orientation de la machine
 * @return {pointCard} - orientation de la machine
 *
 */
pointCard getOrientation(ligneDeProduction* ligneDeProduction);

/**
 * Permet de mettre à jour l'orientation de la machine de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - Ligne de production dont on veut changer l'orientation de la machine
 * @param {orientation} - Nouvelle orientation
 *
 */
void setOrientation(ligneDeProduction* ligneDeProduction, pointCard orientation);

/********** Coord **********/

/**
 * Renvois les coordonnées de la machine de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - ligneDeProduction dont on veut connaitre les coordonnées de la machine
 * @return {coord*} - Coordonnées de la machine
 *
 */
coord* getCoordLDP(ligneDeProduction* ligneDeProduction);

/**
 * Permet de mettre à jour les coordonnées de la machine de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - Ligne de production dont on veut changer les coordonnées de la machine
 * @param {orientation} - Nouvelles coordonnées
 *
 */
void setCoordLDP(ligneDeProduction* ligneDeProduction, coord* c);

/********** Niveau **********/

/**
 * Renvois le niveau de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - ligneDeProduction dont on veut connaitre le niveau
 * @return {int} - niveau
 *
 */
int getNiveauMachine(ligneDeProduction* ligneDeProduction);

/**
 * Permet de mettre à jour le niveau de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 * @param {niveau} - Nouveaux niveau
 *
 */
void setNiveauMachine(ligneDeProduction* ligneDeProduction, int niveau);

/**
 * Permet de mettre à jour le niveau de la ligne de production @param {ligneDeProduction} en l'incrémantant de 1
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 *
 */
void incNiveauMachine(ligneDeProduction* ligneDeProduction);

/********** Stock Max **********/

/**
 * Renvois le nombre maximal de stock de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - ligneDeProduction dont on veut connaitre le stock maximal
 * @return {int} - taille de stockage
 *
 */
int getStockMax(ligneDeProduction* ligneDeProduction);

/**
 * Permet de mettre à jour le stock max de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 * @param {stock} - Nouveaux stock
 *
 */
void setStockMax(ligneDeProduction* ligneDeProduction, int stock);

/**
 * Permet de mettre à jour le stock max de la ligne de production @param {ligneDeProduction} en y ajoutant @param {val}
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 * @param {val} - Stock ajouter
 * @return {int} - Nouveaux stock max
 *
 */
int updateStockMax(ligneDeProduction* ligneDeProduction, int val);

/********** Stock courrant dechet **********/

/**
 * Renvois le nombre de dechet acteulle sur la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - ligneDeProduction dont on veut connaitre le nombre de dechet
 * @return {int} - Nombre de dechet
 *
 */
int getStockCurDechet(ligneDeProduction* ligneDeProduction);

/**
 * Permet de mettre à jour le stock courant de dechet de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 * @param {stock} - Nouveaux stock
 *
 */
void setStockCurDechet(ligneDeProduction* ligneDeProduction, int stock);

/********** Stock courrant dechet **********/

/**
 * Renvois le nombre de ressource acteulle sur la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - ligneDeProduction dont on veut connaitre le nombre de ressource
 * @return {int} - Nombre de dechet
 *
 */
int getStockCurRessource(ligneDeProduction* ligneDeProduction);

/**
 * Permet de mettre à jour le stock courant de ressource de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 * @param {stock} - Nouveaux stock
 *
 */
void setStockCurRessource(ligneDeProduction* ligneDeProduction, int stock);

/********** Ajoue stock courrant **********/

/**
 * Permet de mettre à jour le stock courant de dechet de la ligne de production @param {ligneDeProduction}
 *
 * Si le nombre de dechet est supérieur au stockage maximal de la machine, tout surplus part dans le portail
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 * @param {val} - nombre de déchet à ajouter
 * @param {nbDechetPortail} - Pointeur vers le nombre de dechet du portail
 * @return {int} - Le stock courant de dechet
 *
 */
int addDechet(ligneDeProduction* ligneDeProduction, int val, int* nbDechetPortail);

/**
 * Permet de mettre à jour le stock courant de ressource de la ligne de production @param {ligneDeProduction}
 *
 * Si le nombre de ressource est supérieur au stockage maximal de la machine, tout surplus est perdu
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 * @param {val} - nombre de ressource à ajouter
 * @return {int} - Le stock courant de ressource
 *
 */
int addRessource(ligneDeProduction* ligneDeProduction, int val);

/********** Machine **********/

/**
 * Permet de mettre à jour la machine de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - Ligne de production sur laquelle on va effectuer la MAJ
 * @param {machine} - Nouvelle machine
 *
 */
void setMachine(ligneDeProduction* ligneDeProduction, machine* machine);

/**
 * Renvois la machine de la ligne de production @param {ligneDeProduction}
 *
 * @param {ligneDeProduction} - ligneDeProduction dont on veut connaitre la machine
 * @return {machine*} - Pointeur vers la machine
 */
machine* getMachine(ligneDeProduction* ligneDeProduction);

/********** Création ligne de production **********/

/**
 * Cette fonction permet d'ajouter une machine à la ligne de production
 * dans l'orientation si le joueur à les ressources nécessaires
 *
 * Les ressources du joueurs sont directement déduite si il a assez de ressource.
 * Dans le cas contraire, rien ne se passe
 *
 *
 * @param {ligneDeProduction} - Ligne de production ou on ajoute la machine
 * @param {machine} - Machine à ajouter
 * @param {orientation} - Orientation de la machine
 * @param {argent} - Ressources du joueur
 * @return {int} - 1 si la machine à pu être ajouté, 0 sinon
 *
 */
int addMachine(ligneDeProduction** newMachine,  coord* coord, machine* machine, pointCard orientation, cout* argent);

/********** Amélioration ligne de production **********/

/**
 * Cette fonction permet d'améliorer une machine de la ligne de production
 *
 * Les ressources du joueurs sont directement déduite si il a assez de ressource.
 * Dans le cas contraire, rien ne se passe
 *
 *
 * @param {ligneDeProduction} - Ligne de production ou on ameliore la machine
 * @param {argent} - Ressources du joueur
 * @return {int} - 1 si la machine à pu être améliorer, 0 sinon
 *
 */
int upMachine(ligneDeProduction* ligneDeProduction, cout* argent);

/********** Destruction ligne de production **********/

/**
 * Cette fonction permet de detruire une machine de la ligne de production
 *
 * Les ressources du joueurs sont directement déduite si il a assez de ressource.
 * Dans le cas contraire, rien ne se passe. Si la suppression a lieu, les dechets
 * présents sur la case sont renvoyés au portail.
 *
 *
 * @param {ligneDeProduction} - Ligne de production ou on souhaite détruire la machine
 * @param {argent} - Ressources du joueur
 * @param {nbDechetPortail} - Nombre de dechet du portail
 * @return {int} - 1 si la machine à pu être détruite, 0 sinon
 *
 */
int delMachine(ligneDeProduction* ligneDeProduction, cout* argent, int* nbDechetPortail);

/********** Entrées & Sorties **********/

/**
 * Permet de récupérer le nombre d'entrée ainsi que les entrées de la machine de la ligne de production @param {ligneDeProduction}
 *
 * On prend en compte l'orientation
 *
 * @param {ligneDeProduction} - Ligne de production pour laquelle on veut connaitre ces informations
 * @param {entree} - Entrees
 * @param {entree} - Nombre d'entree
 *
 */
void getEntreeDynamique(ligneDeProduction* ligneDeProduction, pointCard** entree, int* nb_entree);

/**
 * Permet de récupérer le nombre de sortie ainsi que les entrées de la machine de la ligne de production @param {ligneDeProduction}
 *
 * On prend en compte l'orientation
 *
 * @param {ligneDeProduction} - Ligne de production pour laquelle on veut connaitre ces informations
 * @param {entree} - Sorties
 * @param {entree} - Nombre de sortie
 *
 */
void getSortieDynamique(ligneDeProduction* ligneDeProduction, pointCard** sortie, int* nb_sortie);

/**
 * Permet de récupérer les coordonées de la sortie (à la fin des tapis) de la machine @param {ligneDeProduction}
 * 
 * @param {ligneDeProduction} - Ligne de production pour laquelle on veut connaitre ces informations
 * @param {caseArriver} - Coordonnées de la case d'arrivé
 * @param {directionArriver} - Direction de la source (sortie de la machine précédante)
 * @return {int} - 0 si pas de machine sur la case d'arrivée, 1 si il y a une machine sur la case d'arriver avec une entré au bon endroit , 2 si il y a une machine sur la case d'arriver avec aucune entrée à cette endroit
 * 
 */
int getFinChemin(ligneDeProduction* ligneDeProduction, coord** caseArriver, pointCard* directionArriver);


#endif
