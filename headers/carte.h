#ifndef CARTE_H
#define CARTE_H

#include "machine.h"
#include "cout.h"
#include "ligneDeProduction.h"
#include "structure.h"
#include "coordonne.h"
#include "variablesGlobales.h"
#include "personnel.h"

typedef struct carte carte;
typedef struct etudiant etudiant;
typedef struct source source;
typedef struct cellule cellule;
typedef struct fisa fisa;
typedef struct fise fise;

typedef enum typeCase typeCase;
typedef enum typeRessource typeRessource;

/**
 * Enum représentant les différents type d'une case
 *
 */
enum typeCase
{
    LIGNEDEPROD,
    SOURCE,
    VIDE,
    PORTE
};

enum typeRessource{
    DD,
    E
};

/**
 * Cette structure représente une Case avec les coordonées x et y,
 * une ligne de production et le type de la case
 *
 * @attr {ligneDeProduction} ligneDeProduction - un attribut de type ligneDeProduction
 * @attr {typeCase} typeCase - un attribut de type typeCase
 */
struct cellule
{
    ligneDeProduction* ligneDeProduction;
    typeCase typeCase;
};

/**
 * Cette structure représente une carte contenant le type de la carte,
 * la taille de la crate, une cellule, le nombre de ressource, le nombre de déchet,
 * nombre d'étudiant FISA et FISE, le nombre de tours et un étudiant
 *
 * @attr {listeLigneDeProduction} cellule - un attribut de type cellule
 * @attr {int} taille - un attribut de type int
 * @attr {int} nbRessourcePortail - un attribut de type int
 * @attr {int} nbDechetPortail - un attribut de type int
 * @attr {int} nbFISA - un attribut de type int
 * @attr {int} nbFISE - un attribut de type int
 * @attr {int} nbTours - un attribut de type int
 * @attr {int} freqSource - un attirbut de type int
 * @attr {coord} coord - un attribut de type coord
 * @attr {typeRessource} typeRessourceFISA - un attribut de type typeRessource
 * @attr {cout} ressourceJoueur - un attribut de type cout
 * @attr {listePersonnel} listePersonnel - un attribut de type personnel
 * @attr {fisa} fisa - un attribut de type fisa
 * @attr {fise} fise - un attribut de type fise
 * @attr {int} nbPersonnel - un attribut de type carte
 * @attr {coord} coordPorte - un attribut de type carte
 * @attr {coord} coordSources[NB_SOURCES_PLATEAU] - un attribu de type coord
 * @attr {int} nbRessource - un attribut de type int
 * @attr {int} nbCroix - un attribut de type int
 * @attr {int} nbTapisRoulant - un attribut de type int
 * @attr {int} nbDecheterie - un attribut de type int
 * @attr {int} nbDechet - un attribut de type int
 * @attr {int} nbRecycleur - un attribut de type int
 * @attr {int} nbCollecteur - un attribut de type int
*/
struct carte
{
    listeLigneDeProduction* listeLigneDeProduction;
    int taille;
    int nbRessourcePortail;
    int nbDechetPortail;
    int* nbRessourceSource;
    int nbFISA;
    int nbFISE;
    int nbTours;
    int freqSource;
    coord coord;
    typeRessource typeRessourceFISA;
    cout* ressourceJoueur;
    listePersonnel* listePersonnel;
    fisa* fisa;
    fise* fise;
    int nbPersonnel;
    coord *coordPorte;
    coord **coordSources;
    int nbRessource;
    int nbCroix;
    int nbTapisRoulant;
    int nbDecheterie;
    int nbDechet;
    int nbRecycleur;
    int nbCollecteur;
};

/**
 * Cette structure represente un fisa avec son cout et sa production
 * @attr {cout} cout
 * @attr {cout} production
 * 
 */
struct fisa {
    cout *cout;
    cout *production;
};

/**
 * Cette structure represente un fise avec son cout et sa production
 * @attr {cout} cout
 * @attr {cout} productions
 */
struct fise {
    cout *cout;
    cout *production;
};
/**
 * Retourne true si coord est une des coordonnés du portail ou d'une source
 * @param {carte} carte - la carte
 * @param {coord} coord - la coordonnée qu'on veut vérifier
 * @return {int}
 */
int notSourceOuPortail(carte* carte,coord* coord);
/**
 * Cette fonction permet d'ajouter val dechet a la porte
 * @param {carte} carte - un parametre de type carte
 * @param {int} val - un parametre de type int
 * */
void ajouterDechetPortail(carte* carte,int val);
/**
 * Cette fonction renvoit le nombre de Ressource de la carte
 * @param {carte} carte - un parametre de type carte
 * @return {int}
 * */
int getNbRessource(carte* carte);

/**
 * Cette fonction attribue nb ressource au NbRessource de la carte
 * @param {carte} carte - un parametre de type carte
 * @param {int} nb - un paramètre de type int
 * */
void setNbRessource(carte* carte,int nb);
/**
 * Cette fonction renvoit le nombre de Croix sur la carte
 * @param {carte} carte - un parametre de type carte
 * @return {int} 
 * */
int getNbCroix(carte* carte);
/**
 * Cette fonction attribue nb croix au NbCroix de la carte
 * @param {carte} carte - un parametre de type carte
 * @param {int} nb - un paramètre de type int
 * */
void setNbCroix(carte* carte,int nb);
/**
 * Cette fonction renvoit le nombre de Tapis Roulant de la carte
 * @param {carte} carte - un parametre de type carte
 * @return {int}
 * */
int getNbTapisRoulant(carte* carte);
/**
 * Cette fonction attribue nb tapis roulant au nbTapisRoulant de la carte
 * @param {carte} carte - un parametre de type carte
 * @param {int} nb - un paramètre de type int
 * */
void setNbTapisRoulant(carte* carte,int nb);
/**
 * Cette fonction renvoit le nombre de dechetteries de la carte
 * @param {carte} carte - un parametre de type carte
 * @return {int}
 * */
int getNbDechetterie(carte* carte);
/**
 * Cette fonction attribue nb deche au NbRessource de la carte
 * @param {carte} carte - un parametre de type carte
 * @param {int} nb - un paramètre de type int
 * */
void setNbDechetterie(carte* carte,int nb);
/**
 * Cette fonction renvoit nb dechet de la carte
 * @param {carte} carte - un parametre de type carte
 * @return {int}
 * */
int nbDechet(carte* carte);
/**
 * Cette fonction attribue nb dechet au NbDechet de la carte
 * @param {carte} carte - un parametre de type carte
 * @param {int} nb - un paramètre de type int
 * */
void setNbDechet(carte* carte,int nb);
/**
 * Cette fonction renvoit nb recycleur de la carte
 * @param {carte} carte - un parametre de type carte
 * @return {int}
 * */
int nbRecycleur(carte* carte);
/**
 * Cette fonction attribue nb recycleur au NbRecycleur de la carte
 * @param {carte} carte - un parametre de type carte
 * @param {int} nb - un paramètre de type int
 * */
void setNbRecycleur(carte* carte,int nb);
/**
 * Cette fonction renvoit nb collecteur au NbCollecteur de la carte
 * @param {carte} carte - un parametre de type carte
 * @return {int}
 * */
int nbCollecteur(carte* carte);
/**
 * Cette fonction attribue nb collecteur au NbCollecteur de la carte
 * @param {carte} carte - un parametre de type carte
 * @param {int} nb - un paramètre de type int
 * */
void setNbCollecteur(carte* carte,int nb);
/**
 * Cette fonction active l'effet d'un personnel
 * @param {personnel} perso - un parametre de type personnel
 * @param {carte} plateau - un parametre de type carte
 * @param {machine} listeMachineDispo - un parametre de type machine
 * @param {int} nbMachine - un parametre de type int
 * @param {personnel} listePersoDispo - un parametre de type personnel
 * @param {int} nbPerso - un paramètre de type int
 * @param {fisa} infoFISA - un parametre de type fisa
 * @param {fise} infoFISE - un parametre de type fise
 * */
void activeEffetPersonnel
(
    personnel* perso, 
    carte* plateau, machine** listeMachineDispo, 
    int nbMachine, personnel** listePersoDispo, 
    int nbPerso, 
    fisa* infoFISA, 
    fise* infoFISE
);

/**
 * Cette fonction renvoit les coordonnees de la porte
 * @param {carte} plateau - un parametre de type carte
 * @param {coord}
 * */
coord* getCoordPorte(carte* plateau);

/**
 * Cette fonction renvoit les coordonnees d'une source
 * @param {carte} plateau - un parametre de type plateau
 * @param {int} i - un paramètre de type int
 * @return {coord}
 * */
coord* getCoordSource(carte* plateau, int i);

/**
 * Cette fonction retourne une liste de coordonnees des sources
 * @param {carte} plateau - un parametre de type carte
 * @return {coord}
 * */
coord** getCoordSources(carte* plateau);

/**
 * Cette fonction attribue une coordonnee x et y a la porte
 * @param {carte} olateau - un parametre de type carte
 * @param {int} x - un parametre de type int
 * @param {int} y - un parametre de type int
 * */
void setCoordPorte(carte* plateau, int x, int y);

/**
 * Cette fonction attribue une coordonnnee x et y a la i-ème porte
 * @param {carte} plateau - un parametre de type carte
 * @param {int} i - un paramètre de type int
 * @param {int} x - un parametre de type int
 * @param {int} y - un parametre de type int
 * */
void setCoordSource(carte* plateau, int i, int x, int y);

/**
 * Enlève un n ième des FISE et des FISA et envoie une ressource à la porte pour chaque élève enlevé.
 * @param {carte} carte - un parametre de type carte
 * @param {int} n - un parametre de type int
 * */
void diplomerEleve(carte* carte,int n);

/**
 * Incrémente la production des FISE de nbDD en DD et de nbE en E
 * @param {fise} infoFISE
 * @param {int} nbDD
 * @param {int} nbE
 * */
void updateProductionFise(fise* infoFISE, int nbDD, int nbE);

/**
 * Incrémente la production des FISA de nbDD en DD et de nbE en E
 * @param {fisa} infoFISA
 * @param {int} nbDD
 * @param {int} nbE
 * */
void updateProductionFisa(fisa* infoFISA, int nbDD, int nbE);

/**
 * Cette fonction divise nb dechet pour chaque case
 * @param {carte} carte - un parametre de type carte
 * @param {int} nb - un parametre de type int
 * 
 * */
void enleveDechet(carte* carte, int nb);

/**
 *  Cette fonction renvoit le nombre de ressource d'une source
 * @param {carte} carte -un parametre de type carte
 * @return {int}
 * */
int* getNbRessourceSource(carte* carte);
/**
 *  Cette fonction libère la memoire
 * @param {fisa} fisa - un parametre de type fisa
 * */
void libererMemoireFISA(fisa* fisa);
/**
 *  Cette fonction libère la memoire
 * @param {fise} fise - un parametre de type fisa
 * */
void libererMemoireFISE(fise* fise);
/**
 *  Cette fonction initialise le coût d'un fisa et un fise
 * @param {fisa} fisa - un parametre de type fisa
 * @param {fise} fise - un parametre de type fise
 * */
void initAchatFISAFISE(fisa* fisa,fise* fise);
/**
 *  Cette fonction initialise la production d'un fisa et un fise
 * @param {fisa} fisa - un parametre de type fisa
 * @param {fise} fise - un parametre de type fise
 * */
void initProductionFISAFISE(fisa* fisa,fise* fise);
/**
 *  Cette fonction recycle un dechet diminue le nbDechetPortail par nbRecycle
 * @param {carte} carte - un parametre de type carte
 * @param {int} nbRecycle - un parametre de type int
 * 
 * */
void dechetRecycle(carte* carte,int nbRecycle);
/**
 *  Cette fonction active l'effet du collecteur lorsqu'il reçoit une ressource
 * @param {carte} carte - un parametre de type carte
 * */
void effetCollecteurRessource(carte* carte);

/**
 *  Cette fonction active l'effet du collecteur lorsqu'il reçoit un dechet
 * @param {carte} carte - un parametre de type carte
 * */
void effetCollecteurDechet(carte* carte);

/**
 *  Cette fonction modifie la frequence de creation de ressource d'une source
 * @param {carte} carte - un parametre de type carte
 * @param {int} freq - un parametre de type int
 * */
void modifierFrequenceProductionSource(carte* carte,int freq);

/**
 *  Cette fonction renvoit la frequence de creation de ressource d'une source
 * @param {carte} carte - un parametre de type carte
 * @return {int}
 * */
int getFrequenceProductionSource(carte* carte);
/**
 *  Cette fonction active l'effet de la source pour produire 3 ressources
 * @param {carte} carte - un parametre de type carte
 * */
void incrRessourceSource(carte* carte);

/**
 * Cette fonction retourne une coordonne
 * @param {carte} carte - un parametre de type carte
 * @return {coord}
 * 
 * 
 * */
coord getCoordonne(carte* carte);

/**
 * Cette fonction retourne une liste de ligne de production
 * @param {carte} carte - un paramètre de type carte
 * @return {listeLigneDeProduction}
 * 
 * */
listeLigneDeProduction* getListeLigneDeProduction(carte* carte);
/**
 * Cette fonction retourne le nombre de tour
 * @param {carte} carte - un paramètre de type carte
 * @return {int}
 */
int getNbTours(carte* carte);


/**
 * Cette fonction retourne le nombre de FISE
 * @param {carte} carte - un paramètre de type carte
 * @return {int}
 */
int getFISE(carte*carte);


/**
 * Cette fonction retourne le nombre de FISA
 * @param {carte} carte - un paramètre de type carte
 * @return {int}
 */
int getFISA(carte* carte);

fisa* getInfoFisa(carte* carte);
fise* getInfoFise(carte* carte);

/**
 * Cette fonction retourne la taille de la carte
 * @param {carte} carte - un paramètre de type carte
 * @return {int}
*/
int getTaille(carte* carte);


/**
 * Cette fonction retourne le nombre de dechet
 * @param {carte} carte - un paramètre de type carte
 * @return {int}
 */
int getNbDechetPortail(carte* carte);

/**
 * Cette fonction attribue dechet au nbDechetPortail de la carte
 * @param {carte} carte - un paramètre de type carte
 * @return {int}
 */
void setNbDechetPortail(carte* carte, int dechet);

/**
 * Cette fonction retourne le nombre de ressource du portail
 * @param {carte} carte - un paramètre de type carte
 * @return {int}
 */
int getNbRessourcePortail(carte* carte);


/**
 * Cette fonction retourne le nombre de personnel
 * @param {carte} carte - un paramètre de type carte
 * @return {int}
 */
int getNbPersonnel(carte* carte);

/**
 * Cette fonction retourne le type de ressource d'un FISA
 * @param {carte} carte - un paramètre de type carte
 * @return {typeRessource}
 */
typeRessource getTypeRessourceFISA(carte* carte);

/**
 * Cette fonction retourne une liste de personnel
 * @param {carte} carte - un paramètre de type carte
 * @return {personnel*}
 */
listePersonnel* getListePersonnel(carte* carte);

/**
 * Cette fonction retourne la ligne de production d'une cellule
 * @param {cellule} cellule - un parametre de type cellule
 * @return {ligneDeProductiion*}
 */
ligneDeProduction* getLigneDeProd(cellule* cellule);

/**
 *  Cette fonction retourne les ressources d'un joueur
 * @param {carte} carte - un parametre de type carte
 * @return {cout*}
 */
cout* getRessourceJoueur(carte* carte);
/**
 * Cette fonction créer une carte
 * @param {int} taille - un parametre de type int
 * @return {carte*}
 */
carte* creationCarte(int taille);

/**
 * Cette fonction libére la mémoire alloué
 *  à une carte
 * @param {carte} carte - un paramètre de type carte
 */
void libererMemoireCarte(carte* carte);

/**
 *  Cette fonction va recruter un FISE
 * @param {carte} carte - un paramètre de type carte
 */
int recruterFISE(carte* carte,int nbRecruter);

/**
 *  Cette fonction va recruter un FISA
 * @param {carte} carte - un paramètre de type carte
 */
int recruterFISA(carte* carte,int nbRecruter);

/**
 * Cette fonction change le type de ressource créée par les FISA
 * @param {carte} carte - un paramètre de type carte
 */
void changementTypeRessource(carte* carte);

/**
 *  Cette fonction va terminer le tour
 * @param {carte} carte - un paramètre de type 
 *
*/
void terminerTour(carte *carte);
/**
 * Cette fonction retourne le nombre de fisa NbFisa
 * @param {carte} carte - un paramatre de type carte
 * @return {int}
 * */
int getNbFISA(carte* carte);
/**
 * Cette fonction retourne le nombre de fiseNbFise
 * @param {carte} carte - un paramatre de type carte
 * @return {int}
 * */
int getNbFISE(carte* carte);
/**
 * Cette fonction retourne le cout d'un fisa
 * @param {carte} carte - un paramatre de type carte
 * @return {cout}
 * */
cout *getCoutFISA(fisa* fisa);
/**
 * Cette fonction retourne le cout d'un fise
 * @param {carte} carte - un paramatre de type carte
 * @return {cout}
 * */
cout *getCoutFISE(fise* fise);
/**
 * Cette fonction retourne la production d'un fisa 
 * @param {carte} carte - un paramatre de type carte
 * @return {cout}
 * */
cout *getProductionFISE(fise* fise);
/**
 * Cette fonction retourne le cout d'un fise
 * @param {carte} carte - un paramatre de type carte
 * @return {cout}
 * */
cout *getProductionFISA(fisa* fisa);

void updateCoutFise(fise* infoFise,int persoDD,int persoE,int persoE_Min,int persoDD_Min);
void updateCoutFisa(fisa* infoFisa,int persoDD,int persoE,int persoE_Min,int persoDD_Min);
/**
 * Cette fonction permet d'ajouter une machine sur une case donné
 * si les ressources du joueur le permette celon une certaine orientation
 *
 * @param {listeLigneDeProduction} liste- La liste de ligne de production
 * @param {machine} machine - La machine qui doit être ajouté
 * @param {coord} coord - les coordoonées de la machine à ajouté
 * @param {pointCard} orientation - Orientation de la machine (enum pointCard)
 * @param {cout} cout - Les ressources du Joueur
 * @param {carte} carte - carte
 * @ return {int} - Renvois 1 si la machine a pu être ajouté, 0 sinon
 */
int achatMachine
(
    listeLigneDeProduction *liste, 
    machine* machine, 
    coord* coord, 
    pointCard orientation, 
    cout* argent,
    carte* carte
);

/**
 * Cette fonction permet d'améliorer une machine sur une case donné
 * si les ressources du joueur le permette
 *
 * @param {ligneDeProduction} 
 * @param {cout} 
 * @return {int} - Renvois 1 si la machine a pu être améliorer, 0 sinon
 */
int amelioreMachine(ligneDeProduction* ldp, cout* argent);

/**
 * Cette fonction permet de détruire une machine sur une case donné
 * si les ressources du joueur le permette
 *
 * @param {listeLigneDeProduction}
 * @param {ligneDeProduction} 
 * @param {cout}
 * @param {int}
 * @return {int} - Renvois 1 si la machine a pu être détruite, 0 sinon
 */
int detruireMachine
(
    listeLigneDeProduction* liste,
    ligneDeProduction* ldp, 
    cout* argent, 
    int* nbDechetPortail
);

/**
 * Cette fonction permet de recruter un personnel
 * si les ressources du joueur le permette
 *
 * @param {carte} - Paramètre permettant d'ajouter le personnel (contient aussi les informations sur les ressources du joueur)
 * @param {personnel} - Personnel à recruter
 * @param {machine} listeMachine - liste de machine sur la carte
 * @param {int} nbMachine - le nombre de machine sur la carte
 * @param {personnel} listePerso - une liste de Personnel 
 * @param {int} nbPerso - le nombre de personnel sur la carte
 * @ return {int} - Renvois 1 si le personnel a pu être recruté, 0 sinon
 */
int recruterPersonnel
(
    carte* carte, 
    personnel* perso,
    machine** listeMachine,
    int nbMachine,
    personnel** listePerso,
    int nbPerso
);

void getNombresAleatoires(int tailleCarte, int *listeNombresAleatoires);

#endif
