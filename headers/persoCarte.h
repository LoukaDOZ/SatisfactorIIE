#ifndef PERSOCARTE_H
#define PERSOCARTE_H

#include "personnel.h"
#include "cout.h"
#include <stdlib.h>

typedef struct personnelCarte personnelCarte;

/**
 * Structure personnelCarte
 *
 * Cette structure sert pour la liste chainé des personnels achetés par le joueur
 *
 * @attr {personnel*} persoSuivant - Personnel suivant dans la liste
 * @attr {personnel*} perso - Personnel courant
 *
 */
struct personnelCarte{
  personnelCarte* persoSuivant;
  personnel* perso;
};

/********** Personel Suivant **********/

/**
 * Modifie le personnelCarte suivante du @param {perso1}
 *
 * @param {perso1} - personnelCarte à modifier
 * @param {perso2} - Nouvelle personnelCarte suivante
 * 
 */
void setPersonnelSuivant(personnelCarte* perso, personnelCarte* perso2);

/**
 * Renvois le personnelCarte suivante du @param {perso}
 *
 * @param {perso} - personnelCarte dont on veut la suivante
 * @return {personnelCarte*} - personnelCarte suivante
 */
personnelCarte* getPersonnelSuivant(personnelCarte* perso);

/********** Personel **********/

/**
 * Modifie le personnel du @param {perso1}
 *
 * @param {perso1} - personnelCarte à modifier
 * @param {perso2} - Nouveaux personnel
 * 
 */
void setPersonnel(personnelCarte* perso, personnel* perso2);

/**
 * Renvois le personnel du @param {perso}
 *
 * @param {perso} - personnelCarte dont on veut le personnel
 * @return {personnel*} - Personnel 
 */
personnel* getPersonnel(personnelCarte* perso);


/**
 * Cette fonction permet d'ajouter un personnel à un personnelCarte (création)
 *
 * Les ressources du joueurs sont directement déduite si il a assez de ressource.
 * Dans le cas contraire, rien ne se passe
 *
 *
 * @param {personnelCarte*} - personnelCarte ou on ajoute le personnel
 * @param {personnel*} - Personnel à ajouter
 * @param {cout*} - Ressources du joueur
 * @return {int} - 1 si le personnel à pu être ajouté, 0 sinon
 *
 */
int addPersonnel(personnelCarte* newPersonnel, personnel* personnel, cout* argent);

#endif