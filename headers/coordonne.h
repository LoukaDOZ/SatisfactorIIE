#ifndef COORDONNEE_H
#define COORDONNEE_H

#include "machine.h"

typedef struct coord coord;

/**
 * Cette structure sert à représenter les différentes coordonnées
 *
 * @attr {x} - La valeur en abscisse
 * @attr {y} - La valeur en ordonné
 *
 */
struct coord {
  int x;
  int y;
};

/**
 * Renvois la valeur en X du @param {coord}
 *
 * @param {coord} - Coordonée à extraire
 * @return {int} - Coordonée en X
 */
int getCoordX(coord* coord);

/**
 * Modifie la valeur en X du @param {coord}
 *
 * @param {coord} - Coordonée à changer (en X)
 * @param {val} - Nouvelle valeur
 * 
 */
int setCoordX(coord* coord, int val);

/**
 * Renvois la valeur en Y du @param {coord}
 *
 * @param {coord} - Coordonée à extraire
 * @return {int} - Coordonée en Y
 */
int getCoordY(coord* coord);

/**
 * Modifie la valeur en Y du @param {coord}
 *
 * @param {coord} - Coordonée à changer (en Y)
 * @param {val} - Nouvelle valeur
 * 
 */
int setCoordY(coord* coord, int val);

/**
 * Permet de savoir si la coordoné et dans la carte
 *
 * @param {coord} - Coordonée à vérifier
 * @param {size} - Taille carte
 * @return {int} - 1 si dans la carte, 0 sinon
 * 
 */
int coordExist(coord* coord, int size);

/**
 * Cette fonction permet de mettre à jour les valeurs d'une coordonné
 * en fonction de la taille du plateau
 *
 *
 * @param {coord} - Coordonnée à modifier
 * @param {x} - La valeur en abscisse
 * @param {y} - La valeur en ordonné
 * @param {x} - Taille de la grille
 * @return {int} - 1 si les coordonnées appartienne à la grille et si les coordonnées ont été changé. 0 sinon
 *
 */
int setCoord(coord* coord, int x, int y, int sizeCard);

/**
 * Cette fonction permet de mettre à jour les valeur d'une coordonné
 * en fonction d'une autre
 *
 * @param {coord1} - Coordonnées à modifier
 * @param {coord2} - Coordonnées copiées
 *
 */
void setCoord2(coord* coord1, coord* coord2);

/**
 * Cette fonction permet de savoir si deux coordonnées sont égales
 *
 *
 * @param {coord1} - Coordonnée à comparée
 * @param {coord2} - Coordonnée à comparée
 * @return {int} - 1 si les coordonnées sont identique, 0 sinon
 *
 */
int diffCoord(coord* coord1, coord* coord2);

/**
 * Cette fonction permet de savoir si une coordonné est supérieur à une autre :
 * Note : (1;0) > (0;9) et (2;1) > (2;0)
 *
 * @param {coord1} - Coordonnée à comparée
 * @param {coord2} - Coordonnée à comparée
 * @return {int} - 1 si la coord1 est supérieur à coord2, 0 sinon
 *
 */
int compareCoord(coord* coord1, coord* coord2);

/**
 * Cette fonction permet de savoir si une coordonné est supérieur à une autre :
 * Note : (1;0) > (0;9) et (2;1) > (2;0)
 *
 * @param {coord1} - Coordonnée à comparée
 * @param {coord2} - Coordonnée à comparée
 * @return {int} - 1 si la coord1 est égale à coord2, 0 sinon
 *
 */
int compareCoord2(coord* coord1, coord* coord2);

/**
 * Cette fonction permet de savoir si une coordonné est supérieur à une autre :
 * Note : (1;0) > (0;9) et (2;1) > (2;0)
 *
 * @param {coord1} - Coordonnée à comparée
 * @param {coord2} - Coordonnée à comparée
 * @return {int} - 1 si la coord1 est supérieur à coord2, 0 sinon
 *
 */
int compareCoord3(coord* coord1, coord* coord2);


void setNewCoord(coord* caseArriver, pointCard* directionArriver);

#endif
