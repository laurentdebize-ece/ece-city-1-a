#include "map.h"


void initialiserMap(Map map[45][35],HUD hud[6]){

    for (int i=0;i<45;i++){
        for (int j=0;j<35;j++){
            map[i][j].etat=-1;
            map[i][j].stade=0;
            map[i][j].occupe=0;
        }
    }
    for (int i=0;i<6;i++){
        hud[i].etat=0;
    }
}

void remiseZero(HUD hud[6],int i){
    for (int j=0;j<6;j++){
        if (j!=i){
            hud[j].etat=0;}
    }
}

int temps(Map map[45][35],int evolution,int time){

    if (time%15==0 && time!=map[0][0].tempsBanni){ //Savoir si temps est un multiple de 15 pour l'evolution
        evolution=1;
        map[0][0].tempsBanni=time;
    }
    return evolution;
}

void dessinerMap(Vector2 mapPosition,int i,int j){

    DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE, LARGEUR1CASE, GRAY);

}

void placementBatiment(Map map[45][35],Vector2 mapPosition,int i,int j){
    if (map[i][j].etat == 0) {  //Quoi faire en fonction de l'etat de la case (voir map.h)
        DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE, LARGEUR1CASE, BLACK);
    }
    else if (map[i][j].etat == 1) { //Evolution des maisons
        if (map[i][j].stade == 0) {
            DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE * 2.5 , LARGEUR1CASE * 2.5  , RED);
        }
        if (map[i][j].stade == 1) {
            DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE * 2.5  , LARGEUR1CASE * 2.5  ,
                          GREEN);
        }
        if (map[i][j].stade == 2) {
            DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE * 2.5  , LARGEUR1CASE * 2.5  ,
                          YELLOW);
        }
        if (map[i][j].stade >= 3) {
            mapPosition.y = 50;
            DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE * 2.5, LARGEUR1CASE * 2.5,
                          BLUE);
        }

    } else if (map[i][j].etat == 2) {
        DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE * 3.5, LARGEUR1CASE * 5.5, YELLOW);
    } else if (map[i][j].etat == 3) {
        DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE, LARGEUR1CASE, BLUE);
    }
}

void HUDcollision(HUD hud[6],Rectangle HUD,Vector2 mousePosition,int collisionHUD,int i){
    DrawRectangleLines(HUD.x, HUD.y, HUD.width, HUD.height, BLUE);
    collisionHUD = CheckCollisionPointRec(mousePosition, HUD);
    if (collisionHUD != 0) {
        DrawRectangle(HUD.x, HUD.y, HUD.width, HUD.height, BLUE);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            hud[i].etat = 1;
            remiseZero(hud, i);

        }
    }
}

void MapCollision(Map map[45][35],HUD hud[6],Vector2 mapPosition,Vector2 mapSize,Vector2 mousePosition,Rectangle MAP,int collisionMAP,int i,int j){
    collisionMAP = CheckCollisionPointRec(mousePosition, MAP);
    if (collisionMAP != 0) {
        DrawRectangle(mapPosition.x,mapPosition.y, LARGEUR1CASE,LARGEUR1CASE, RED);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            for (int k = 0; k < 6; k++) {
                if (hud[1].etat == 1 && map[i][j].occupe == 0 && map[i - 1][j + 1].occupe == 0 &&
                    map[i - 1][j - 1].occupe == 0 && map[i + 1][j + 1].occupe == 0 && map[i + 1][j - 1].occupe == 0) {
                    for (int a = -1; a < 2; a++) {
                        for (int b = -1; b < 2; b++) {
                            map[i ][j ].etat = 1;
                            map[i + a][j + b].occupe = 1;
                        }
                    }
                }
                if (hud[2].etat == 1 && map[i][j].occupe == 0 && map[i - 1][j + 1].occupe == 0 &&
                    map[i - 1][j - 1].occupe == 0 && map[i + 1][j + 1].occupe == 0 && map[i + 1][j - 1].occupe == 0) {
                    for (int a = -2; a < 3; a++) {
                        for (int b = -3; b < 4; b++) {
                            map[i ][j ].etat = 2;
                            map[i + a][j + b].occupe = 1;
                        }
                    }



                }
            }

        }
    }
}

void affichageInfo(int time){ //Temps, argent etc...
    DrawRectangleLines(10, 10, 100, 20, BLUE);
    DrawText(TextFormat("Time: %d", (time)), 20, 15, 10, BLACK);
}


void boucle(Map map[45][35],HUD hud[6],Vector2 mapPosition,Vector2 mapSize,Vector2 mousePosition,int evolution,int time,int collisionHUD,int collisionMAP) {

    Rectangle HUD = initialisationHUD();
    Rectangle MAP = initialisationMAP();

    while (!WindowShouldClose()) {
        time = GetTime();
        evolution = temps(map, evolution, time);
        for (int i = 0; i < 45; i++) { // Evolution
            for (int j = 0; j < 35; j++) {
                if (evolution == 1 && map[i][j].stade < 3 && map[i][j].etat == 1) {
                    map[i][j].stade++;
                }

            }
        }
        evolution = 0;

        mousePosition = GetMousePosition();
        BeginDrawing();

        ClearBackground(RAYWHITE); //Fond Blanc

        for (int i = 0; i < 45; i++) {
            for (int j = 0; j < 35; j++) {
                mapPosition.x = i * LARGEUR1CASE + LARGEUR1CASE*11; //Coordonnée de la map
                mapPosition.y = j * LARGEUR1CASE + LARGEUR1CASE*6;
                MAP.x = i * LARGEUR1CASE + LARGEUR1CASE*11; //Coordonnée de la map
                MAP.y = j * LARGEUR1CASE + LARGEUR1CASE*6;
                dessinerMap(mapPosition,i,j);
                MapCollision(map,hud,mapPosition,mapSize,mousePosition,MAP,collisionMAP,i,j);
                placementBatiment(map,mapPosition,i,j);
            }
        }

        for (int i = 0; i < 6; i++) { //Dessin du HUD
            HUD.y = 50 + 50 * i;
            HUDcollision(hud,HUD,mousePosition,collisionHUD,i);
        }
        affichageInfo(time);


        EndDrawing();

    }
    CloseWindow();
}