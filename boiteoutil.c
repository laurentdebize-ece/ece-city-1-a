#include "boiteoutil.h"
#include "map.h"

void initialisationCaseHUD(Rectangle HUD[NOMBRE_CASE_HUD]){

    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {

        HUD[i].height=100;
        HUD[i].width=100;
        HUD[i].x=30;
        HUD[i].y=200 + HUD[i].width * (float)i;

    }
}

void initialisationHUD(HUD hud[NOMBRE_CASE_HUD]){
    for (int i=0;i<NOMBRE_CASE_HUD;i++){
        hud[i].etat=0;
    }
}

void remiseZero(HUD hud[NOMBRE_CASE_HUD],int i){
    for (int j=0;j<NOMBRE_CASE_HUD;j++){
        if (j!=i){
            hud[j].etat=0;}
    }
}

void HUDcollision(HUD hud[NOMBRE_CASE_HUD],Rectangle HUD[NOMBRE_CASE_HUD],Vector2 mousePosition){
    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {

        //HUD.y = HUD.y + HUD.height * (float)i;

        if (CheckCollisionPointRec(mousePosition, HUD[i]) != 0) {
            DrawRectangle((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BROWN);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                hud[i].etat = 1;
                remiseZero(hud, i);
            }
        }
    }
}

void dessinerHUD(Rectangle HUD[NOMBRE_CASE_HUD]){
    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {
        DrawRectangle((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BEIGE);
        DrawRectangleLines((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BLACK);
    }
}