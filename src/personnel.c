#include "../headers/personnel.h"

struct s_infos_personnel infos_personnel = {.numero = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24},
                                            .nom = {"Fetia Bannour", "Kevin Goilard", "Vincent Jeannas", "Thomas Laurent",
                                                    "Massinissa Merabet", "Stefi Nouleho", "Vitera Y", "Laurence Bourard",
                                                    "Nicolas Brunel", "Anastase Charantonis", "Catherine Dubois", "Stefania Dumbrava",
                                                    "Alain Faye", "Anne-Laure Ligozat", "Christophe Mouilleron", "Marie Szafranski",
                                                    "Gael Thomas", "Eric Lejeune", "Christine Mathias", "Katrin Salhab",
                                                    "Julien Forest", "Thomas Lim", "Dimitri Watel", "Laurent Prével"},
                                            .e = {100, 100, 100, 100, 100, 200, 200, 200, 100 , 100, 100, 100, 100,
                                                  1000, 1000, 1000, 1000, 1000, 1000, 1500, 2000, 1000, 2000, 3000},
                                            .dd = {30, 30, 30, 30, 30, 100, 100, 100, 200, 200, 200, 200, 200,
                                                   10, 400, 400, 400, 200, 200, 300, 500, 400, 500, 1000},
                                            .premiere_action = {10, 3, 8, 25, 5, 25, 75, 10, 3, 3, 3, 5, 5, 2, 20, 2, 10, 5, 5, 50, 1, 1, 4, 10},
                                            .deuxieme_action = {1, 1, 1, 2, 5, 5, 5, 30, 10, 10, 10, 25, 10, 0, 10, 1, 0, 2, 2, 20, 1, 0, 4, 1},
                                            .premiere_action_min = {10, 3, 8, 25, 5, 25, 75, 20, 3, 3, 3, 5, 5, 0, 0, 0, 0, 5, 5, 10, 0, 1, 0, 0},
                                            .deuxieme_action_min = {1, 1, 1, 2, 5, 5, 5, 30, 10, 10, 10, 25, 10, 0, 0, 0, 0, 2, 2, 10, 0, 0, 0},
                                            .effet = {"Le coût de construction des collecteurs diminue de 10E et 1DD (minimum 10E et 1DD).", "Le coût de construction des tapis diminue de 3E et 1DD (minimum 3E et 1DD).", "Le coût de construction des croix diminue de 8E et 1DD (minimum 8E et 1DD).", "Le coût de construction des centres de recyclage diminue de 25E et 2DD (minimum 25E et 2DD).", "Le coût de construction des déchetterie diminue de 5E et 5DD (minimum 5 et 5DD).", "Le coût d’amélioration des collecteurs diminue de 25E et 5DD (minimum 25E et 5DD).", "Le coût d’amélioration des centres de recyclage diminue de 75E et 5DD (mini-mum 75E et 5DD).", "Le coût d’amélioration des déchetterie diminue de 10E et 30DD (minimum 20E et 30DD).", "Le coût de destruction des collecteurs diminue de 3E et 10DD (minimum 3Eet 10DD).", "Le coût de destruction des tapis diminue de 3E et 10DD (minimum 3E et 10DD).", "Le coût de destruction des croix diminue de 3E et 10DD (minimum 3E et 10DD).", "Le coût de destruction des centres de recyclage diminue de 5E et 25DD (minimum 5E et 25DD).", "Le coût de destruction des déchetterie diminue de 5E et 10DD (minimum 5Eet 10DD).", "La moitié des déchets de chaque case disparaissent.", "L’école recrute 20 FISE et 10 FISA.", "A chaque fois qu’une ressource est envoyée à la porte, elle compte double. Le nombre de déchet produit est toujours de 1.", "Quand un déchet quitte la porte, il a une chance sur 10 de disparaître.", "Le coût des FISE diminue de 5E et 2DD (minimum 5E et 2DD).", "Le coût des FISA diminue de 5E et 2DD (minimum 5E et 2DD).", "Les membres du personnel coûtent 50E et 20DD de moins (minimum 10E et 10DD).", "Les FISE produisent 1E et 1DD de plus chaque tours.", "Les sources mettent un tour de moins à produire (minimum 1).", "Les FISA produisent 4E ou 4DD de plus tous les deux tours.", "Un dixième des FISE et des FISA de l’école sont diplômés. Ils quittent l’écolemais chaque élève diplômé envoie une ressource à la porte."}};

/********** Num **********/

void setNumPersonnel(personnel* perso, int num){
  perso->num = num;
}

int getNumPersonnel(personnel* perso){
  return perso->num;
}

/********** Nom **********/

void setNomPersonnel(personnel* perso, char* nom){
  perso->nom = nom;
}

char* getNomPersonnel(personnel* perso){
  return perso->nom;
}

/********** Description **********/

void setDescPersonnel(personnel* perso, char* desc){
  perso->description = desc;
}

char* getDescPersonnel(personnel* perso){
  return perso->description;
}

/********** Cout **********/

cout* getCoutAction(personnel* perso){
  return perso->action;
}

void setCoutActionDD(personnel* perso, int val){
  perso->action->DD = val;
}

void setCoutActionE(personnel* perso, int val){
  perso->action->E = val;
}

cout* getCoutActionMin(personnel* perso){
  return perso->min_action;
}


void setCoutActionMinDD(personnel* perso, int val){
  perso->min_action->DD = val;
}

void setCoutActionMinE(personnel* perso, int val){
  perso->min_action->E = val;
}

cout* getCoutAchat(personnel* perso){
  return perso->cout_engagement;
}

void setCoutAchatDD(personnel* perso, int val){
  perso->cout_engagement->DD = val;
}

void setCoutAchatE(personnel* perso, int val){
  perso->cout_engagement->E = val;
}

void setCoutAchat(personnel* perso, cout* cout){
  perso->cout_engagement = cout ;
}

void setCoutAchat2(personnel* perso, int coutDD, int coutE){
  setCoutAchatDD(perso, coutDD);
  setCoutAchatE(perso, coutE);
}

void updateCoutAchat(personnel* perso, int redDD, int redE, int minDD, int minE){
  updateCoutE(getCoutAchat(perso), -redE, minE);
  updateCoutDD(getCoutAchat(perso), -redDD, minDD);
}

/********** Achat Personnel **********/

int achatPersonnel(personnel* perso,cout* argent){
  return updateCout(argent, getCoutAchat(perso));
}

/********** Fonction main **********/

void init_personnel(personnel ***liste_personnel, int *taille_liste_personnel) {
    *liste_personnel = (personnel**) malloc(NOMBRE_PERSONNEL*sizeof(personnel*));
    for(int i=0; i<NOMBRE_PERSONNEL; i++) {
        personnel *perso = (personnel*) malloc(sizeof(personnel));
        setNumPersonnel(perso, i+1);
        
        setNomPersonnel(perso, infos_personnel.nom[i]);
        
        setDescPersonnel(perso, infos_personnel.effet[i]);
        
        cout *action = (cout*) malloc(sizeof(cout));
        perso->action = action;
        setCoutActionE(perso, infos_personnel.premiere_action[i]);
        setCoutActionDD(perso, infos_personnel.deuxieme_action[i]);
        
        cout *action_min = (cout*) malloc(sizeof(cout));
        perso->min_action = action_min;
        setCoutActionMinE(perso, infos_personnel.premiere_action_min[i]);
        setCoutActionMinDD(perso, infos_personnel.deuxieme_action_min[i]);
        
        cout *engagement = (cout*) malloc(sizeof(cout));
        perso->cout_engagement = engagement;
        setCoutAchatE(perso, infos_personnel.e[i]);
        setCoutAchatDD(perso, infos_personnel.dd[i]);
        
        (*liste_personnel)[i] = perso;
        /*printf("[%d] : %s\n%s\n%d %d\n%d %d\n%d %d\n\n", infos_personnel.numero[i], infos_personnel.nom[i], infos_personnel.effet[i], infos_personnel.premiere_action[i],
                                                        infos_personnel.deuxieme_action[i], infos_personnel.premiere_action_min[i], infos_personnel.deuxieme_action_min[i],
                                                        infos_personnel.e[i], infos_personnel.dd[i]);*/
        /*printf("[%d] : %s\n%s\n%d %d\n%d %d\n%d %d\n\n", perso->num, perso->nom, perso->description, perso->action->E, perso->action->DD,
                                                     perso->min_action->E, perso->min_action->DD, perso->cout_engagement->E, perso->cout_engagement->DD);*/
    }
    *taille_liste_personnel = NOMBRE_PERSONNEL;
}
