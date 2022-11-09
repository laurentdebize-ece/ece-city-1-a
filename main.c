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

void dessinerMap(Vector3 mapPosition,int i,int j){

    //DrawCube(carte,carteSize.x,carteSize.y,carteSize.z,GRAY);
    DrawCube(mapPosition, tailleCaseLargeur, 0.0f, tailleCaseHauteur, GRAY);

}

void collisionMap(Map map[45][35],HUD hud[6],Ray ray,Vector3 mapPosition,Vector3 mapSize,RayCollision collision,int i, int j){ //Collision Souris Map
    collision = GetRayCollisionBox(ray, (BoundingBox) {
            (Vector3) {mapPosition.x - mapSize.x / 2, 0, mapPosition.z - mapSize.z / 2},
            (Vector3) {mapPosition.x + mapSize.x / 2, 0, mapPosition.z + mapSize.z / 2}});
    if (collision.hit != 0) {
        DrawCube(mapPosition, tailleCaseLargeur, 0.0f, tailleCaseHauteur, RED);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            for (int k = 0; k < 6; k++) {
                if (hud[k].etat == 1 && map[i][j].occupe == 0 && map[i + 2][j + 2].occupe == 0 &&
                    map[i][j + 2].occupe == 0 && map[i + 2][j].occupe == 0) {
                    map[i][j].etat = k;
                    map[i][j].occupe = 1;
                    if (hud[1].etat == 1) {
                        for (int a = 0; a < 3; a++) {
                            for (int b = 0; b < 3; b++) {
                                map[i + a][j + b].etat = 1;
                                map[i + a][j + b].occupe = 1;
                            }
                        }
                    }

                }
            }

        }
    }
}

void placementBatiment(Map map[45][35],Vector3 mapPosition,int i,int j){
    if (map[i][j].etat == 0) {  //Quoi faire en fonction de l'etat de la case (voir map.h)
        DrawCube(mapPosition, tailleCaseLargeur, 0.0f, tailleCaseHauteur, BLACK);
    }
    else if (map[i][j].etat == 1) { //Evolution des maisons
        if (map[i][j].stade == 0) {
            DrawCube(mapPosition, tailleCaseLargeur * 3 / 2, 2.0f, tailleCaseHauteur / 1.2 * 3 / 2, RED);
        }
        if (map[i][j].stade == 1) {
            DrawCube(mapPosition, tailleCaseLargeur / 1.2 * 3 / 2, 20.0f, tailleCaseHauteur / 1.2 * 3 / 2,
                     GREEN);
        }
        if (map[i][j].stade >= 2) {
            DrawCube(mapPosition, tailleCaseLargeur / 1.2 * 3 / 2, 200.0f, tailleCaseHauteur / 1.2 * 3 / 2,
                     BLUE);
        }

    } else if (map[i][j].etat == 2) {
        DrawCube(mapPosition, tailleCaseLargeur, 0.0f, tailleCaseHauteur, BLUE);
    } else if (map[i][j].etat == 3) {
        DrawCube(mapPosition, tailleCaseLargeur, 0.0f, tailleCaseHauteur, GREEN);
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

void affichageInfo(int time){ //Temps, argent etc...
    DrawRectangleLines(10, 10, 100, 20, BLUE);
    DrawText(TextFormat("Time: %d", (time)), 20, 15, 10, BLACK);
}


void boucle(Map map[45][35],HUD hud[6],Camera3D camera,Vector3 mapPosition,Vector3 mapSize,Ray ray,Vector2 mousePosition,Rectangle HUD,RayCollision collision,float x, float y, float z,int evolution,int time,int collisionHUD) {

    while (!WindowShouldClose()) {
        time = GetTime();
        evolution = temps(map, evolution, time);
        for (int i = 0; i < 45; i++) { // Evolution
            for (int j = 0; j < 35; j++) {
                if (evolution == 1 && map[i][j].stade < 3 && map[i][j].etat == 1) {
                    map[i][j].stade++;
                    printf("%d\n", map[i][j].stade);
                }

            }
        }
        evolution = 0;

        UpdateCamera(&camera); // Système de camera de base de Raylib
        ray = GetMouseRay(GetMousePosition(), camera);
        mousePosition = GetMousePosition();
        BeginDrawing();

        ClearBackground(RAYWHITE); //Fond Blanc

        if (IsKeyDown(KEY_LEFT)) { //Deplacement de la camera aussi possible avec ALt + mouseWheelPressed
            x--;
            camera.target = (Vector3) {x, y, z};
        }
        if (IsKeyDown(KEY_RIGHT)) {
            x++;
            camera.target = (Vector3) {x, y, z};
        }
        if (IsKeyDown(KEY_UP)) {
            z--;
            camera.target = (Vector3) {x, y, z};
        }
        if (IsKeyDown(KEY_DOWN)) {
            z++;
            camera.target = (Vector3) {x, y, z};
        }

        BeginMode3D(camera);
        for (int i = 0; i < 45; i++) {
            for (int j = 0; j < 35; j++) {
                mapPosition.x = i * tailleCaseLargeur; //Coordonnée de la map
                mapPosition.z = j * tailleCaseHauteur;
                dessinerMap(mapPosition,i,j);
                collisionMap(map,hud,ray,mapPosition,mapSize,collision,i,j);
                placementBatiment(map,mapPosition,i,j);
            }
        }
        EndMode3D();

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

    Camera3D camera = { 0 };
    camera.position = (Vector3){ x, y, z };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 5.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 mapPosition = { 0.0f, 0.0f, 0.0f };
    Vector3 mapSize = { tailleCaseLargeur, 0.0f, tailleCaseHauteur };

    Ray ray = { 0 };
    Vector2 mousePosition = {0};
    Rectangle HUD = {10,50}; // Pour la collision avec le HUD
    HUD.height=50;
    HUD.width=50;
    RayCollision collision = { 0 };


    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);
    boucle(map,hud,camera,mapPosition,mapSize,ray,mousePosition,HUD,collision,x,y,z,evolution,time,collisionHUD);



}
