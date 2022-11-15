//
// Created by Erwan Pillard on 09/11/2022.
//

#ifndef ECE_CITY_1_A_BOITEOUTIL_H
#define ECE_CITY_1_A_BOITEOUTIL_H

#include "raylib.h"


#define NOMBRE_CASE_HUD 6

typedef struct{
    int etat;
}HUD;

Rectangle initialisationCaseHUD();
Rectangle initialisationCaseMAP();

void initialisationHUD(HUD hud[6]);
void dessinerHUD(Rectangle HUD);
void HUDcollision(HUD hud[NOMBRE_CASE_HUD],Rectangle HUD,Vector2 mousePosition);
#endif //ECE_CITY_1_A_BOITEOUTIL_H
