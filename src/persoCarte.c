#include "../headers/persoCarte.h"
#include <stdlib.h>

/********** Personel Suivant **********/


void setPersonnelSuivant(personnelCarte* perso,personnelCarte* perso2){
  perso->persoSuivant = perso2;
}

personnelCarte* getPersonnelSuivant(personnelCarte* perso){
  return perso->persoSuivant;
}

/********** Personel **********/

void setPersonnel(personnelCarte* perso, personnel* perso2){
  perso->perso = perso2;
}

personnel* getPersonnel(personnelCarte* perso){
  return perso->perso;
}

int addPersonnel(personnelCarte* newPersonnel, personnel* personnel, cout* argent){
  if(achatPersonnel(personnel, argent)){
    newPersonnel = (personnelCarte*) malloc(sizeof(personnelCarte));
    setPersonnel(newPersonnel,personnel);
    return 1;
  }
  else
    return 0;
}