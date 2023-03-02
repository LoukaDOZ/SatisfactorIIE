#include "../headers/cout.h"


/********** Cout en DD **********/

int getCoutDD(cout* cout){
  return cout->DD;
}

int setCoutDD(cout* cout, int val){
  cout->DD = val;
  return cout->DD >= 0;
}

int updateCoutDD(cout* cout, int val, int min){
  if(cout->DD + val >= min)
    cout->DD += val;
  else
    cout->DD = min;
  return cout->DD >= 0;
}

int updateCoutDD2(cout* cout, int val){
  cout->DD += val;
  return cout->DD >= 0;
}

/********** Cout en E **********/

int getCoutE(cout* cout){
  return cout->E;
}


int setCoutE(cout* cout, int val){
  cout->E = val;
  return cout->E >= 0;
}

int updateCoutE(cout* cout, int val, int min){
  if(cout->E + val >= min)
    cout->E += val;
    else
      cout->E = min;
  return cout->E >= 0;
}

int updateCoutE2(cout* cout, int val){
  cout->E += val;
  return cout->E >= 0;
}

/********** Vérification cout **********/

int verifCout(cout* cout1, cout* cout2){
  return getCoutDD(cout1) >= getCoutDD(cout2) && getCoutE(cout1) >= getCoutE(cout2);
}

int verifCout2(cout* cout1, int coutDD, int coutE){
  return getCoutDD(cout1) >= coutDD && getCoutE(cout1) >= coutE;
}

/********** Update cout **********/

int updateCout(cout* cout1, cout* cout2){
  if(verifCout(cout1,cout2)){
    updateCoutDD(cout1,-getCoutDD(cout2),0);
    updateCoutE(cout1,-getCoutE(cout2),0);
    return 1;
  }
  else
    return 0;
}

int updateCout2(cout* cout, int coutDD, int coutE){
  if(verifCout2(cout,coutDD,coutE)){
    updateCoutDD(cout,-coutDD,0);
    updateCoutE(cout,-coutE,0);
    return 1;
  }
  else
    return 0;
}

int updateCout3(cout* cout, int coutDD, int coutE){
  updateCoutDD(cout,coutDD,0);
  updateCoutE(cout,coutE,0);
  return 1;
}
