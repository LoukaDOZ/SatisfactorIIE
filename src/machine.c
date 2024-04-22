#include "../headers/machine.h"
#include <stdlib.h>

struct s_infos_machines infos_machines = {.nom = {"Collecteur", "Tapis", "Croix", "Centre de recyclage", "Déchetterie"},
                                          .e_construction = {200, 60, 160, 500, 100},
                                          .dd_construction = {20, 20, 20, 40, 100},
                                          .e_amelioration = {500, 0, 0, 1500, 200},
                                          .dd_amelioration = {100, 0, 0, 100, 600},
                                          .e_destruction = {60, 60, 60, 100, 100},
                                          .dd_destruction = {200, 200, 200, 500, 200},
                                          .stock_initial = {1, 0, 0, 100, 50},
                                          .stock_amelioration = {1, 0, 0, 10, 20},
                                          .effet = {"Un collecteur est une machine qui doit être placée sur une case adjacente à une source ou à une porte. Le collecteur envoie les ressources produites par la source sur la sortie indiquée.", "Un tapis roulant permet de transporter les ressources/déchets en ligne droite. Il possède 1 entrée et 1 sortie.", "Une croix est un ensemble de deux tapis roulant juxtaposés, permettant de croiser deux lignes de tapis roulants. Elle possède 2 entrées et 2 sorties.", "Le centre de recyclage permet de transformer les déchets en ressources. Il centre possède 3 entrées, 1 sortie et peut initialement stocker jusqu'à 100 déchets.", "La déchetterie permet de stocker des déchets. Elle possède 4 entrées, 0 sortie et peut initialement stocker jusqu'à 50 déchets."}};

/********** Type machine **********/

typeMachine getTypeMachine(machine* machine){
  return machine->type_machine;
}

void setTypeMachine(machine* machine, typeMachine type){
  machine->type_machine = type;
}

/********** Point d'entrées et de sorties **********/

void getEntreeMachine(machine* machine,pointCard** entree, int* nb_entree){
  *entree = machine->entree;
  *nb_entree = machine->nb_entree;
}

void setEntreeMachine(machine* machine,pointCard* entree, int nb_entree){
  machine->entree = entree;
  machine->nb_entree = nb_entree;
}

void getSortieMachine(machine* machine,pointCard** sortie, int* nb_sortie){
  *sortie = machine->sortie;
  *nb_sortie = machine->nb_sortie;
}

void setSortieMachine(machine* machine,pointCard* sortie, int nb_sortie){
  machine->sortie = sortie;
  machine->nb_sortie = nb_sortie;
}

/********** Stock initial **********/

int getStockInit(machine* machine){
  return machine->stock_init;
}

void setStockInit(machine* machine, int val){
  machine->stock_init = val;
}

/********** Stock amélioration **********/

int getStockUp(machine* machine){
  return machine->stock_upgrade;
}

void setStockUp(machine* machine, int val){
  machine->stock_upgrade = val;
}

/********** Cout Construction **********/

           /******* E *******/

int getCoutConstructionE(machine* machine){
  return getCoutE(machine->cout_construction);
}

int setCoutConstructionE(machine* machine, int val){
  return setCoutE(machine->cout_construction, val);
}

int updateCoutConstructionE(machine* machine, int val, int min){
  return updateCoutE(machine->cout_construction, val, min);
}

           /******* DD *******/

int getCoutConstructionDD(machine* machine){
  return getCoutDD(machine->cout_construction);
}

int setCoutConstructionDD(machine* machine, int val){
  return setCoutDD(machine->cout_construction, val);
}

int updateCoutConstructionDD(machine* machine, int val, int min){
  return updateCoutDD(machine->cout_construction, val, min);
}
            /******* Tout *******/

void setCoutConstruction(machine* machine, int  coutE, int coutDD){
  setCoutConstructionE(machine, coutE);
  setCoutConstructionDD(machine, coutDD);
}

cout getCoutConstruction(machine* machine){
  cout ret;
  setCoutE(&ret,getCoutConstructionE(machine));
  setCoutDD(&ret,getCoutConstructionDD(machine));
  return ret;
}

/********** Cout Amélioration **********/

           /******* E *******/

int getCoutAmeliorationE(machine* machine){
  return getCoutE(machine->cout_amelioration);
}

int setCoutAmeliorationE(machine* machine, int val){
  return setCoutE(machine->cout_amelioration, val);
}

int updateCoutAmeliorationE(machine* machine, int val, int min){
  return updateCoutE(machine->cout_amelioration, val, min);
}

           /******* DD *******/

int getCoutAmeliorationDD(machine* machine){
  return getCoutDD(machine->cout_amelioration);
}

int setCoutAmeliorationDD(machine* machine, int val){
  return setCoutDD(machine->cout_amelioration, val);
}

int updateCoutAmeliorationDD(machine* machine, int val, int min){
  return updateCoutDD(machine->cout_amelioration, val, min);
}

          /******* Tout *******/

void setCoutAmelioration(machine* machine, int  coutE, int coutDD){
  setCoutAmeliorationE(machine, coutE);
  setCoutAmeliorationDD(machine, coutDD);
}

cout getCoutAmelioration(machine* machine){
  cout ret;
  setCoutE(&ret,getCoutAmeliorationE(machine));
  setCoutDD(&ret,getCoutAmeliorationDD(machine));
  return ret;
}

/********** Cout Desctruction **********/

           /******* E *******/

int getCoutDestructionE(machine* machine){
  return getCoutE(machine->cout_destruction);
}

int setCoutDestructionE(machine* machine, int val){
  return setCoutE(machine->cout_destruction, val);
}

int updateCoutDestructionE(machine* machine, int val, int min){
  return updateCoutE(machine->cout_destruction, val, min);
}

           /******* DD *******/

int getCoutDestructionDD(machine* machine){
  return getCoutDD(machine->cout_destruction);
}

int setCoutDestructionDD(machine* machine, int val){
  return setCoutDD(machine->cout_destruction, val);
}

int updateCoutDestructionDD(machine* machine, int val, int min){
  return updateCoutDD(machine->cout_destruction, val, min);
}

          /******* Tout *******/

void setCoutDestruction(machine* machine, int  coutE, int coutDD){
  setCoutDestructionE(machine, coutE);
  setCoutDestructionDD(machine, coutDD);
}

cout getCoutDestruction(machine* machine){
  cout ret;
  setCoutE(&ret,getCoutDestructionE(machine));
  setCoutDD(&ret,getCoutDestructionDD(machine));
  return ret;
}

/********** Description **********/

char* getDescMachine(machine* machine){
  return machine->description;
}

void setDescMachine(machine* machine, char* desc){
  machine->description = desc;
}


/********** Fonction Header **********/

void init_machines(machine*** liste_machines, int* taille_liste_machines) {
  /* Collecteur */
  machine* collecteur = (machine*) malloc(sizeof(machine));
  setTypeMachine(collecteur,COLLECTEUR);
  collecteur->cout_construction = (cout*) malloc(sizeof(cout));
  setCoutConstruction(collecteur, infos_machines.e_construction[0], infos_machines.dd_construction[0]);
  collecteur->cout_amelioration = (cout*) malloc(sizeof(cout));
  setCoutAmelioration(collecteur, infos_machines.e_amelioration[0], infos_machines.dd_amelioration[0]);
  collecteur->cout_destruction = (cout*) malloc(sizeof(cout));
  setCoutDestruction(collecteur, infos_machines.e_destruction[0], infos_machines.dd_destruction[0]);
  setStockInit(collecteur, infos_machines.stock_initial[0]);
  int nb_entree = 0;
  pointCard* entree = (pointCard*) malloc (nb_entree*sizeof(pointCard));
  setEntreeMachine(collecteur, entree, nb_entree);
  int nb_sortie = 1;
  pointCard* sortie = (pointCard*) malloc (nb_sortie*sizeof(pointCard));
  sortie[0] = NORD;
  setSortieMachine(collecteur, sortie, nb_sortie);
  setStockUp(collecteur, infos_machines.stock_amelioration[0]);
  setDescMachine(collecteur, infos_machines.effet[0]);
  
  /* Tapis */
  machine* tapis = (machine*) malloc(sizeof(machine));
  setTypeMachine(tapis,TAPIS);
  tapis->cout_construction = (cout*) malloc(sizeof(cout));
  setCoutConstruction(tapis, infos_machines.e_construction[1], infos_machines.dd_construction[1]);
  tapis->cout_amelioration = (cout*) malloc(sizeof(cout));
  setCoutAmelioration(tapis, infos_machines.e_amelioration[1], infos_machines.dd_amelioration[1]);
  tapis->cout_destruction = (cout*) malloc(sizeof(cout));
  setCoutDestruction(tapis, infos_machines.e_destruction[1], infos_machines.dd_destruction[1]);
  setStockInit(tapis, infos_machines.stock_initial[1]);
  nb_entree = 3;
  entree = (pointCard*) malloc (nb_entree*sizeof(pointCard));
  entree[0] = EST;
  entree[1] = SUD;
  entree[2] = OUEST;
  setEntreeMachine(tapis, entree, nb_entree);
  nb_sortie = 1;
  entree = (pointCard*) malloc (nb_sortie*sizeof(pointCard));
  sortie[0] = NORD;
  setSortieMachine(tapis, sortie, nb_sortie);
  setStockUp(tapis, infos_machines.stock_amelioration[1]);
  setDescMachine(tapis, infos_machines.effet[1]);
  
  /* Croix */
  machine* croix = (machine*) malloc(sizeof(machine));
  setTypeMachine(croix,CROIX);
  croix->cout_construction = (cout*) malloc(sizeof(cout));
  setCoutConstruction(croix, infos_machines.e_construction[2], infos_machines.dd_construction[2]);
  croix->cout_amelioration = (cout*) malloc(sizeof(cout));
  setCoutAmelioration(croix, infos_machines.e_amelioration[2], infos_machines.dd_amelioration[2]);
  croix->cout_destruction = (cout*) malloc(sizeof(cout));
  setCoutDestruction(croix, infos_machines.e_destruction[2], infos_machines.dd_destruction[2]);
  setStockInit(croix, infos_machines.stock_initial[2]);
  nb_entree = 2;
  entree = (pointCard*) malloc (nb_entree*sizeof(pointCard));
  entree[0] = SUD;
  entree[1] = EST;
  setEntreeMachine(croix, entree, nb_entree);
  nb_sortie = 2;
  entree = (pointCard*) malloc (nb_sortie*sizeof(pointCard));
  sortie[0] = NORD;
  sortie[1] = OUEST;
  setSortieMachine(croix, sortie, nb_sortie);
  setStockUp(croix, infos_machines.stock_amelioration[2]);
  setDescMachine(croix, infos_machines.effet[2]);
  
  /* Centre de recyclage */
  machine* recyclage = (machine*) malloc(sizeof(machine));
  setTypeMachine(recyclage,RECYCLAGE);
  recyclage->cout_construction = (cout*) malloc(sizeof(cout));
  setCoutConstruction(recyclage, infos_machines.e_construction[3], infos_machines.dd_construction[3]);
  recyclage->cout_amelioration = (cout*) malloc(sizeof(cout));
  setCoutAmelioration(recyclage, infos_machines.e_amelioration[3], infos_machines.dd_amelioration[3]);
  recyclage->cout_destruction = (cout*) malloc(sizeof(cout));
  setCoutDestruction(recyclage, infos_machines.e_destruction[3], infos_machines.dd_destruction[3]);
  setStockInit(recyclage, infos_machines.stock_initial[3]);
  nb_entree = 3;
  entree = (pointCard*) malloc (nb_entree*sizeof(pointCard));
  entree[0] = EST;
  entree[1] = SUD;
  entree[2] = OUEST;
  setEntreeMachine(recyclage, entree, nb_entree);
  nb_sortie = 1;
  entree = (pointCard*) malloc (nb_sortie*sizeof(pointCard));
  sortie[0] = NORD;
  setSortieMachine(recyclage, sortie, nb_sortie);
  setStockUp(recyclage, infos_machines.stock_amelioration[3]);
  setDescMachine(recyclage, infos_machines.effet[3]);
  
  /* DÃ©chetterie */
  machine* dechetterie = (machine*) malloc(sizeof(machine));
  setTypeMachine(dechetterie,DECHETTERIE);
  dechetterie->cout_construction = (cout*) malloc(sizeof(cout));
  setCoutConstruction(dechetterie, infos_machines.e_construction[4], infos_machines.dd_construction[4]);
  dechetterie->cout_amelioration = (cout*) malloc(sizeof(cout));
  setCoutAmelioration(dechetterie, infos_machines.e_amelioration[4], infos_machines.dd_amelioration[4]);
  dechetterie->cout_destruction = (cout*) malloc(sizeof(cout));
  setCoutDestruction(dechetterie, infos_machines.e_destruction[4], infos_machines.dd_destruction[4]);
  setStockInit(dechetterie, infos_machines.stock_initial[4]);
  nb_entree = 4;
  entree = (pointCard*) malloc (nb_entree*sizeof(pointCard));
  entree[0] = NORD;
  entree[1] = EST;
  entree[2] = SUD;
  entree[3] = OUEST;
  setEntreeMachine(dechetterie, entree, nb_entree);
  nb_sortie = 0;
  entree = (pointCard*) malloc (nb_sortie*sizeof(pointCard));
  setSortieMachine(dechetterie, sortie, nb_sortie);
  setStockUp(dechetterie, infos_machines.stock_amelioration[4]);
  setDescMachine(dechetterie, infos_machines.effet[4]);

  *taille_liste_machines = NOMBRE_MACHINES;
  *liste_machines = (machine**) malloc(*taille_liste_machines*sizeof(machine*));
  (*liste_machines)[0] = collecteur;
  (*liste_machines)[1] = tapis;
  (*liste_machines)[2] = croix;
  (*liste_machines)[3] = recyclage;
  (*liste_machines)[4] = dechetterie;
}
