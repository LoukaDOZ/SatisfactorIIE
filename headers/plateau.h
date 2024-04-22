#include "carte.h"
#ifndef PLATEAU_H
#define PLATEAU_H
typedef struct plateau plateau;

/**
 * Cette structure représente le plateau du jeu 
 * qui contient la carte du jeu
 * 
 * @attr {carte} carte
 */
struct plateau
{
    carte carte;
};
#endif