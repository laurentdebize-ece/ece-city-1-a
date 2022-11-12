#include "map.h"


int main(){
    MAP map[45][35];
    HUD hud[NOMBRE_CASE_HUD];
    initialiserMap(map,hud);

    InitWindow(LARGUEUR, HAUTEUR, "ECE city");

    SetTargetFPS(60);

    //Fonction executé

    //affichermenu();
    //boucle(map,hud,evolution,time,collisionHUD,collisionMAP);
    mapNiveau0(map, hud);

}
