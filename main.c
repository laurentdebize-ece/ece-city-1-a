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

    DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur, tailleCaseHauteur, GRAY);

}

void placementBatiment(Map map[45][35],Vector2 mapPosition,int i,int j){
    if (map[i][j].etat == 0) {  //Quoi faire en fonction de l'etat de la case (voir map.h)
        DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur, tailleCaseHauteur, BLACK);
    }
    else if (map[i][j].etat == 1) { //Evolution des maisons
        if (map[i][j].stade == 0) {
            DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur * 2.5 , tailleCaseHauteur * 2.5  , RED);
        }
        if (map[i][j].stade == 1) {
            DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur * 2.5  , tailleCaseHauteur * 2.5  ,
                     GREEN);
        }
        if (map[i][j].stade == 2) {
            DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur * 2.5  , tailleCaseHauteur * 2.5  ,
                     YELLOW);
        }
        if (map[i][j].stade >= 3) {
            mapPosition.y = 50;
            DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur * 2.5, tailleCaseHauteur * 2.5,
                     BLUE);
        }

    } else if (map[i][j].etat == 2) {
        DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur * 3.5, tailleCaseHauteur * 5.5, YELLOW);
    } else if (map[i][j].etat == 3) {
        DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur, tailleCaseHauteur, BLUE);
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
        DrawRectangle(mapPosition.x,mapPosition.y, tailleCaseLargeur,tailleCaseHauteur, RED);
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


void boucle(Map map[45][35],HUD hud[6],Vector2 mapPosition,Vector2 mapSize,Ray ray,Vector2 mousePosition,Rectangle HUD,Rectangle MAP,RayCollision collision,float x, float y, float z,int evolution,int time,int collisionHUD,int collisionMAP) {

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
                mapPosition.x = i * tailleCaseLargeur + tailleCaseLargeur*11; //Coordonnée de la map
                mapPosition.y = j * tailleCaseHauteur + tailleCaseHauteur*6;
                MAP.x = i * tailleCaseLargeur + tailleCaseLargeur*11; //Coordonnée de la map
                MAP.y = j * tailleCaseHauteur + tailleCaseHauteur*6;
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



int main(){
    Map map[45][35];
    HUD hud[6];
    initialiserMap(map,hud);
    InitWindow(LARGUEUR, HAUTEUR, "ECE city");
    float x = 0;
    float y = 176.875702;
    float z = 176.875687;
    int evolution = 0;
    int time;
    int collisionHUD;
    int collisionMAP;

    Vector2 mapPosition = { 0.0f, 0.0f };
    Vector2 mapSize = { tailleCaseLargeur,  tailleCaseHauteur };

    Ray ray = { 0 };
    Vector2 mousePosition = {0};
    Rectangle HUD = {10,50};
    Rectangle MAP = {tailleCaseLargeur*3,tailleCaseHauteur*3};// Pour la collision avec le HUD
    MAP.height=tailleCaseHauteur;
    MAP.width=tailleCaseLargeur;
    HUD.height=50;
    HUD.width=50;
    RayCollision collision = { 0 };

    SetTargetFPS(60);
    boucle(map,hud,mapPosition,mapSize,ray,mousePosition,HUD,MAP,collision,x,y,z,evolution,time,collisionHUD,collisionMAP);



}
