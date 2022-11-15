//
// Created by Erwan Pillard on 09/11/2022.
//

#include "boiteoutil.h"
#include "map.h"

Rectangle initialisationCaseHUD(){
    Rectangle HUD;

    HUD.height=50;
    HUD.width=50;
    HUD.x=10;
    HUD.y=50;

    return HUD;
}

void initialisationHUD(HUD hud[6]){
    for (int i=0;i<NOMBRE_CASE_HUD;i++){
        hud[i].etat=0;
    }
}

Rectangle initialisationCaseMAP(){
    Rectangle MAP;

    MAP.x = POSITIONMAP_X;
    MAP.y = POSITIONMAP_Y;
    MAP.height=LARGEUR1CASE;
    MAP.width=LARGEUR1CASE;

    return MAP;
}

void remiseZero(HUD hud[6],int i){
    for (int j=0;j<6;j++){
        if (j!=i){
            hud[j].etat=0;}
    }
}

void HUDcollision(HUD hud[NOMBRE_CASE_HUD],Rectangle HUD,Vector2 mousePosition){
    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {

        HUD.y = HUD.height + HUD.height * (float)i;

        if (CheckCollisionPointRec(mousePosition, HUD) != 0) {
            DrawRectangle((int)HUD.x, (int)HUD.y, (int)HUD.width, (int)HUD.height, BLUE);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                hud[i].etat = 1;
                remiseZero(hud, i);
            }
        }
    }
}

void dessinerHUD(Rectangle HUD){
    for (int i = 0; i < 6; i++) {
        DrawRectangleLines((int)HUD.x, (int)HUD.y + (int)HUD.height * i, (int)HUD.width, (int)HUD.height, BLUE);
    }
}