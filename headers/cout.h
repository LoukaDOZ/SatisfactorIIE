#ifndef COUT_H
#define COUT_H

typedef struct cout cout;

/**
 * Cette structure sert à représenter les différentes ressources (en E et DD)
 * comme un seul attribut pour l'ensemble des autres structure.
 *
 * @attr {int} E - Utilisé pour identifier un cout / une valeur en E
 * @attr {int} DD - Utilisé pour identifier un cout / une valeur en DD
 *
 */
struct cout {
  int E;
  int DD;
};

/********** Cout en DD **********/

/**
 * Renvois la valeur en DD du @param {cout}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va récupérer les DD
 * @return {int} - Représentation de la valeur en DD
 */
int getCoutDD(cout* cout);

/**
 * Permet de mettre à jour la valeur en DD @param {cout} avec une valeur
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va mettre à jour les DD
 * @param {val} - Valeur fixé
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int setCoutDD(cout* cout, int val);

/**
 * Permet de mettre à jour la valeur en DD @param {cout} en ajoutant une valeur à la valeur par défaut, si le minimum @param {min} est dépassé, la valeur en DD vaut @param {min}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va mettre à jour les DD
 * @param {val} - Valeur qu'on va ajouter
 * @param {min} - Valeur minimale du nouveau cout
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutDD(cout* cout, int val, int min);

/**
 * Permet de mettre à jour la valeur en DD @param {cout} en ajoutant une valeur à la valeur par défaut
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va mettre à jour les DD
 * @param {val} - Valeur qu'on va ajouter
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutDD2(cout* cout, int val);

/********** Cout en E **********/

/**
 * Renvois la valeur en E du @param {cout}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va récupérer les E
 * @return {int} - Représentation de la valeur en E
 */
int getCoutE(cout* cout);

/**
 * Permet de mettre à jour la valeur en E @param {cout} avec une valeur
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va mettre à jour les E
 * @param {val} - Valeur fixé
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int setCoutE(cout* cout, int val);

/**
 * Permet de mettre à jour la valeur en E @param {cout} en ajoutant une valeur à la valeur par défaut, si le minimum @param {min} est dépassé, la valeur en E vaut @param {min}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va mettre à jour les E
 * @param {val} - Valeur qu'on va ajouter
 * @param {min} - Valeur minimale du nouveau cout
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutE(cout* cout, int val, int min);

/**
 * Permet de mettre à jour la valeur en E @param {cout} en ajoutant une valeur à la valeur par défaut
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va mettre à jour les E
 * @param {val} - Valeur qu'on va ajouter
 * @return {int} - 1 si la valeur est positive ou nule, 0 sinon
 */
int updateCoutE2(cout* cout, int val);

/********** Vérification cout **********/

/**
 * Permet de comparer un cout @param {cout} avec un second cout @param {cout2}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va effectuer une comparaison
 * @param {cout2} - Représente la valeur à comparé en DD
 * @return {int} - 1 si le cout en DD et le cout en E de cout2 sont supérieur ou égale à ceux présent dans cout
 */
int verifCout(cout* cout1, cout* cout2);


/**
 * Permet de comparer un cout @param {cout} avec une valeur en DD @param {coutDD} et en E @param {coutE}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va effectuer une comparaison
 * @param {coutDD} - Représente la valeur à comparé en DD
 * @param {coutE} - Représente la valeur à comparé en E
 * @return {int} - 1 si le coutDD et le coutE sont supérieur ou égale à ceux présent dans cout
 */
int verifCout2(cout* cout1, int coutDD, int coutE);

/********** Update cout **********/

/**
 * Permet de mettre à jour un cout @param {cout} en soustrayant un autre cout @param {cout2}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va effectuer les modifications
 * @param {cout2} - Représente les ressources à enlever à @param {cout}
 * @return {int} - 1 la mise à jour à pu être effectué, 0 sinon
 */
int updateCout(cout* cout1, cout* cout2);

/**
 * Permet de mettre à jour un cout @param {cout} en soustrayant une valeur en DD @param {coutDD} et une valeur en E @param {coutE}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va effectuer les modifications
 * @param {coutDD} - Représente la valeur à décrémenter en DD
 * @param {coutE} - Représente la valeur à décrémenter en E
 * @return {int} - 1 la mise à jour à pu être effectué, 0 sinon
 */
int updateCout2(cout* cout, int coutDD, int coutE);

/**
 * Permet de mettre à jour un cout @param {cout} en ajoutant une valeur en DD @param {coutDD} et une valeur en E @param {coutE}
 *
 * @param {cout} - Ensemble de ressources sur lequelle on va effectuer les modifications
 * @param {coutDD} - Représente la valeur à incrémenter en DD
 * @param {coutE} - Représente la valeur à incrémenter en E
 * @return {int} - 1 la mise à jour à pu être effectué
 */
int updateCout3(cout* cout, int coutDD, int coutE);

#endif
