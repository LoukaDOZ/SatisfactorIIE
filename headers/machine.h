#ifndef MACHINE_H
#define MACHINE_H

#include "variablesGlobales.h"
#include "cout.h"

typedef enum pointCard pointCard;
typedef enum typeMachine typeMachine;
typedef struct machine machine;

/**
 * Une énumération permettant d'identifier le type de machine
 *
 */
enum typeMachine
{
    COLLECTEUR,
    TAPIS,
    CROIX,
    RECYCLAGE,
    DECHETTERIE
};

/**
 * Une énumération permettant d'identifier les différents entrées sorties
 *
 */
enum pointCard
{
    NORD,
    EST,
    SUD,
    OUEST
};

/**
 * Structure machine
 *
 * @attr {typeMachine} type_machine - Un type pour identifier le type de machine
 * @attr {pointCard*} entree - Liste des entrées de la machine
 * @attr {int} nb_entree - Nombre d'entrée de la machine
 * @attr {pointCard*} sortie - Liste des sorties de la machine
 * @attr {int} nb_sortie - Nombre de sortie de la machine
 * @attr {int} stock_init - Valeur du stock initial (niveau 1) pour une machine
 * @attr {int} stock_upgrade - Valeur du stock qui augmente à chaque amélioration pour une machine
 * @attr {char*} description - Description de la machine
 * @attr {cout*} cout_construction - Représente les couts (en DD et E) de construction
 * @attr {cout*} cout_amelioration - Représente les couts (en DD et E) d'amélioration
 * @attr {cout*} cout_destruction - Représente les couts (en DD et E) de destruction
 *
 */
struct machine{
  typeMachine type_machine;
  pointCard* entree;
  int nb_entree;
  pointCard* sortie;
  int nb_sortie;
  int stock_init;
  int stock_upgrade;
  char* description;
  cout* cout_construction;
  cout* cout_amelioration;
  cout* cout_destruction;
};

/********** Type machine **********/

/**
 * Renvois le type de machine du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le type
 * @return {typeMachine} - Type de la machine
 */
typeMachine getTypeMachine(machine* machine);

/**
 * Permet de mettre à jour la valeur type_machine du @param {machine}
 *
 * @param {machine} - Machine dont on veut mettre à jour le type
 * @param {typeMachine} - Nouveau type
 */
void setTypeMachine(machine* machine, typeMachine type);

/********** Point d'entrées et de sorties **********/

/**
 * Permet de récupérer les entrees de @param {machine}
 *
 * @param {machine} - Machine dont on veut récupérer les entrées
 * @param {entree} - Entrées
 * @param {nb_entree} - Nombre d'entrée
 */
void getEntreeMachine(machine* machine,pointCard** entree, int* nb_entree);

/**
 * Permet de mettre à jour les entrees de @param {machine}
 *
 * @param {machine} - Machine dont on veut mettre à jour les entrees
 * @param {entree} - Nouvelle entrée
 * @param {nb_entree} - Nouveaux nombre d'entrée
 */
void setEntreeMachine(machine* machine,pointCard* entree, int nb_entree);

/**
 * Permet de récupérer les sorties de @param {machine}
 *
 * @param {machine} - Machine dont on veut récupérer les sorties
 * @param {entree} - Sorties
 * @param {nb_entree} - Nombre de sortie
 */
void getSortieMachine(machine* machine,pointCard** sortie, int* nb_sortie);

/**
 * Permet de mettre à jour les sorties de @param {machine}
 *
 * @param {machine} - Machine dont on veut mettre à jour les sorties
 * @param {entree} - Nouvelle sorties
 * @param {nb_entree} - Nouveaux nombre de sorties
 */
void setSortieMachine(machine* machine,pointCard* sortie, int nb_sortie);

/********** Stock initial **********/

/**
 * Renvois le stock initial de la machine @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le stock
 * @return {int} - Stock de la machine
 */
int getStockInit(machine* machine);

/**
 * Permet de mettre à jour la valeur stock_init du @param {machine}
 *
 * @param {machine} - Machine dont on veut mettre à jour le stock initial
 * @param {typeMachine} - Nouveau stock
 */
void setStockInit(machine* machine, int val);

/********** Stock amélioration **********/

/**
 * Renvois le stock d'amélioration de la machine @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le stock
 * @return {int} - Stock de la machine
 */
int getStockUp(machine* machine);

/**
 * Permet de mettre à jour la valeur stock_upgrade du @param {machine}
 *
 * @param {machine} - Machine dont on veut mettre à jour le stock d'amélioration
 * @param {typeMachine} - Nouveau stock
 */
void setStockUp(machine* machine, int val);

/********** Cout Construction **********/

           /******* E *******/

/**
 * Renvois le cout de contruction en E du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout de construction
 * @return {int} - cout de contruction en E
 */
int getCoutConstructionE(machine* machine);

/**
 * Permet de mettre à jour le cout de contruction en E de @param {machine} avec une valeur @param {val}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur fixé
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int setCoutConstructionE(machine* machine, int val);

/**
 * Permet de mettre à jour le cout de contruction en E de @param {machine} en ajoutant une valeur à la valeur par défaut, si le minimum @param {min} est dépassé, la valeur en E vaut @param {min}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur qu'on va ajouter
 * @param {min} - Valeur minimale du nouveau cout
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutConstructionE(machine* machine, int val, int min);

           /******* DD *******/

/**
 * Renvois le cout de contruction en DD du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout de construction
 * @return {int} - cout de contruction en DD
 */
int getCoutConstructionDD(machine* machine);

/**
 * Permet de mettre à jour le cout de contruction en DD de @param {machine} avec une valeur @param {val}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur fixé
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int setCoutConstructionDD(machine* machine, int val);

/**
 * Permet de mettre à jour le cout de contruction en DD de @param {machine} en ajoutant une valeur à la valeur par défaut, si le minimum @param {min} est dépassé, la valeur en DD vaut @param {min}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur qu'on va ajouter
 * @param {min} - Valeur minimale du nouveau cout
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutConstructionDD(machine* machine, int val, int min);

            /******* Tout *******/

/**
 * Permet de mettre à jour le cout de contruction du @param {machine}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {coutE} - Nouvelle valeur en E
 * @param {coutDD} - Nouvelle valeur en DD
 */
void setCoutConstruction(machine* machine, int  coutE, int coutDD);

/**
 * Renvois le cout de construction du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout de construction
 * @return {cout} - cout de construction
 */
cout getCoutConstruction(machine* machine);

/********** Cout Amélioration **********/

           /******* E *******/

/**
 * Renvois le cout d'amélioration en E du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout de construction
 * @return {int} - cout d'amélioration en E
 */
int getCoutAmeliorationE(machine* machine);

/**
 * Permet de mettre à jour le cout d'amélioration en E de @param {machine} avec une valeur @param {val}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur fixé
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int setCoutAmeliorationE(machine* machine, int val);

/**
 * Permet de mettre à jour le cout d'amélioration en E de @param {machine} en ajoutant une valeur à la valeur par défaut, si le minimum @param {min} est dépassé, la valeur en E vaut @param {min}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur qu'on va ajouter
 * @param {min} - Valeur minimale du nouveau cout
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutAmeliorationE(machine* machine, int val, int min);

           /******* DD *******/

/**
 * Renvois le cout d'amélioration en DD du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout de construction
 * @return {int} - cout d'amélioration en DD
 */
int getCoutAmeliorationDD(machine* machine);

/**
 * Permet de mettre à jour le cout d'amélioration en DD de @param {machine} avec une valeur @param {val}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur fixé
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int setCoutAmeliorationDD(machine* machine, int val);

/**
 * Permet de mettre à jour le cout d'amélioration en DD de @param {machine} en ajoutant une valeur à la valeur par défaut, si le minimum @param {min} est dépassé, la valeur en DD vaut @param {min}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur qu'on va ajouter
 * @param {min} - Valeur minimale du nouveau cout
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutAmeliorationDD(machine* machine, int val, int min);

          /******* Tout *******/

/**
 * Permet de mettre à jour le cout d'amélioration du @param {machine}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {coutE} - Nouvelle valeur en E
 * @param {coutDD} - Nouvelle valeur en DD
 */
void setCoutAmelioration(machine* machine, int  coutE, int coutDD);

/**
 * Renvois le cout d'amélioration du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout d'amélioration
 * @return {cout} - cout d'amélioration
 */
cout getCoutAmelioration(machine* machine);

/********** Cout Desctruction **********/

           /******* E *******/

/**
 * Renvois le cout de destruction en E du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout de construction
 * @return {int} - cout de destruction en E
 */
int getCoutDestructionE(machine* machine);

/**
 * Permet de mettre à jour le cout de destruction en E de @param {machine} avec une valeur @param {val}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur fixé
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int setCoutDestructionE(machine* machine, int val);

/**
 * Permet de mettre à jour le cout de destruction en E de @param {machine} en ajoutant une valeur à la valeur par défaut, si le minimum @param {min} est dépassé, la valeur en E vaut @param {min}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur qu'on va ajouter
 * @param {min} - Valeur minimale du nouveau cout
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutDestructionE(machine* machine, int val, int min);

           /******* DD *******/

/**
 * Renvois le cout de destruction en DD du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout de construction
 * @return {int} - cout de destruction en DD
 */
int getCoutDestructionDD(machine* machine);

/**
 * Permet de mettre à jour le cout de destruction en DD de @param {machine} avec une valeur @param {val}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur fixé
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int setCoutDestructionDD(machine* machine, int val);

/**
 * Permet de mettre à jour le cout de destruction en DD de @param {machine} en ajoutant une valeur à la valeur par défaut, si le minimum @param {min} est dépassé, la valeur en DD vaut @param {min}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {val} - Valeur qu'on va ajouter
 * @param {min} - Valeur minimale du nouveau cout
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutDestructionDD(machine* machine, int val, int min);

          /******* Tout *******/

/**
 * Permet de mettre à jour le cout de destruction du @param {machine}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {coutE} - Nouvelle valeur en E
 * @param {coutDD} - Nouvelle valeur en DD
 */
void setCoutDestruction(machine* machine, int  coutE, int coutDD);

/**
 * Renvois le cout de destruction du @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre le cout de destruction
 * @return {cout} - cout de destruction
 */
cout getCoutDestruction(machine* machine);

/********** Description **********/

/**
 * Renvois la description de la machine @param {machine}
 *
 * @param {machine} - Machine dont on veut connaitre la description
 * @return {char*} - Description
 */
char* getDescMachine(machine* machine);

/**
 * Permet de mettre à jour la description du @param {machine}
 *
 * @param {machine} - Machine sur laquelle on va effectuer la MAJ
 * @param {coutE} - Nouvelle description
 *
 */
void setDescMachine(machine* machine, char* desc);

/********** Fonction main **********/

/**
 * Cette fonction permet d'ajouter à une liste passé en paramêtre, l'ensemble des machines disponible dans le jeux.
 * Le second argument récupère la taille de cette liste
 *
 * @param {liste_machines} - Une liste de machine (initialement vide)
 * @param {taille_liste_machines} - taille de la liste @attr {liste_machines}
 *
 */
void init_machines(machine*** liste_machines, int* taille_liste_machines);

#endif
