#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "ligneDeProduction.h"
#include "coordonne.h"
#include "persoCarte.h"

/* MACHINE */

typedef struct listeLigneDeProduction listeLigneDeProduction;

/**
 * Structure listeLigneDeProduction
 * 
 * Modélise une liste chainé avec son première élément ainsi que son nombre d'élément
 *
 * @attr {int} nbLigneDeProd - Nombre d'élément de la liste
 * @attr {ligneDeProduction*} startList - Première élément de la liste
 *
 */
struct listeLigneDeProduction {
  int nbLigneDeProd;
  ligneDeProduction* startList;
};

/**
 * Renvois le nombre de LDP du @param {liste}
 *
 * @param {liste} - Liste dont on veut la taille
 * @return {int} - Taille de la liste
 */
int getNbLDP(listeLigneDeProduction* liste);

/**
 * Renvois le première élément du @param {liste}
 *
 * @param {liste} - Liste dont on veut le première élément
 * @return {ligneDeProduction*} - Première élément
 */
ligneDeProduction* getStartListLDP(listeLigneDeProduction* liste);

/**
 * Cette renvois une structure initialisé avec un nombre de LDP à 0 et aucun première élément
 *
 * @return {listeLigneDeProduction*} - Structure initialisé
 *
 */
listeLigneDeProduction* initialisationListeLDP();

/**
 * Cette fonction ajoute un élément @param {ligneDeProd} à la structure @param {liste}
 * et met à jour automatiquement les différents attributs de la structure
 *
 * @param {liste} - Structure à laquelle on ajoute un élément
 * @param {ligneDeProd} - Element qu'on ajoute
 * @param {sizeCarte} - Taille de la carte
 *
 */
void insertionListLDP(listeLigneDeProduction *liste, ligneDeProduction* ligneDeProd, int sizeCarte);

/**
 * Cette fonction supprime l'élément @param {ligneDeProd} de la structure @param {liste}
 * et met à jour automatiquement les différents attributs de la liste
 *
 * @param {liste} - Structure à laquelle on veut supprimer un élément
 * @param {ligneDeProd} - Element qu'on supprime
 *
 */
void suppressionListLDP(listeLigneDeProduction *liste, ligneDeProduction* ligneDeProd);

/**
 * Cette fonction renvois l'élément placé au coordonné @param {coord} de la structure @param {liste}
 * si il existe
 *
 * @param {liste} - Liste dans laquelle on veut récupérer un élément
 * @param {coord} - Coordonnée de l'élément à récuperer
 * @param {sizeCarte} - Taille de la carte
 * @return {ligneDeProduction*} - LDP corespondante où NULL si aucune trouvé
 *
 */
ligneDeProduction* findByCoordListLDP(listeLigneDeProduction *liste, coord* coord, int sizeCarte);

/* PERSONNEL */

typedef struct listePersonnel listePersonnel;

/**
 * Structure listePersonnel
 * 
 * Modélise une liste chainé avec son première élément ainsi que son nombre d'élément
 *
 * @attr {int} nbPersonnel - Nombre d'élément de la liste
 * @attr {persoCarte*} startList - Première élément de la liste
 *
 */
struct listePersonnel {
  int nbPersonnel;
  personnelCarte* startList;
};

/**
 * Renvois le nombre de personnel du @param {liste}
 *
 * @param {liste} - Liste dont on veut la taille
 * @return {int} - Taille de la liste
 */
int getNbPersonnelList(listePersonnel* liste);


/**
 * Renvois le première élément du @param {liste}
 *
 * @param {liste} - Liste dont on veut le première élément
 * @return {persoCarte*} - Première élément
 */
personnelCarte* getStartListPersonnel(listePersonnel* liste);

/**
 * Cette fonction renvois une structure initialisé avec un nombre de personnel à 0 et aucun première élément
 *
 * @return {listePersonnel*} - Structure initialisé
 *
 */
listePersonnel* initialisationListePerso();

/**
 * Cette fonction ajoute un élément @param {perso} à la structure @param {liste}
 *
 * @param {liste} - Structure à laquelle on ajoute un élément
 * @param {perso} - Element qu'on ajoute
 *
 */
void insertionListPerso(listePersonnel *liste, personnelCarte* perso);

/**
 * Renvois le nombre de personnel dans @param {liste} qui ont pour id @param {id}
 *
 * @param {liste} - Liste sur laquelle on effectue la recherche
 * @param {id} - Id qu'on recherche
 * @return {int} - Nombre d'élément
 *
 */
int CountById(listePersonnel* liste, int id);

#endif
