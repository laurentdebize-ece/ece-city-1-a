#include "map.h"


int main(){
    Map map[45][35];
    HUD hud[6];
    initialiserMap(map,hud);
    InitWindow(LARGUEUR, HAUTEUR, "ECE city");

    int evolution = 0;
    int time;
    int collisionHUD;
    int collisionMAP;

    Vector2 mapPosition = { 0.0f, 0.0f };
    Vector2 mapSize = { LARGEUR1CASE,  LARGEUR1CASE };

    Vector2 mousePosition = {0};

    SetTargetFPS(60);

    //Fonction executé
    boucle(map,hud,mapPosition,mapSize,mousePosition,evolution,time,collisionHUD,collisionMAP);

}
