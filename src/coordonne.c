#include "../headers/coordonne.h"


int getCoordX(coord* coord){
  return coord->x;
}

int setCoordX(coord* coord, int val){
  coord->x = val;
  return coord->x >= 0;
}

int getCoordY(coord* coord){
  return coord->y;
}

int setCoordY(coord* coord, int val){
  coord->y = val;
  return coord->y >= 0;
}

int coordExist(coord* coord, int size){
  return getCoordX(coord) < size && getCoordX(coord) >= 0 && getCoordY(coord) < size && getCoordY(coord) >= 0;
}

int setCoord(coord* coord, int x, int y, int sizeCard){
  if( 0>x || x >= sizeCard || 0>y || y >= sizeCard)
    return 0;
  setCoordX(coord, x);
  setCoordY(coord, y);
  return 1;
}

void setCoord2(coord* coord1, coord* coord2){
  setCoordX(coord1, getCoordX(coord2));
  setCoordY(coord1, getCoordY(coord2));
}

int diffCoord(coord* coord1, coord* coord2){
  return getCoordX(coord1) == getCoordX(coord2) && getCoordY(coord1) == getCoordY(coord2);
}

int compareCoord(coord* coord1, coord* coord2){
  return getCoordX(coord1) > getCoordX(coord2) || (getCoordX(coord1) == getCoordX(coord2) && getCoordY(coord1) > getCoordY(coord2));
}

//TODO
/*
 1 sup
 0 egal
 -1 inf
*/
int compareCoord2(coord* coord1, coord* coord2) {
    if(getCoordX(coord1) > getCoordX(coord2)) {
        return 1;
    } else if(getCoordX(coord1) == getCoordX(coord2)) {
        if(getCoordY(coord1) > getCoordY(coord2)) {
            return 1;
        } else if(getCoordY(coord1) == getCoordY(coord2)) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return -1;
    }

}

int compareCoord3(coord* coord1, coord* coord2){
  return (getCoordX(coord1) == getCoordX(coord2) && getCoordY(coord1) == getCoordY(coord2));
}

void setNewCoord(coord* caseArriver, pointCard* directionArriver){
  if(*directionArriver == NORD){
    setCoordY(caseArriver, getCoordY(caseArriver)-1);
  }
  else if(*directionArriver == EST){
    setCoordX(caseArriver, getCoordX(caseArriver)+1);
  }
  else if(*directionArriver == SUD){
    setCoordY(caseArriver, getCoordY(caseArriver)+1);
  }
  else{
    setCoordX(caseArriver, getCoordX(caseArriver)-1);
  }
}
