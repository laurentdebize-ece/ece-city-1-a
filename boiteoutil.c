#include "boiteoutil.h"
#include "map.h"

void initialisationCaseHUD(Rectangle HUD[NOMBRE_CASE_HUD]){

    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {

        HUD[i].height=100;
        HUD[i].width=100;
        HUD[i].x=30;
        HUD[i].y=200 + HUD[i].width * (float)i;

    }

    HUD[4].height=100;
    HUD[4].width=100;
    HUD[4].x=895;
    HUD[4].y=250;

    HUD[5].height=100;
    HUD[5].width=100;
    HUD[5].x=895;
    HUD[5].y=350;

    HUD[6].height=100;
    HUD[6].width=100;
    HUD[6].x=895;
    HUD[6].y=450;

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

void HUDcollision(HUD hud[NOMBRE_CASE_HUD],Rectangle HUD[NOMBRE_CASE_HUD],Vector2 mousePosition, int *niveauAffichage){
    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {

        //HUD.y = HUD.y + HUD.height * (float)i;

        if (CheckCollisionPointRec(mousePosition, HUD[i]) != 0) {
            if (i < 4){
                DrawRectangle((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BROWN);
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    hud[i].etat = 1;
                    remiseZero(hud, i);
                }
            }
            else{
                DrawRectangleLines((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BROWN);
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    hud[i].etat = 1;
                    *niveauAffichage = i - 4;
                }
            }
        }
    }
}

void dessinerHUD(Rectangle HUD[NOMBRE_CASE_HUD]){
    for (int i = 0; i < NOMBRE_CASE_HUD; i++) {
        DrawRectangle((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BEIGE);
        DrawRectangleLines((int)HUD[i].x, (int)HUD[i].y, (int)HUD[i].width, (int)HUD[i].height, BLACK);
    }

    DrawRectangleGradientH( (int)HUD[4].x,  (int)HUD[4].y, (int)HUD[4].width,  (int)HUD[4].height, BEIGE, BROWN);
    DrawRectangleLines((int)HUD[4].x, (int)HUD[4].y, (int)HUD[4].width, (int)HUD[4].height, WHITE);
    DrawText("0", 925, 265, 80, WHITE);

    DrawRectangleGradientH((int)HUD[5].x, (int)HUD[5].y, (int)HUD[5].width, (int)HUD[5].height,BEIGE, BROWN);
    DrawRectangleLines((int)HUD[5].x, (int)HUD[5].y, (int)HUD[5].width, (int)HUD[5].height, WHITE );
    DrawText("-1", 910, 365, 70, WHITE);

    DrawRectangleGradientH((int)HUD[6].x, (int)HUD[6].y, (int)HUD[6].width, (int)HUD[6].height,BEIGE, BROWN);
    DrawRectangleLines((int)HUD[6].x, (int)HUD[6].y, (int)HUD[6].width, (int)HUD[6].height, WHITE);
    DrawText("-2", 905, 465, 70, WHITE);

}