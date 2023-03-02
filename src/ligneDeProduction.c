#include "../headers/ligneDeProduction.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

/********** Machine suivante **********/

ligneDeProduction* getLDPSuivante(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->suivant;
}

void setLDPSuivante(ligneDeProduction* ldp, ligneDeProduction* suivant){
  ldp->suivant = suivant;
}

/********** Machines Voisines **********/

ligneDeProduction* getLDPNord(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->ldpNord;
}

void setLDPNord(ligneDeProduction* ligneDeProduction1, ligneDeProduction* ligneDeProduction2){
  ligneDeProduction1->ldpNord = ligneDeProduction2;
}

ligneDeProduction* getLDPEst(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->ldpEst;
}

void setLDPEst(ligneDeProduction* ligneDeProduction1, ligneDeProduction* ligneDeProduction2){
  ligneDeProduction1->ldpEst = ligneDeProduction2;
}

ligneDeProduction* getLDPSud(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->ldpSud;
}

void setLDPSud(ligneDeProduction* ligneDeProduction1, ligneDeProduction* ligneDeProduction2){
  ligneDeProduction1->ldpSud = ligneDeProduction2;
}

ligneDeProduction* getLDPOuest(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->ldpOuest;
}

void setLDPOuest(ligneDeProduction* ligneDeProduction1, ligneDeProduction* ligneDeProduction2){
  ligneDeProduction1->ldpOuest = ligneDeProduction2;
}

/********** Orientation **********/

pointCard getOrientation(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->orientation;
}

void setOrientation(ligneDeProduction* ligneDeProduction, pointCard orientation){
  ligneDeProduction->orientation = orientation;
}

/********** Coord **********/

coord* getCoordLDP(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->coordCarte;
}

void setCoordLDP(ligneDeProduction* ligneDeProduction, coord* c){
  ligneDeProduction->coordCarte = c;
}

/********** Niveau **********/

int getNiveauMachine(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->niveauMachine;
}

void setNiveauMachine(ligneDeProduction* ligneDeProduction, int niveau){
  ligneDeProduction->niveauMachine = niveau;
}

void incNiveauMachine(ligneDeProduction* ligneDeProduction){
  ligneDeProduction->niveauMachine++;
}

/********** Stock Max **********/

int getStockMax(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->stockMax;
}

void setStockMax(ligneDeProduction* ligneDeProduction, int stock){
  ligneDeProduction->stockMax = stock;
}

int updateStockMax(ligneDeProduction* ligneDeProduction, int val){
  ligneDeProduction->stockMax += val;
  return ligneDeProduction->stockMax;
}

/********** Stock courrant dechet **********/

int getStockCurDechet(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->stockCourrantDechet[0];
}

void setStockCurDechet(ligneDeProduction* ligneDeProduction, int stock){
  ligneDeProduction->stockCourrantDechet[0] = stock;
}

int getStockCurDechet2(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->stockCourrantDechet[1];
}

void setStockCurDechet2(ligneDeProduction* ligneDeProduction, int stock){
  ligneDeProduction->stockCourrantDechet[1] = stock;
}

/********** Stock courrant ressource **********/

int getStockCurRessource(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->stockCourrantRessource[0];
}

void setStockCurRessource(ligneDeProduction* ligneDeProduction, int stock){
  ligneDeProduction->stockCourrantRessource[0] = stock;
}

int getStockCurRessource2(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->stockCourrantRessource[1];
}

void setStockCurRessource2(ligneDeProduction* ligneDeProduction, int stock){
  ligneDeProduction->stockCourrantRessource[1] = stock;
}

/********** Ajoue stock courrant **********/

int addDechet(ligneDeProduction* ligneDeProduction, int val, int* nbDechetPortail){
  int diff = getStockMax(ligneDeProduction) - getStockCurDechet(ligneDeProduction) - getStockCurRessource(ligneDeProduction) - val;
  if( diff >= 0){
    ligneDeProduction->stockCourrantDechet[0] += val;
  }
  else{
    setStockCurDechet(ligneDeProduction, getStockMax(ligneDeProduction) - getStockCurRessource(ligneDeProduction));
    *nbDechetPortail += diff;
  }
  return ligneDeProduction->stockCourrantDechet[0];
}

int addRessource(ligneDeProduction* ligneDeProduction, int val){
  if(getStockMax(ligneDeProduction) >= getStockCurDechet(ligneDeProduction) + getStockCurRessource(ligneDeProduction) + val){
    ligneDeProduction->stockCourrantRessource[0] += val;
  }
  else{
    setStockCurRessource(ligneDeProduction, getStockMax(ligneDeProduction) - getStockCurDechet(ligneDeProduction));
  }
  return ligneDeProduction->stockCourrantRessource[0];
}

int addDechet2(ligneDeProduction* ligneDeProduction, int val){
  ligneDeProduction->stockCourrantDechet[1] += val;
  return ligneDeProduction->stockCourrantDechet[1];
}

int addRessource2(ligneDeProduction* ligneDeProduction, int val){
  ligneDeProduction->stockCourrantRessource[1] += val;
  return ligneDeProduction->stockCourrantRessource[1];
}

int getDechet(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->stockCourrantDechet[0]+ligneDeProduction->stockCourrantDechet[1];
}
/********** Machine **********/

void setMachine(ligneDeProduction* ligneDeProduction, machine* machine){
  ligneDeProduction->machine = machine;
}

machine* getMachine(ligneDeProduction* ligneDeProduction){
  return ligneDeProduction->machine;
}

/********** Création ligne de production **********/

int addMachine(ligneDeProduction** newMachine, coord* coord, machine* machine, pointCard orientation, cout* argent){
  cout prix = getCoutConstruction(machine);
  if(updateCout(argent, &prix)){
    *newMachine = (ligneDeProduction*) malloc(sizeof(ligneDeProduction));
    setMachine(*newMachine,machine);
    setOrientation(*newMachine,orientation);
    setCoordLDP(*newMachine,coord);
    setStockMax(*newMachine,getStockInit(machine));
    setStockCurDechet(*newMachine,0);
    setStockCurDechet2(*newMachine,0);
    setStockCurRessource(*newMachine,0);
    setStockCurRessource2(*newMachine,0);
    setNiveauMachine(*newMachine,1);
    return 1;
  }
  return 0;
}

/********** Amélioration ligne de production **********/

int upMachine(ligneDeProduction* ligneDeProduction, cout* argent){
  cout prix = getCoutAmelioration(getMachine(ligneDeProduction));
  if(updateCout(argent, &prix)){
    incNiveauMachine(ligneDeProduction);
    updateStockMax(ligneDeProduction, getStockUp(getMachine(ligneDeProduction)));
    return 1;
  }
  return 0;
}

/********** Destruction ligne de production **********/

int delMachine(ligneDeProduction* ligneDeProduction, cout* argent, int* nbDechetPortail){
  cout prix = getCoutDestruction(getMachine(ligneDeProduction));
  if(updateCout(argent, &prix)){
    *nbDechetPortail += getStockCurDechet(ligneDeProduction);
    return 1;
  }
  return 0;
}

/********** Entrées & Sorties **********/

void getEntreeDynamique(ligneDeProduction* ligneDeProduction, pointCard** entree, int* nb_entree){
  getEntreeMachine(getMachine(ligneDeProduction),entree,nb_entree);
  pointCard* ret = (pointCard*) malloc(*nb_entree*sizeof(pointCard));
  for(int i=0; i < *nb_entree; i++){
    ret[i] = (((*entree)[i] + getOrientation(ligneDeProduction))%4);
  }
  *entree = ret;
}

void getSortieDynamique(ligneDeProduction* ligneDeProduction, pointCard** sortie, int* nb_sortie){
  getSortieMachine(getMachine(ligneDeProduction),sortie,nb_sortie);
  pointCard* ret = (pointCard*) malloc(*nb_sortie*sizeof(pointCard));
  for(int i=0; i < *nb_sortie; i++){
    ret[i] = (((*sortie)[i] + getOrientation(ligneDeProduction))%4);
  }
  *sortie = ret;
}


//TODO : A modifier pour éviter boucle infini
int getFinCheminAux(ligneDeProduction* ligneDeProduction, coord* caseArriver, pointCard* directionArriver){

  if(ligneDeProduction == NULL){  //Pas de machine
    setNewCoord(caseArriver,directionArriver);
    return 0;
  }

  //caseArriver = getCoordLDP(ligneDeProduction);
  setCoord2(caseArriver,getCoordLDP(ligneDeProduction));
  int nb_entree;
  pointCard* entree;
  getEntreeDynamique(ligneDeProduction, &entree, &nb_entree);

  //Si la machine n'est ni un tapis ni une croix
  if(getTypeMachine(getMachine(ligneDeProduction)) != TAPIS && getTypeMachine(getMachine(ligneDeProduction)) != CROIX){   
    for(int i=0; i < nb_entree; i++){
      if((*directionArriver+2)%4 == entree[i]){ //Si il y a une entrée au niveau de la sortie
        free(entree);
        return 1;
      }
    }
    //Si il n'y a pas d'entrée au niveau de la sortie
    free(entree);
    return 2;
  }
  //La machine est un tapis ou une croix
  for(int i=0; i < nb_entree; i++){
    if( (*directionArriver+2)%4 == entree[i] ){ //Si il y a une entrée au niveau de la sortie
      free(entree);
      if(getTypeMachine(getMachine(ligneDeProduction)) == CROIX){ //Si la machine est une croix
        if(*directionArriver == NORD){
          return getFinCheminAux(getLDPNord(ligneDeProduction), caseArriver, directionArriver);;
        }
        if(*directionArriver == EST){
          return getFinCheminAux(getLDPEst(ligneDeProduction), caseArriver, directionArriver);
        }
        if(*directionArriver == SUD){
          return getFinCheminAux(getLDPSud(ligneDeProduction), caseArriver, directionArriver);
        }
        return getFinCheminAux(getLDPOuest(ligneDeProduction), caseArriver, directionArriver);
      }
      else{ //La machine est un tapis
        int nb_sortie;
        pointCard* sortie;
        getSortieDynamique(ligneDeProduction, &sortie, &nb_sortie);
        *directionArriver = sortie[0];
        free(sortie);
        if(*directionArriver == NORD){
          return getFinCheminAux(getLDPNord(ligneDeProduction), caseArriver, directionArriver);
        }
        if(*directionArriver == EST){
          return getFinCheminAux(getLDPEst(ligneDeProduction), caseArriver, directionArriver);
        }
        if(*directionArriver == SUD){
          return getFinCheminAux(getLDPSud(ligneDeProduction), caseArriver, directionArriver);
        }
        return getFinCheminAux(getLDPOuest(ligneDeProduction), caseArriver, directionArriver);
      }
    }
  }
  // Si aucune entrée ne corespond à la sortie précédante
  free(entree);
  return 2;
}

// Le but est de renvoyer la première position de la première machine 
//qui n'est n'y une croix n'y un tapis avec la direction
int getFinChemin(ligneDeProduction* ligneDeProduction, coord** caseArriver, pointCard* directionArriver){
  coord* c = (coord*) malloc(sizeof(coord));
  setCoord2(c,getCoordLDP(ligneDeProduction));
  int nb_sortie;
  pointCard* sortie;
  getSortieDynamique(ligneDeProduction, &sortie, &nb_sortie);
  *directionArriver = sortie[0];
  free(sortie);
  setNewCoord(c, directionArriver);
#include <stdio.h>
  printf("0\n");
  *caseArriver = c;
  if(*directionArriver == NORD) {
      printf("A\n");
      if(getLDPNord(ligneDeProduction) == NULL){
        return 0;
      }
      ligneDeProduction = getLDPNord(ligneDeProduction);
  } else if(*directionArriver == EST) {
      printf("B\n");
      if(getLDPEst(ligneDeProduction) == NULL){
        return 0;
      }
      ligneDeProduction = getLDPEst(ligneDeProduction);
  } else if(*directionArriver == SUD) {
      printf("C\n");
      if(getLDPSud(ligneDeProduction) == NULL){
        return 0;
      }
      ligneDeProduction = getLDPSud(ligneDeProduction);
  } else {
      printf("D\n");
      if(getLDPOuest(ligneDeProduction) == NULL){
        return 0;
      }
      ligneDeProduction = getLDPOuest(ligneDeProduction);
  }
  printf("E\n");
  int nb_sortie1;
  pointCard* sortie1;
  getSortieDynamique(ligneDeProduction, &sortie1, &nb_sortie1);
  *directionArriver = sortie1[0];
  free(sortie1);
  int ret = getFinCheminAux(ligneDeProduction, c, directionArriver);
  *caseArriver = c;
  return ret;
}
