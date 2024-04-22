#include "../headers/structure.h"

#include <stdlib.h>
#include <stdio.h>
int getNbLDP(listeLigneDeProduction* liste){
  return liste->nbLigneDeProd;
}

ligneDeProduction* getStartListLDP(listeLigneDeProduction* liste){
  return liste->startList;
}

listeLigneDeProduction* initialisationListeLDP(){
  listeLigneDeProduction* liste = (listeLigneDeProduction*) malloc(sizeof(listeLigneDeProduction));
  liste->nbLigneDeProd = 0;
  liste->startList = NULL;
  return liste;
}



//A Optimiser
ligneDeProduction* findByCoordListLDP_aux(ligneDeProduction *ligneDeProd, coord* coord, int sizeCarte){
  if(! coordExist(coord, sizeCarte))
    return NULL;
  if(compareCoord3(coord,getCoordLDP(ligneDeProd)))
    return ligneDeProd;
  if(getLDPSuivante(ligneDeProd) == NULL)
    return NULL;
  return findByCoordListLDP_aux(getLDPSuivante(ligneDeProd), coord, sizeCarte);
}

ligneDeProduction* findByCoordListLDP(listeLigneDeProduction *liste, coord* coord, int sizeCarte){
    if(getNbLDP(liste) == 0) return NULL;
  return findByCoordListLDP_aux(liste->startList,coord, sizeCarte);
}

void insertionListLDP(listeLigneDeProduction *liste, ligneDeProduction* ligneDeProd, int sizeCarte){
  /*
  if(liste->nbLigneDeProd == 0){
    liste->nbLigneDeProd ++;

    setLDPSuivante(ligneDeProd,NULL);
    liste->startList = ligneDeProd;

    setLDPNord(ligneDeProd,NULL);
    setLDPEst(ligneDeProd,NULL);
    setLDPSud(ligneDeProd,NULL);
    setLDPOuest(ligneDeProd,NULL);
  }
  */
  if(liste->nbLigneDeProd != 0) {
      setLDPSuivante(ligneDeProd,liste->startList);
  }
  liste->nbLigneDeProd ++;
  liste->startList = ligneDeProd;
  coord coordNord;
  setCoord2(&coordNord,getCoordLDP(ligneDeProd));
  setCoordY(&coordNord,getCoordY(&coordNord)-1);
  coord coordEst;
  setCoord2(&coordEst,getCoordLDP(ligneDeProd));
  setCoordX(&coordEst,getCoordX(&coordEst)+1);

  coord coordSud;
  setCoord2(&coordSud,getCoordLDP(ligneDeProd));
  setCoordY(&coordSud,getCoordY(&coordSud)+1);

  coord coordOuest;
  setCoord2(&coordOuest,getCoordLDP(ligneDeProd));
  setCoordX(&coordOuest,getCoordX(&coordOuest)-1);
  ligneDeProduction* voisinNord = findByCoordListLDP_aux(liste->startList,&coordNord, sizeCarte);
  setLDPNord(ligneDeProd,voisinNord);
  if(voisinNord != NULL)
    setLDPSud(voisinNord,ligneDeProd);

  ligneDeProduction* voisinEst = findByCoordListLDP_aux(liste->startList,&coordEst, sizeCarte);
  setLDPEst(ligneDeProd,voisinEst);
  if(voisinEst != NULL)
    setLDPOuest(voisinEst,ligneDeProd);
 

  ligneDeProduction* voisinSud = findByCoordListLDP_aux(liste->startList,&coordSud, sizeCarte);
  setLDPSud(ligneDeProd,voisinSud);
  if(voisinSud != NULL)
    setLDPNord(voisinSud,ligneDeProd);

  ligneDeProduction* voisinOuest = findByCoordListLDP_aux(liste->startList,&coordOuest, sizeCarte);
  setLDPOuest(ligneDeProd,voisinOuest);
  if(voisinOuest != NULL)
    setLDPEst(voisinOuest,ligneDeProd);
}

ligneDeProduction* getPredLDP_aux(ligneDeProduction* ligneDeProd1, ligneDeProduction* ligneDeProd2){
  if(getLDPSuivante(ligneDeProd1) == ligneDeProd2)
    return ligneDeProd1;
  if(getLDPSuivante(ligneDeProd1) == NULL)
    return NULL;
  return getPredLDP_aux(getLDPSuivante(ligneDeProd1), ligneDeProd2);
}

ligneDeProduction* getPredLDP(listeLigneDeProduction *liste, ligneDeProduction* ligneDeProd){
  return getPredLDP_aux(liste->startList, ligneDeProd);
}

void suppressionListLDP(listeLigneDeProduction *liste, ligneDeProduction* ligneDeProd){
  liste->nbLigneDeProd --;
  /* Suppression de l'élément au début de la liste */
  if(liste->startList == ligneDeProd){
    liste->startList = getLDPSuivante(ligneDeProd);
  }
  /* Suppression de l'élément au millieu de la liste */
  else{
    ligneDeProduction* ldpPred = getPredLDP(liste, ligneDeProd);
    if(ldpPred != NULL)
      setLDPSuivante(ldpPred, getLDPSuivante(ligneDeProd));
  }
  if(getLDPNord(ligneDeProd) != NULL)
    setLDPSud(getLDPNord(ligneDeProd),NULL);
  if(getLDPEst(ligneDeProd) != NULL)
    setLDPOuest(getLDPEst(ligneDeProd),NULL);
  if(getLDPSud(ligneDeProd) != NULL)
    setLDPNord(getLDPSud(ligneDeProd),NULL);
  if(getLDPOuest(ligneDeProd) != NULL)
    setLDPEst(getLDPOuest(ligneDeProd),NULL);
  free(getCoordLDP(ligneDeProd));
  free(ligneDeProd);
}

int getNbPersonnelList(listePersonnel* liste){
  return liste->nbPersonnel;
}

personnelCarte* getStartListPersonnel(listePersonnel* liste){
  return liste->startList;
}

listePersonnel* initialisationListePerso(){
  listePersonnel* liste = (listePersonnel*) malloc(sizeof(listePersonnel));
  liste->nbPersonnel = 0;
  liste->startList = NULL;
  return liste;
}

void insertionListPerso(listePersonnel *liste, personnelCarte* perso){
  setPersonnelSuivant(perso,liste->startList);
  liste->startList = perso;
  liste->nbPersonnel ++;
}

int CountById_aux(personnelCarte *perso, int id){
  if(perso == NULL)
    return 0;
  else 
    return (id == getNumPersonnel(getPersonnel(perso))) + CountById_aux(getPersonnelSuivant(perso), id);
}

int CountById(listePersonnel *liste, int id){
  return CountById_aux(liste->startList, id);
}
