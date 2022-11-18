//
// Created by Erwan Pillard on 15/11/2022.
//

#include "informationPerm.h"


void initialisationInfo(INFO *infoPerm){

    infoPerm->time = 0;
    infoPerm->ECEFlouz = 500000.0f;
    infoPerm->habitants = 0;
    infoPerm->capaciteEau = 0;
    infoPerm->capaciteElec = 0;
    infoPerm->prixCentrale = 100000.0f;
    infoPerm->prixHabitation = 1000.0f;
    infoPerm->prixRoute = 10.0f;
}

void affichageInfo(INFO *infoPerm){ //Temps, argent etc...
    DrawRectangleLines(10, 10, 160, 90, BLUE);
    DrawText(TextFormat("Time: %d", (infoPerm->time)), 20, 15, 10, BLACK);
    DrawText(TextFormat("ECEFlouz: %f", (infoPerm->ECEFlouz)), 20, 30, 10, BLACK);
    DrawText(TextFormat("Habitants: %d", (infoPerm->habitants)), 20, 45, 10, BLACK);
    DrawText(TextFormat("Capacité électricité: %d", (infoPerm->capaciteElec)), 20, 60, 10, BLACK);
    DrawText(TextFormat("Capacité eau: %d", (infoPerm->capaciteEau)), 20, 75, 10, BLACK);
}