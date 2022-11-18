#ifndef ECE_CITY_1_A_INFORMATIONPERM_H
#define ECE_CITY_1_A_INFORMATIONPERM_H

#include "raylib.h"

typedef struct{

    int time;
    float ECEFlouz;
    int habitants;
    int capaciteElec;
    int capaciteEau;
    float prixHabitation;
    float prixCentrale;
    float prixRoute;

}INFO;

void initialisationInfo(INFO *infoPerm);

void affichageInfo(INFO *infoPerm);

#endif //ECE_CITY_1_A_INFORMATIONPERM_H
