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

void initialisationCaseHUD(Rectangle HUD[NOMBRE_CASE_HUD]);

void initialisationHUD(HUD hud[6]);
void dessinerHUD(Rectangle HUD[NOMBRE_CASE_HUD]);
void HUDcollision(HUD hud[NOMBRE_CASE_HUD],Rectangle HUD[NOMBRE_CASE_HUD],Vector2 mousePosition);
#endif //ECE_CITY_1_A_BOITEOUTIL_H
