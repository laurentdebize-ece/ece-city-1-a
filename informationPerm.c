//
// Created by Erwan Pillard on 15/11/2022.
//

#include "informationPerm.h"

void affichageInfo(int time){ //Temps, argent etc...
    DrawRectangleLines(10, 10, 100, 20, BLUE);
    DrawText(TextFormat("Time: %d", (time)), 20, 15, 10, BLACK);
}