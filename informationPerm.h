//
// Created by Erwan Pillard on 15/11/2022.
//

#ifndef ECE_CITY_1_A_INFORMATIONPERM_H
#define ECE_CITY_1_A_INFORMATIONPERM_H

#include "raylib.h"

typedef struct{
    int time;
    float ECEFlouz;
    int habitants;
    int capaciteElec;
    int capaciteEau;
}INFO;

INFO initialisationInfo();

void affichageInfo(INFO infoPerm);

#endif //ECE_CITY_1_A_INFORMATIONPERM_H
