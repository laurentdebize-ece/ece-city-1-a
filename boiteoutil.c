#include "boiteoutil.h"
#include "map.h"

void initialisationCaseHUD(Rectangle HUD[NOMBRE_CASE_HUD]){

    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {

        HUD[i].height=50;
        HUD[i].width=50;
        HUD[i].x=10;
        HUD[i].y=150 + HUD[i].width * (float)i;

    }
}

void initialisationHUD(HUD hud[6]){
    for (int i=0;i<NOMBRE_CASE_HUD;i++){
        hud[i].etat=0;
    }
}

void remiseZero(HUD hud[6],int i){
    for (int j=0;j<6;j++){
        if (j!=i){
            hud[j].etat=0;}
    }
}

void HUDcollision(HUD hud[NOMBRE_CASE_HUD],Rectangle HUD[NOMBRE_CASE_HUD],Vector2 mousePosition){
    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {

        //HUD.y = HUD.y + HUD.height * (float)i;

        if (CheckCollisionPointRec(mousePosition, HUD[i]) != 0) {
            DrawRectangle((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BLUE);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                hud[i].etat = 1;
                remiseZero(hud, i);
            }
        }
    }
}

void dessinerHUD(Rectangle HUD[NOMBRE_CASE_HUD]){
    for (int i = 0; i < 6; i++) {
        DrawRectangleLines((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BLUE);
    }
}