#include "../headers/carte.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct s_infos_carte infos_carte = {.type = {"facile", "moyenne", "grande"},
                                    .hauteur = {10, 20, 30},
                                    .largeur = {10, 20, 30}};

coord* getCoordPorte(carte* plateau) {
    return plateau->coordPorte;
}

void initAchatFISAFISE(fisa* fisa,fise* fise){
    fisa->cout = (cout*) malloc(sizeof(cout));
    fise->cout = (cout*) malloc(sizeof(cout));
    (*fisa).cout->DD = COUT_ACHAT_ELEVE_DD;
    (*fisa).cout->E = COUT_ACHAT_ELEVE_E;
    (*fise).cout->DD = COUT_ACHAT_ELEVE_DD;
    (*fise).cout->E = COUT_ACHAT_ELEVE_E;
}

void initProductionFISAFISE(fisa* fisa,fise* fise){
    fisa->production = (cout*) malloc(sizeof(cout));
    fise->production = (cout*) malloc(sizeof(cout));
    (*fisa).production->DD = NB_INITIAL_DD_PRODUITS_FISA;
    (*fisa).production->E = NB_INITIAL_E_PRODUITS_FISA;
    (*fise).production->DD = NB_INITIAL_DD_PRODUITS_FISE;
    (*fise).production->E = NB_INITIAL_E_PRODUITS_FISE;
}


void libererMemoireCarte(carte* carte){
    free(carte);
}

void libererMemoireFISA(fisa* fisa){
    free(fisa);
}

void libererMemoireFISE(fise* fise){
    free(fise);
}


int recruterFISE(carte* carte,int nbRecruter){
    if (!updateCout(carte->ressourceJoueur,getCoutFISE(carte->fise))){ //Si manque d'argent
        return 0;
    }
    (*carte).nbFISE+= nbRecruter;
    return 1;
}


int recruterFISA(carte* carte,int nbRecruter){
    if (!updateCout(carte->ressourceJoueur,getCoutFISA(carte->fisa))){ //Si manque d'argent
        return 0;
    }
    (*carte).nbFISA+= nbRecruter;
    return 1;
}


void changementTypeRessource(carte* carte){
    if((*carte).typeRessourceFISA == DD)
        (*carte).typeRessourceFISA = E;
    else
        (*carte).typeRessourceFISA = DD;
    
}


int notSourceOuPortail(carte* carte,coord* coord){
    if
    (coord->x == getCoordPorte(carte)->x && coord->y == getCoordPorte(carte)->y){
        return 1;
    }
    else{
        for (int i = 0; i < NB_SOURCES_PLATEAU; i++)
    {
        if(coord->x == getCoordSource(carte,i)->x && coord->y == getCoordSource(carte,i)->y){
            return 1;
        }
    }
    }
    return 0;
}

int achatMachine
    (
        listeLigneDeProduction *liste, 
        machine* machine, coord* coord, 
        pointCard orientation, 
        cout* argent,
        carte* carte
    )
{
        ligneDeProduction* ldp = findByCoordListLDP(liste, coord, getTaille(carte));
        if( ldp != NULL || notSourceOuPortail(carte,coord) ){ //Si une machine existe déjà à cet endroit ou un portail ou une source a cette endroit
            return 1;
        }
        ligneDeProduction* newMachine = NULL;
        if ( ! addMachine(&newMachine, coord, machine, orientation, argent) ){ //Si manque d'argent
            return 2;
        }
        //Aucun problème (machine crée et ajouté à la liste)
        insertionListLDP(liste, newMachine, getTaille(carte));
        return 0;
}

int amelioreMachine(ligneDeProduction* ldp, cout* argent){
        if( ldp == NULL ){ //Si machine n'existe pas
            return 1;
        }
        if ( ! upMachine(ldp, argent) ){ //Si manque d'argent
            return 2;
        }
        //Aucun problème (machine amélioré)
        return 0;
}

int detruireMachine(listeLigneDeProduction* liste,ligneDeProduction* ldp, cout* argent, int* nbDechetPortail){
  if( ldp == NULL ){ //Si machine n'existe pas
    return 1;
  }
  if ( ! delMachine(ldp, argent, nbDechetPortail) ){ //Si manque d'argent
    return 2;
  }
  //Aucun problème (machine détruite et supprimée de la liste)
  suppressionListLDP(liste, ldp);
  return 0;
}


int recruterPersonnel
(
 
    carte* carte, 
    personnel* perso,
    machine** listeMachine,
    int nbMachine,
    personnel** listePerso,
    int nbPerso
    ){
        fisa* infoFisa = getInfoFisa(carte);
        fise* infoFise = getInfoFise(carte);
        if(updateCout(getRessourceJoueur(carte),getCoutAchat(perso))
        ){
            personnelCarte* persoCarte = (personnelCarte*) malloc (sizeof(personnelCarte));
            setPersonnel(persoCarte, perso);
            insertionListPerso(getListePersonnel(carte), persoCarte);
            activeEffetPersonnel
            (
                perso,carte,
                listeMachine,nbMachine,
                listePerso,nbPerso,
                infoFisa,
                infoFise
            );
        return 1;
        }
        return 0;
}

void effetCollecteurRessource(carte* carte){
    ligneDeProduction* ldp = getListeLigneDeProduction(carte)->startList;
    pointCard entree;
    coord* coordLDP;
    for(int i =0; i< getListeLigneDeProduction(carte)->nbLigneDeProd;i++){
        if(getTypeMachine(getMachine(ldp)) == COLLECTEUR){
            int ret = getFinChemin(ldp ,&coordLDP , &entree );
            ligneDeProduction *ldpFinChemin = findByCoordListLDP(
                    getListeLigneDeProduction(carte),
                    coordLDP,
                    getTaille(carte));
            if(ret == 1){
                for(int j=0;j<NB_SOURCES_PLATEAU;j++){
                    if(getCoordSource(carte,j)->x == coordLDP->x && getCoordSource(carte,j)->y == coordLDP->y){
                        addRessource(ldpFinChemin,getStockCurRessource(ldp));
                        setStockCurRessource(ldp,0);
                    }
                }
            }

            if(ret == 0){
                if(coordLDP->x == getCoordPorte(carte)->x && coordLDP->y == getCoordPorte(carte)->y){
                    ajouterDechetPortail(carte,getStockCurRessource(ldp));
                }
                else{
                    setStockCurRessource(ldp,0);
                }
                setStockCurRessource(ldp,0);
            }

            if(ret == 2){
                setStockCurRessource(ldp,0);
            } 
        }
    }
    free(coordLDP);
}

void effetCollecteurDechet(carte* carte){
    ligneDeProduction* ldp = getListeLigneDeProduction(carte)->startList;
    pointCard entree;
    coord* coordLDP;
    int pNbPortail = getNbDechetPortail(carte);
    for(int i =0; i< getListeLigneDeProduction(carte)->nbLigneDeProd;i++){
        if(getTypeMachine(getMachine(ldp)) == COLLECTEUR){
            int ret = getFinChemin(ldp ,&coordLDP , &entree );
            ligneDeProduction *ldpFinChemin = findByCoordListLDP(
                        getListeLigneDeProduction(carte),
                        coordLDP,
                        getTaille(carte));
            if (ret == 1)
            {
                addDechet(ldpFinChemin,getStockCurDechet(ldp),&pNbPortail);
                setStockCurDechet(ldp,0);
            }  

            if(ret == 0){
                if((*coordLDP).x == getCoordPorte(carte)->x && (*coordLDP).y == getCoordPorte(carte)->y){
                    ajouterDechetPortail(carte,getStockCurDechet(ldp));
                    setStockCurDechet(ldp,0);
                }                
            }
            if(ret == 2){
                ajouterDechetPortail(carte,getStockCurDechet(ldp));
                setStockCurDechet(ldp,0);
            }
        }     
    }
    free(coordLDP);
}


void effetCentreRecyclage(carte* carte){
ligneDeProduction* ldp = getListeLigneDeProduction(carte)->startList;
coord* coordLDP;
pointCard sortie;
for (int i = 0; i < getListeLigneDeProduction(carte)->nbLigneDeProd;i++)
{
    if(getTypeMachine(getMachine(ldp)) == RECYCLAGE){
        if(getStockCurDechet(ldp) > 10){
            int ret = getFinChemin(ldp,&coordLDP,&sortie);
            ligneDeProduction *ldpFinChemin = findByCoordListLDP(
                        getListeLigneDeProduction(carte),
                        coordLDP,
                        getTaille(carte));
            if(ret == 1){
                addRessource(ldpFinChemin,1);
                setStockCurDechet(ldp,0);
            }
            else {
                setStockCurDechet(ldp,0);
            }
        }
    }
}
}


/********** Effet personnel **********/

void activeEffetPersonnel(personnel* perso, 
    carte* plateau, 
    machine** listeMachineDispo, 
    int nbMachine, 
    personnel** listePersoDispo, 
    int nbPerso, fisa* infoFISA, 
    fise* infoFISE)
{
  switch( getNumPersonnel(perso)){
    case 1 :
      {machine* collecteurs= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == COLLECTEUR){
          collecteurs = listeMachineDispo[i];
          break;
        }
      }
      updateCoutConstructionE(collecteurs,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutConstructionDD(collecteurs,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 2 :
      {machine* tapis = NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == TAPIS){
          tapis = listeMachineDispo[i];
          break;
        }
      }
      updateCoutConstructionE(tapis,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutConstructionDD(tapis,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 3 :
      {machine* croix= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == CROIX){
          croix = listeMachineDispo[i];
          break;
        }
      }
      updateCoutConstructionE(croix,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutConstructionDD(croix,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 4 :
      {machine* recyclage= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == RECYCLAGE){
          recyclage = listeMachineDispo[i];
          break;
        }
      }
      updateCoutConstructionE(recyclage,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutConstructionDD(recyclage,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 5 :
      {machine* dechetterie= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == DECHETTERIE){
          dechetterie = listeMachineDispo[i];
          break;
        }
      }
      updateCoutConstructionE(dechetterie,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutConstructionDD(dechetterie,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 6 :
      {machine* collecteurs= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == COLLECTEUR){
          collecteurs = listeMachineDispo[i];
          break;
        }
      }
      updateCoutAmeliorationE(collecteurs,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutAmeliorationDD(collecteurs,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 7 :
      {machine* recyclage= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == RECYCLAGE){
          recyclage = listeMachineDispo[i];
          break;
        }
      }
      updateCoutAmeliorationE(recyclage,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutAmeliorationDD(recyclage,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 8 :
      {machine* dechetterie= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == DECHETTERIE){
          dechetterie = listeMachineDispo[i];
          break;
        }
      }
      updateCoutAmeliorationE(dechetterie,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutAmeliorationDD(dechetterie,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 9 :
     { machine* collecteurs= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == COLLECTEUR){
          collecteurs = listeMachineDispo[i];
          break;
        }
      }
      updateCoutDestructionE(collecteurs,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutDestructionDD(collecteurs,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 10 :
      {machine* tapis= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == TAPIS){
          tapis = listeMachineDispo[i];
          break;
        }
      }
      updateCoutDestructionE(tapis,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutDestructionDD(tapis,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 11 :
      {machine* croix= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == CROIX){
          croix = listeMachineDispo[i];
          break;
        }
      }
      updateCoutDestructionE(croix,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutDestructionDD(croix,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 12 :
      {machine* recyclage= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == RECYCLAGE){
          recyclage = listeMachineDispo[i];
          break;
        }
      }
      updateCoutDestructionE(recyclage,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutDestructionDD(recyclage,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 13 :
      {machine* dechetterie= NULL;
      for(int i = 0; i < nbMachine; i++){
        if( getTypeMachine(listeMachineDispo[i]) == DECHETTERIE){
          dechetterie = listeMachineDispo[i];
          break;
        }
      }
      updateCoutDestructionE(dechetterie,-getCoutE(perso->action),getCoutE(perso->min_action));
      updateCoutDestructionDD(dechetterie,-getCoutDD(perso->action),getCoutDD(perso->min_action));
      break;}
    case 14 :
      enleveDechet(plateau, getCoutE(perso->action));
      break;
    case 15 :
      recruterFISA(plateau, getCoutE(perso->action));
      recruterFISE(plateau, getCoutDD(perso->action));
      break;
    case 16 :
      break;
    case 17 :
      break;
    case 18 :
      updateCoutFise(infoFISE, -getCoutDD(perso->action), -getCoutE(perso->action), getCoutDD(perso->min_action), getCoutE(perso->min_action));
      break;
    case 19 :
      updateCoutFisa(infoFISA, -getCoutDD(perso->action), -getCoutE(perso->action), getCoutDD(perso->min_action), getCoutE(perso->min_action));
      break;
    case 20 :
      for(int i = 0; i < nbPerso; i++){
        updateCoutAchat(listePersoDispo[i], getCoutDD(perso->action), getCoutE(perso->action), getCoutDD(perso->min_action), getCoutE(perso->min_action));
      }
      break;
    case 21 :
      updateProductionFise(infoFISE, getCoutDD(perso->action), getCoutE(perso->action));
      break;
    case 22 :
      modifierFrequenceProductionSource(plateau,getFrequenceProductionSource(plateau) - getCoutE(perso->action));
      break;
    case 23 :
      updateProductionFisa(infoFISA, getCoutDD(perso->action), getCoutE(perso->action));
      break;
    case 24 :
      diplomerEleve(plateau,getCoutE(perso->action));
      break;
    default :
      break;
  }
}

void updateCoutFise(fise* infoFise,int persoDD,int persoE,int persoE_Min,int persoDD_Min){
    updateCoutE((*infoFise).cout,-(persoE),persoE_Min);
    updateCoutDD((*infoFise).cout,-(persoDD),persoDD_Min);
}
void updateCoutFisa(fisa* infoFisa,int persoDD,int persoE,int persoE_Min,int persoDD_Min){
    updateCoutE((*infoFisa).cout,-(persoE),persoE_Min);
    updateCoutDD((*infoFisa).cout,-(persoDD),persoDD_Min);
}

fisa* getInfoFisa(carte* carte){
    return (*carte).fisa;
}
fise* getInfoFise(carte* carte){
    return (*carte).fise;
}
void ajouterDechetPortail(carte* carte,int val){
    (*carte).nbDechetPortail += val;
}
int getNbRessource(carte* carte){
    return (*carte).nbRessource;
}
void setNbRessource(carte* carte,int nb){
    (*carte).nbRessource = nb;
}
int getNbCroix(carte* carte){
    return (*carte).nbCroix;
}
void setNbCroix(carte* carte,int nb){
    (*carte).nbCroix = nb;
}
int getNbTapisRoulant(carte* carte){
    return (*carte).nbTapisRoulant;
}
void setNbTapisRoulant(carte* carte,int nb){
    (*carte).nbTapisRoulant = nb;
}
int getNbDechetterie(carte* carte){
    return (*carte).nbDecheterie;
}
void setNbDechetterie(carte* carte,int nb){
    (*carte).nbDecheterie = nb;
}
int nbDechet(carte* carte){
    return (*carte).nbDechet;
}
void setNbDechet(carte* carte,int nb){
    (*carte).nbDechet = nb;
}
int nbRecycleur(carte* carte){
    return (*carte).nbRecycleur;
}
void setNbRecycleur(carte* carte,int nb){
    (*carte).nbRecycleur = nb;
}
int nbCollecteur(carte* carte){
    return (*carte).nbCollecteur;
}
void setNbCollecteur(carte* carte,int nb){
    (*carte).nbCollecteur = nb;
}

coord* getCoordSource(carte* plateau, int i) {
  /* plateau = NULL ? */
  if(i >= NB_SOURCES_PLATEAU)
    return NULL;

  return plateau->coordSources[i];
}

coord** getCoordSources(carte* plateau) {
  /* plateau = NULL ? */

  return plateau->coordSources;
}

void setCoordPorte(carte* plateau, int x, int y) {
  setCoord((plateau->coordPorte), x, y, getTaille(plateau));
}

void setCoordSource(carte* plateau, int i, int x, int y) {
  setCoord((plateau->coordSources[i]), x, y, getTaille(plateau));
}

void diplomerEleve(carte* carte,int n){
    int nbFISAMoins = ((*carte).nbFISA)/n;
    int nbFISEMoins = ((*carte).nbFISE)/n;
    printf("%d %d\n", nbFISAMoins, nbFISEMoins);
    (*carte).nbFISA -= nbFISAMoins;
    (*carte).nbFISE -= nbFISEMoins;
    (*carte).nbRessourcePortail += nbFISAMoins + nbFISEMoins;
}

void updateProductionFise(fise* infoFISE, int nbDD, int nbE){
    (*infoFISE).production->DD = nbDD;
    (*infoFISE).production->E = nbE;
}
void updateProductionFisa(fisa* infoFISA, int nbDD, int nbE){
    (*infoFISA).production->DD = nbDD;
    (*infoFISA).production->E = nbE;
}
void enleveDechet(carte* carte, int nb){
    ligneDeProduction* ldp = getListeLigneDeProduction(carte)->startList;
    while (ldp != NULL)
    {
      if(getTypeMachine(getMachine(ldp)) == CROIX)
        setStockCurDechet2(ldp,round(getStockCurDechet2(ldp)/nb));
      setStockCurDechet(ldp,round(getStockCurDechet(ldp)/nb));
      ldp = getLDPSuivante(ldp);
    }
    setNbDechetPortail(carte,round((*carte).nbDechetPortail/nb));
}

int* getNbRessourceSource(carte* carte){
   return (*carte).nbRessourceSource;
}
void dechetRecycle(carte* carte,int nbRecycle){
    (*carte).nbDechetPortail -= nbRecycle;
}

void modifierFrequenceProductionSource(carte* carte,int freq){
    (*carte).freqSource -= freq;
}
int getFrequenceProductionSource(carte* carte){
    return (*carte).freqSource;
}
void incrRessourceSource(carte* carte){
    for(int i=0; i < NB_SOURCES_PLATEAU; i++)
      (*carte).nbRessourceSource[i] += 3;
}

ligneDeProduction* getLigneDeProd(cellule* cellule){
    return (*cellule).ligneDeProduction;
}

listeLigneDeProduction* getListeLigneDeProduction(carte* carte){
    return (*carte).listeLigneDeProduction;
}

coord getCoordonne(carte* carte){
    return (*carte).coord;
}

int getNbFISA(carte* carte){
    return (*carte).nbFISA;
}

int getNbFISE(carte* carte){
    return (*carte).nbFISE;
}
cout *getCoutFISA(fisa* fisa){
    return (*fisa).cout;
}
cout *getCoutFISE(fise* fise){
    return (*fise).cout;
}
cout *getProductionFISE(fise* fise){
    return (*fise).production;
}
cout *getProductionFISA(fisa* fisa){
    return (*fisa).production;
}


int getTaille(carte* carte){
    return (*carte).taille;
}

cout* getRessourceJoueur(carte* carte){
    return (*carte).ressourceJoueur;
}

int getNbTours(carte* carte){
    return (*carte).nbTours;
}


int getFISE(carte*carte){
    return (*carte).nbFISE;
}


int getFISA(carte* carte){
        return (*carte).nbFISA;
}


int getNbDechetPortail(carte* carte){
    return (*carte).nbDechetPortail;
}

void setNbDechetPortail(carte* carte, int dechet){
    (*carte).nbDechetPortail = dechet;
}


int getNbRessourcePortail(carte* carte){
    return (*carte).nbRessourcePortail;
}


int getNbPersonnel(carte* carte){
    return (*carte).nbPersonnel;
}


typeRessource getTypeRessourceFISA(carte* carte){
    return (*carte).typeRessourceFISA;
}


listePersonnel* getListePersonnel(carte* carte){
    return (*carte).listePersonnel;
}


typeCase getTypeCase(cellule* cellule){
    return (*cellule).typeCase;
}

void setTypeCase(cellule* cellule,typeCase typeCase){
    (*cellule).typeCase  = typeCase;
}

void setLigneDeProd(cellule* cellule){
    (*cellule).ligneDeProduction = (ligneDeProduction*) malloc(sizeof(ligneDeProduction));
}

//TODO
void getNombresAleatoires(int tailleCarte, int *listeNombresAleatoires) {
  listeNombresAleatoires[0] = 0;
  listeNombresAleatoires[1] = 0;
  listeNombresAleatoires[2] = 0;
  listeNombresAleatoires[3] = 1;
  listeNombresAleatoires[4] = 0;
  listeNombresAleatoires[5] = 2;
  listeNombresAleatoires[6] = 0;
  listeNombresAleatoires[7] = 3;

    /*listeNombresAleatoires[0] = rand()%tailleCarte;
    listeNombresAleatoires[1] = rand()%tailleCarte;

    do {
        listeNombresAleatoires[2] = rand()%tailleCarte;
        listeNombresAleatoires[3] = rand()%tailleCarte;
    } while((listeNombresAleatoires[2] == listeNombresAleatoires[0]) && (listeNombresAleatoires[3] == listeNombresAleatoires[1]));

    do {
        listeNombresAleatoires[4] = rand()%tailleCarte;
        listeNombresAleatoires[5] = rand()%tailleCarte;
    } while(((listeNombresAleatoires[4] == listeNombresAleatoires[0]) && (listeNombresAleatoires[5] == listeNombresAleatoires[1])) ||
            ((listeNombresAleatoires[4] == listeNombresAleatoires[2]) && (listeNombresAleatoires[5] == listeNombresAleatoires[3])));

    do {
        listeNombresAleatoires[6] = rand()%tailleCarte;
        listeNombresAleatoires[7] = rand()%tailleCarte;
    } while(((listeNombresAleatoires[6] == listeNombresAleatoires[0]) && (listeNombresAleatoires[7] == listeNombresAleatoires[1])) ||
            ((listeNombresAleatoires[6] == listeNombresAleatoires[2]) && (listeNombresAleatoires[7] == listeNombresAleatoires[3])) ||
            ((listeNombresAleatoires[6] == listeNombresAleatoires[4]) && (listeNombresAleatoires[7] == listeNombresAleatoires[5])));*/
}

carte* creationCarte(int taille){
    carte* Carte = (carte*) malloc(taille*sizeof(carte));
    (*Carte).taille = taille;
    (*Carte).nbFISA = NB_INITIAL_FISA;
    (*Carte).nbFISE = NB_INITIAL_FISE;
    (*Carte).freqSource = 10;
    Carte->ressourceJoueur = (cout*) malloc(sizeof(cout));
    setCoutE(Carte->ressourceJoueur, E_INITIAL);
    (*Carte).ressourceJoueur->DD = DD_INITIAL;
    (*Carte).nbTours = 0;
    (*Carte).nbPersonnel = 0;
    (*Carte).nbDechetPortail = 0;
    (*Carte).nbRessourcePortail = 0;
    Carte->listePersonnel = initialisationListePerso();
    Carte->listeLigneDeProduction = initialisationListeLDP();
    Carte->coordPorte = (coord*) malloc(sizeof(coord));

    int *listeNombresAleatoires = malloc(8*sizeof(int));
    getNombresAleatoires(Carte->taille, listeNombresAleatoires);

    setCoord(Carte->coordPorte, listeNombresAleatoires[0], listeNombresAleatoires[1], getTaille(Carte));
    Carte->coordSources = (coord**) malloc(NB_SOURCES_PLATEAU*sizeof(coord*));
    Carte->nbRessourceSource = (int*) malloc(NB_SOURCES_PLATEAU*sizeof(int));
    Carte->coordSources[0] = (coord*) malloc(sizeof(coord));
    Carte->coordSources[1] = (coord*) malloc(sizeof(coord));
    Carte->coordSources[2] = (coord*) malloc(sizeof(coord));
    setCoord(Carte->coordSources[0], listeNombresAleatoires[2], listeNombresAleatoires[3], getTaille(Carte));
    setCoord(Carte->coordSources[1], listeNombresAleatoires[4], listeNombresAleatoires[5], getTaille(Carte));
    setCoord(Carte->coordSources[2], listeNombresAleatoires[6], listeNombresAleatoires[7], getTaille(Carte));

    free(listeNombresAleatoires);

    fisa* fisa1 = (fisa*) malloc(sizeof(fisa));
    fise* fise1 = (fise*) malloc(sizeof(fise));
    Carte->fisa = fisa1;
    Carte->fise = fise1;
    initAchatFISAFISE(fisa1, fise1);
    initProductionFISAFISE(fisa1, fise1);
    return Carte;
}

pointCard getoppose(pointCard pc) {
  switch(pc) {
    case NORD:
      return SUD;
    case EST:
      return OUEST;
    case SUD:
      return NORD;
    case OUEST:
    default:
      return EST;
  }
}

void trieListe(pointCard* liste, int nb_element){
  if(nb_element) return ;
  if( liste[0]%2 > liste[1]%2){
    pointCard pc = liste[0];
    liste[0] = liste[1];
    liste[1] = pc;
  }
}

void printLDP(ligneDeProduction* ldp) {
  switch(getTypeMachine(getMachine(ldp))) {
    case TAPIS:
      printf("TAPIS");
      break;
    case CROIX:
      printf("CROIX");
      break;
    case DECHETTERIE:
      printf("DECHETTERIE");
      break;
    case RECYCLAGE:
      printf("RECYCLAGE");
      break;
    case COLLECTEUR:
      printf("COLLECTEUR");
      break;
  }

  coord* c = getCoordLDP(ldp);
  printf(" en %d %d", getCoordX(c), getCoordY(c));
}

int appliquer_effet_gael_thomas(int ressources, int nb_gael, int chance) {
  int total = ressources;

  if(chance > 0) {
    for(int i = 0; i < ressources; i++) {
      printf("R %d\n", i);
      for(int j = 0; j < nb_gael; j++) {
        printf("GAEL %d : ", j);
        int r = rand() % chance;
        printf("%d\n", r);
        if(r == 0) {
          printf("Total %d -> ", total);
          total--;
          printf("%d\n", total);
          break;
        }
      }
    }
  }

  return total;
}

void traitementMachine(ligneDeProduction* ldp, pointCard* origine, 
    listeLigneDeProduction* machines_traitees, carte* plateau, int* cptNewR) {
  ligneDeProduction* chercher = getStartListLDP(machines_traitees);
  int trouvee = 0;
  while(chercher != NULL) {
    if(compareCoord2(getCoordLDP(ldp), getCoordLDP(chercher)) == 0) {
      trouvee = 1;
      break;
    }
    chercher = getLDPSuivante(chercher);
  }
  
  if(!trouvee) {
    ligneDeProduction* new = (ligneDeProduction*) malloc(sizeof(ligneDeProduction));
    setCoordLDP(new, getCoordLDP(ldp));
    new->suivant = NULL;
    new->ldpNord = NULL;
    new->ldpEst = NULL;
    new->ldpSud = NULL;
    new->ldpOuest = NULL;
    insertionListLDP(machines_traitees, new, getTaille(plateau));

    /// A FAIRE
    if(getTypeMachine(getMachine(ldp)) != DECHETTERIE) {
      pointCard sortie;
      int nb;
      pointCard* liste;
      getSortieDynamique(ldp, &liste, &nb);
      trieListe(liste, nb);
      for(int i = 0; i < nb; i++){
        switch(getTypeMachine(getMachine(ldp))) {
          case COLLECTEUR:
          case TAPIS:
          case RECYCLAGE:
            sortie = liste[i];
            break;
          case CROIX:
            sortie = liste[i];
            break;
          default:;
        }

        ligneDeProduction* ldp_suivante;
        int plusx = 0;
        int plusy = 0;
        switch(sortie) {
          case NORD:
            ldp_suivante = getLDPNord(ldp);
            plusy = -1;
            break;
          case EST:
            ldp_suivante = getLDPEst(ldp);
            plusx = +1;
            break;
          case SUD:
            ldp_suivante = getLDPSud(ldp);
            plusy = +1;
            break;
          case OUEST:
            ldp_suivante = getLDPOuest(ldp);
            plusx = -1;
            break;
        }
        //SUITE
        int bool_croix = 0;
        if(ldp_suivante != NULL) {
          int suivante_a_entree = 0;
          int nb2;
          pointCard* liste2;
          getEntreeDynamique(ldp_suivante, &liste2, &nb2);

          for(int j = 0; j < nb2; j++) {
            if(liste2[j] == getoppose(sortie)){
              suivante_a_entree = 1;
              if(getTypeMachine(getMachine(ldp_suivante))== CROIX){
                  bool_croix = liste2[j]%2;
              }
            }
          }
          free(liste2);
          // MODIF
          if(suivante_a_entree) {
            pointCard opp = getoppose(sortie);
            traitementMachine(ldp_suivante, &opp, machines_traitees, plateau, cptNewR);

            switch(getTypeMachine(getMachine(ldp_suivante))) {
              case TAPIS: ;
                if(getTypeMachine(getMachine(ldp)) != RECYCLAGE)
                  ldp_suivante->stockCourrantDechet[0] += ldp->stockCourrantDechet[i];
                ldp_suivante->stockCourrantRessource[0] += ldp->stockCourrantRessource[i];
                break;
              case RECYCLAGE:
              case DECHETTERIE:
                if(ldp_suivante->stockCourrantDechet[0] + ldp->stockCourrantDechet[i] > getStockMax(ldp_suivante)) {
                  plateau->nbDechetPortail += ldp->stockCourrantDechet[i] - (getStockMax(ldp_suivante) - ldp_suivante->stockCourrantDechet[0]);
                  ldp_suivante->stockCourrantDechet[0] = getStockMax(ldp_suivante);
                } else
                  ldp_suivante->stockCourrantDechet[0] += ldp->stockCourrantDechet[i];
                break;
              case CROIX:
                if(getTypeMachine(getMachine(ldp)) != RECYCLAGE)
                  ldp_suivante->stockCourrantDechet[bool_croix] += ldp->stockCourrantDechet[i];
                ldp_suivante->stockCourrantRessource[bool_croix] += ldp->stockCourrantRessource[i];
                break;
              default:;
            }

            if(getTypeMachine(getMachine(ldp)) != RECYCLAGE)
              ldp->stockCourrantDechet[i] = 0;
            ldp->stockCourrantRessource[i] = 0;
          } else {
            if(getTypeMachine(getMachine(ldp)) != RECYCLAGE) {
              plateau->nbDechetPortail += ldp->stockCourrantDechet[i];
              ldp->stockCourrantDechet[i] = 0;
            }
            ldp->stockCourrantRessource[i] = 0;
          }
        } else { //Si case vide
          coord sortiec;
          setCoord(&sortiec, getCoordX(getCoordLDP(ldp)) + plusx, getCoordY(getCoordLDP(ldp)) + plusy, getTaille(plateau));

          if(compareCoord2(getCoordPorte(plateau), &sortiec) == 0) {
            if(getTypeMachine(getMachine(ldp)) != RECYCLAGE) {
              plateau->nbDechetPortail += ldp->stockCourrantDechet[i];
              ldp->stockCourrantDechet[i] = 0;
            }
            plateau->nbRessourcePortail += ldp->stockCourrantRessource[i]*(1 + CountById(getListePersonnel(plateau), 16));
            *cptNewR += ldp->stockCourrantRessource[i];
            ldp->stockCourrantRessource[i] = 0;
          } else {
            if(getTypeMachine(getMachine(ldp)) != RECYCLAGE) {
              plateau->nbDechetPortail += ldp->stockCourrantDechet[i];
              ldp->stockCourrantDechet[i] = 0;
            }
            ldp->stockCourrantRessource[i] = 0;
          }
        }
      }
      free(liste);
    }
  }
}

void free_machine_traitee(ligneDeProduction* ldp) {
  if(ldp != NULL) {
    free_machine_traitee(getLDPSuivante(ldp));
    free(ldp);
  }
}

void terminerTour(carte *carte){
  fisa* fisa = (*carte).fisa;
  fise* fise= (*carte).fise;
  if(getNbRessourcePortail(carte) < RESSOURCES_FIN_PARTIE){

    //Récupère ressources élève
    if(getNbTours(carte) % 2 == 0){
      if(getTypeRessourceFISA(carte) == DD)
        updateCout3(getRessourceJoueur(carte),(carte->nbFISA)*getProductionFISA(fisa)->DD,0);
      else
        updateCout3(getRessourceJoueur(carte),0,(carte->nbFISA)*getProductionFISA(fisa)->E);
    }
    updateCout3(getRessourceJoueur(carte),(carte->nbFISE)*getProductionFISE(fise)->DD,(carte->nbFISE)*getProductionFISE(fise)->E);

    //Déplacer ressources et déchet
    int cptNewRessource = 0;
    ligneDeProduction* ldp = carte->listeLigneDeProduction->startList;
    listeLigneDeProduction* machines_traitees = initialisationListeLDP();
    while(ldp != NULL){
      traitementMachine(ldp, NULL, machines_traitees, carte, &cptNewRessource);
      ldp = ldp->suivant;
    }

    free_machine_traitee(getStartListLDP(machines_traitees));
    free(machines_traitees);

    //Remplir Sources
    if(getNbTours(carte) % getFrequenceProductionSource(carte) == 0){
      incrRessourceSource(carte);
    }

    //Effet recycleur
    ldp = carte->listeLigneDeProduction->startList;
    while(ldp != NULL){
      if(getTypeMachine(getMachine(ldp)) == RECYCLAGE){
        while(ldp->stockCourrantDechet[0] >= 10){
          ldp->stockCourrantDechet[0] -= 10;
          ldp->stockCourrantRessource[0] += 1;
        }
      }
      ldp = ldp->suivant;
    }

    //Créer déchet porte
    ajouterDechetPortail(carte,cptNewRessource);

    //Ressource
    for(int i=0; i< NB_SOURCES_PLATEAU; i++){
      if(carte->nbRessourceSource[i] != 0){
        coord coordNord;
        setCoord2(&coordNord,carte->coordSources[i]);
        setCoordY(&coordNord,getCoordY(&coordNord)+1);
        coord coordEst;
        setCoord2(&coordEst,carte->coordSources[i]);
        setCoordX(&coordEst,getCoordX(&coordEst)+1);
        coord coordSud;
        setCoord2(&coordSud,carte->coordSources[i]);
        setCoordY(&coordSud,getCoordY(&coordSud)-1);
        coord coordOuest;
        setCoord2(&coordOuest,carte->coordSources[i]);
        setCoordX(&coordOuest,getCoordX(&coordOuest)-1);
        ligneDeProduction* ldpNord = findByCoordListLDP(carte->listeLigneDeProduction, &coordNord, carte->taille);
        if(carte->nbRessourceSource[i] != 0 && ldpNord != NULL && getTypeMachine(getMachine(ldpNord)) == COLLECTEUR){
          int j = carte->nbRessourceSource[i] - ldpNord->stockMax + ldpNord->stockCourrantDechet[0] + ldpNord->stockCourrantRessource[0];
          if(j < 0){
            addRessource(ldpNord,carte->nbRessourceSource[i]);
            carte->nbRessourceSource[i] = 0;
          }
          else{
            addRessource(ldpNord,carte->nbRessourceSource[i] - j);
            carte->nbRessourceSource[i] = j;
          }
        }
        ligneDeProduction* ldpOuest= findByCoordListLDP(carte->listeLigneDeProduction, &coordOuest, carte->taille);
        if(carte->nbRessourceSource[i] != 0 && ldpOuest != NULL && getTypeMachine(getMachine(ldpOuest)) == COLLECTEUR){
          int j = carte->nbRessourceSource[i] - ldpOuest->stockMax + ldpOuest->stockCourrantDechet[0] + ldpOuest->stockCourrantRessource[0];
          if(j < 0){
            addRessource(ldpOuest,carte->nbRessourceSource[i]);
            carte->nbRessourceSource[i] = 0;
          }
          else{
            addRessource(ldpOuest,carte->nbRessourceSource[i] - j);
            carte->nbRessourceSource[i] = j;
          }
        }
        ligneDeProduction* ldpEst = findByCoordListLDP(carte->listeLigneDeProduction, &coordEst, carte->taille);
        if(carte->nbRessourceSource[i] != 0 && ldpEst != NULL && getTypeMachine(getMachine(ldpEst)) == COLLECTEUR){
          int j = carte->nbRessourceSource[i] - ldpEst->stockMax + ldpEst->stockCourrantDechet[0] + ldpEst->stockCourrantRessource[0];
          if(j < 0){
            addRessource(ldpEst,carte->nbRessourceSource[i]);
            carte->nbRessourceSource[i] = 0;
          }
          else{
            addRessource(ldpEst,carte->nbRessourceSource[i] - j);
            carte->nbRessourceSource[i] = j;
          }
        }
        ligneDeProduction* ldpSud = findByCoordListLDP(carte->listeLigneDeProduction, &coordSud, carte->taille);
        if(carte->nbRessourceSource[i] != 0 && ldpSud != NULL && getTypeMachine(getMachine(ldpSud)) == COLLECTEUR){
          int j = carte->nbRessourceSource[i] - ldpSud->stockMax + ldpSud->stockCourrantDechet[0] + ldpSud->stockCourrantRessource[0];
          if(j < 0){
            addRessource(ldpSud,carte->nbRessourceSource[i]);
            carte->nbRessourceSource[i] = 0;
          }
          else{
            addRessource(ldpSud,carte->nbRessourceSource[i] - j);
            carte->nbRessourceSource[i] = j;
          }
        }
        carte->nbRessourceSource[i] = 0;
      }
      
    }
    
    //Dechets porte
    if(carte->nbDechetPortail != 0){
        int nb_gael = CountById(getListePersonnel(carte), 17);
        int chance = 0;

        if(nb_gael > 0) {
          personnelCarte* pc = getStartListPersonnel(getListePersonnel(carte));
          while(pc != NULL) {
            if(getNumPersonnel(getPersonnel(pc)) == 17) {
              chance = getCoutE(getPersonnel(pc)->action);
              break;
            }

            pc = getPersonnelSuivant(pc);
          }
        }

        coord coordNord;
        setCoord2(&coordNord,carte->coordPorte);
        setCoordY(&coordNord,getCoordY(&coordNord)+1);
        coord coordEst;
        setCoord2(&coordEst,carte->coordPorte);
        setCoordX(&coordEst,getCoordX(&coordEst)+1);
        coord coordSud;
        setCoord2(&coordSud,carte->coordPorte);
        setCoordY(&coordSud,getCoordY(&coordSud)-1);
        coord coordOuest;
        setCoord2(&coordOuest,carte->coordPorte);
        setCoordX(&coordOuest,getCoordX(&coordOuest)-1);
        ligneDeProduction* ldpNord = findByCoordListLDP(carte->listeLigneDeProduction, &coordNord, carte->taille);
        if(carte->nbDechetPortail != 0 && ldpNord != NULL && getTypeMachine(getMachine(ldpNord)) == COLLECTEUR){
          int j = carte->nbDechetPortail - ldpNord->stockMax + ldpNord->stockCourrantDechet[0] + ldpNord->stockCourrantRessource[0];
          if(j < 0){
            addDechet(ldpNord,
              appliquer_effet_gael_thomas(carte->nbDechetPortail, nb_gael, chance), 
              &carte->nbDechetPortail);
            carte->nbDechetPortail = 0;
          }
          else{
            addDechet(ldpNord,
              appliquer_effet_gael_thomas(carte->nbDechetPortail - j, nb_gael, chance), 
              &carte->nbDechetPortail);
            carte->nbDechetPortail = j;
          }
        }
        ligneDeProduction* ldpOuest= findByCoordListLDP(carte->listeLigneDeProduction, &coordOuest, carte->taille);
        if(carte->nbDechetPortail != 0 && ldpOuest != NULL && getTypeMachine(getMachine(ldpOuest)) == COLLECTEUR){
          int j = carte->nbDechetPortail - ldpOuest->stockMax + ldpOuest->stockCourrantDechet[0] + ldpOuest->stockCourrantRessource[0];
          if(j < 0){
            addDechet(ldpOuest,
              appliquer_effet_gael_thomas(carte->nbDechetPortail, nb_gael, chance), 
              &carte->nbDechetPortail);
            carte->nbDechetPortail = 0;
          }
          else{
            addDechet(ldpOuest,
              appliquer_effet_gael_thomas(carte->nbDechetPortail - j, nb_gael, chance), 
              &carte->nbDechetPortail);
            carte->nbDechetPortail = j;
          }
        }
        ligneDeProduction* ldpEst = findByCoordListLDP(carte->listeLigneDeProduction, &coordEst, carte->taille);
        if(carte->nbDechetPortail != 0 && ldpEst != NULL && getTypeMachine(getMachine(ldpEst)) == COLLECTEUR){
          int j = carte->nbDechetPortail - ldpEst->stockMax + ldpEst->stockCourrantDechet[0] + ldpEst->stockCourrantRessource[0];
          if(j < 0){
            addDechet(ldpEst,
              appliquer_effet_gael_thomas(carte->nbDechetPortail, nb_gael, chance), 
              &carte->nbDechetPortail);
            carte->nbDechetPortail= 0;
          }
          else{
            addDechet(ldpEst,
              appliquer_effet_gael_thomas(carte->nbDechetPortail - j, nb_gael, chance), 
              &carte->nbDechetPortail);
            carte->nbDechetPortail = j;
          }
        }
        ligneDeProduction* ldpSud = findByCoordListLDP(carte->listeLigneDeProduction, &coordSud, carte->taille);
        if(carte->nbDechetPortail != 0 && ldpSud != NULL && getTypeMachine(getMachine(ldpSud)) == COLLECTEUR){
          int j = carte->nbDechetPortail - ldpSud->stockMax + ldpSud->stockCourrantDechet[0] + ldpSud->stockCourrantRessource[0];
          if(j < 0){
            addDechet(ldpSud,
              appliquer_effet_gael_thomas(carte->nbDechetPortail, nb_gael, chance), 
              &carte->nbDechetPortail);
            carte->nbDechetPortail = 0;
          }
          else{
            addDechet(ldpSud,
              appliquer_effet_gael_thomas(carte->nbDechetPortail - j, nb_gael, chance), 
              &carte->nbDechetPortail);
            carte->nbDechetPortail = j;
          }
        }
      }

    //Décrémenter en fonction des déchet sur la carte TODO
    if(getNbDechetPortail(carte)>0){
      updateCout2(getRessourceJoueur(carte),getNbDechetPortail(carte),0);
    }

    /*coord cc1;
    coord cc2;
    coord cc3;
    coord cc4;
    coord cc5;
    coord cc6;
    coord cc7;
    setCoord(&cc1, 1, 0, getTaille(carte));
    setCoord(&cc2, 2, 0, getTaille(carte));
    setCoord(&cc3, 2, 1, getTaille(carte));
    setCoord(&cc4, 2, 2, getTaille(carte));
    setCoord(&cc5, 1, 2, getTaille(carte));
    setCoord(&cc6, 1, 1, getTaille(carte));
    setCoord(&cc7, 3, 0, getTaille(carte));
    findByCoordListLDP(getListeLigneDeProduction(carte), &cc1, getTaille(carte))->stockCourrantDechet[0] = 50;
    findByCoordListLDP(getListeLigneDeProduction(carte), &cc2, getTaille(carte))->stockCourrantDechet[0] = 3;
    findByCoordListLDP(getListeLigneDeProduction(carte), &cc3, getTaille(carte))->stockCourrantDechet[0] = 0;
    findByCoordListLDP(getListeLigneDeProduction(carte), &cc3, getTaille(carte))->stockCourrantDechet[1] = 145;
    findByCoordListLDP(getListeLigneDeProduction(carte), &cc4, getTaille(carte))->stockCourrantDechet[0] = 46;
    findByCoordListLDP(getListeLigneDeProduction(carte), &cc5, getTaille(carte))->stockCourrantDechet[0] = 2;
    findByCoordListLDP(getListeLigneDeProduction(carte), &cc6, getTaille(carte))->stockCourrantDechet[0] = 32;
    findByCoordListLDP(getListeLigneDeProduction(carte), &cc7, getTaille(carte))->stockCourrantDechet[0] = 13;
    */carte->nbDechetPortail = 22;

    //Incrémentation nbTour
    (*carte).nbTours++;
  }
}
