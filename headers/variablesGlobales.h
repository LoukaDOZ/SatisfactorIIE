#ifndef VARIABLESGLOBALES_H
#define VARIABLESGLOBALES_H
/////////////////////////////////////////////////////////////////////////////////
#define E_INITIAL 10000
#define DD_INITIAL 10000
#define NB_SOURCES_PLATEAU 3
#define NB_RESSOURCES_PRODUITES_SOURCE 3
#define NB_INITIAL_FISE 5
#define NB_INITIAL_FISA 5
#define NB_INITIAL_E_PRODUITS_FISE 1
#define NB_INITIAL_DD_PRODUITS_FISE 1
#define NB_INITIAL_E_PRODUITS_FISA 4
#define NB_INITIAL_DD_PRODUITS_FISA 4
#define RESSOURCES_FIN_PARTIE 10000
#define COUT_ACHAT_ELEVE_E 50
#define COUT_ACHAT_ELEVE_DD 20
#define NOMBRE_PERSONNEL 24
#define NOMBRE_MACHINES 5


struct s_infos_machines {
    char *nom[NOMBRE_MACHINES];
    unsigned int e_construction[NOMBRE_MACHINES];
    unsigned int dd_construction[NOMBRE_MACHINES];
    unsigned int e_amelioration[NOMBRE_MACHINES];
    unsigned int dd_amelioration[NOMBRE_MACHINES];
    unsigned int e_destruction[NOMBRE_MACHINES];
    unsigned int dd_destruction[NOMBRE_MACHINES];
    unsigned int stock_initial[NOMBRE_MACHINES];
    unsigned int stock_amelioration[NOMBRE_MACHINES];
    char *effet[NOMBRE_MACHINES];
};


struct s_infos_personnel {
    unsigned int numero[NOMBRE_PERSONNEL];
    char *nom[NOMBRE_PERSONNEL];
    unsigned int e[NOMBRE_PERSONNEL];
    unsigned int dd[NOMBRE_PERSONNEL];
    unsigned int premiere_action[NOMBRE_PERSONNEL];
    unsigned int deuxieme_action[NOMBRE_PERSONNEL];
    unsigned int premiere_action_min[NOMBRE_PERSONNEL];
    unsigned int deuxieme_action_min[NOMBRE_PERSONNEL];
    unsigned int type_action_personnel[NOMBRE_PERSONNEL];
    char *effet[NOMBRE_PERSONNEL];
};


struct s_infos_carte {
    char *type[3];
    unsigned int hauteur [3];
    unsigned int largeur [3];
};


#endif
