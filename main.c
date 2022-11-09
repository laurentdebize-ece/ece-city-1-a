#include "map.h"


void initialiserMap(Map map[45][30],HUD hud[6]){

    for (int i=0;i<45;i++){
        for (int j=0;j<30;j++){
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


void affichage(Map map[45][30],HUD hud[6])
{
    const int width = 800;
    const int height = 450;
    int tailleH=(height)/6;
    int tailleW=(width)/9;
    int H=(height-2*tailleH)/30; //Distance entre le centre de deux carré adjacent de la map
    int W=(width-2*tailleW)/45; //Distance entre le centre de deux carré adjacent de la map

    InitWindow(width, height, "ECE city");
    float distance = 250.14f;
    float angleVert = 45.0f;
    float angleHorizon = 90.0f;
    float distanceHorizon = distance * cosf(angleVert * PI / 180.0f);
    float x = distanceHorizon* cosf(angleHorizon * PI / 180.0f);;
    float y = distance * sinf(angleVert * PI / 180.0f);;
    float z = distanceHorizon * sinf(angleHorizon * PI / 180.0f);
    int collisionHUD;
    int time;
    int evolution=0; //Evoltion prochaine des maisons
    int tempsBanni=0; //Temps deja utilsé pour l'evolution (pour eviter d'boluer plusieurs fois au meme moment)

    Camera3D camera = { 0 };
    camera.position = (Vector3){ x, y, z };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 5.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f }; // Dalle de la map
    Vector3 cubeSize = { W, 0.0f, H };
    Vector3 carte = { width/2, 0.0f, height/2 };
    Vector3 carteSize = { width, 0.0f, height};

    Ray ray = { 0 };
    Vector2 mousePosition = {0};
    Rectangle HUD = {10,50}; // Pour la collsion avec le HUD
    HUD.height=50;
    HUD.width=50;
    RayCollision collision = { 0 };

    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);



    while (!WindowShouldClose())
    {

        if (time%15==0 && time!=tempsBanni){ //Savoir si temps est un multipke de 15 pour l'evolution
            evolution=1;
            tempsBanni=time;
        }
        for (int i=0;i<45;i++){ // Evolution
            for (int j=0;j<30;j++){
                if (evolution==1 && map[i][j].stade<3 && map[i][j].etat==1){
                    map[i][j].stade++;
                    printf("%d\n",map[i][j].stade);
                }

            }
        }
        evolution=0;

        UpdateCamera(&camera); // Système de camera de base de Raylib
        ray = GetMouseRay(GetMousePosition(), camera);
        mousePosition = GetMousePosition();
        BeginDrawing();

        ClearBackground(RAYWHITE);
        if (IsKeyDown(KEY_LEFT)){ //Deplacement de la camera aussi possible avec ALt + mouseWheelPressed
            x--;
            camera.target = (Vector3){ x, y, z };
        }
        if (IsKeyDown(KEY_RIGHT)){
            x++;
            camera.target = (Vector3){ x, y, z };
        }
        if (IsKeyDown(KEY_UP)){
            z--;
            camera.target = (Vector3){ x, y, z };
        }
        if (IsKeyDown(KEY_DOWN)){
            z++;
            camera.target = (Vector3){ x, y, z };
        }
        BeginMode3D(camera);
        for (int i=0;i<45;i++){
            for(int j=0;j<30;j++){
                cubePosition.x=i*W; //Coordonnée de la map
                cubePosition.z=j*H;
                //DrawCube(carte,carteSize.x,carteSize.y,carteSize.z,GRAY);


                    DrawCube(cubePosition, W, 0.0f, H, GRAY);

                collision = GetRayCollisionBox(ray,(BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, 0, cubePosition.z - cubeSize.z/2 },
                                                                 (Vector3){ cubePosition.x + cubeSize.x/2, 0, cubePosition.z + cubeSize.z/2 }});
                if (collision.hit!=0){
                    DrawCube(cubePosition,W,0.0f,H,RED);
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                        for (int k=0;k<6;k++) {
                            if (hud[k].etat == 1 && map[i][j].occupe==0 && map[i+2][j+2].occupe==0 && map[i][j+2].occupe==0 && map[i+2][j].occupe==0) {
                                map[i][j].etat = k;
                                map[i][j].occupe = 1;
                                if (hud[1].etat==1){
                                    for (int a=0;a<3;a++){
                                        for (int b=0;b<3;b++){
                                            map[i+a][j+b].etat = 1;
                                            map[i+a][j+b].occupe = 1;
                                        }
                                    }
                                }

                            }
                        }

                    }
                }
                if (map[i][j].etat==0){  //Quoi faire en fonction de l'etat de la case (voir map.h)
                    DrawCube(cubePosition,W,0.0f,H,BLACK);
                }
                else if (map[i][j].etat==1){ //Evolution des maisons
                    if (map[i][j].stade==0){
                        DrawCube(cubePosition,W*3/2,2.0f,H/1.2*3/2,RED);
                    }
                    if (map[i][j].stade==1){
                        DrawCube(cubePosition,W/1.2*3/2,20.0f,H/1.2*3/2,GREEN);
                    }
                    if (map[i][j].stade>=2){
                        DrawCube(cubePosition,W/1.2*3/2,200.0f,H/1.2*3/2,BLUE);
                    }

                }
                else if (map[i][j].etat==2){
                    DrawCube(cubePosition,W,0.0f,H,BLUE);
                }
                else if (map[i][j].etat==3){
                    DrawCube(cubePosition,W,0.0f,H,GREEN);
                }

            }
        }
        EndMode3D();

        for (int i=0;i<6;i++){ //Dessin du HUD
            HUD.y=50+50*i;
            DrawRectangleLines( HUD.x, HUD.y, HUD.width, HUD.height, BLUE);
            collisionHUD = CheckCollisionPointRec(mousePosition,HUD);
            if (collisionHUD != 0){
                DrawRectangle( HUD.x, HUD.y, HUD.width, HUD.height, BLUE);
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    hud[i].etat=1;
                    remiseZero(hud,i);

                }
            }
        }
        DrawRectangleLines( 10, 10, 100, 20, BLUE);
        time = GetTime();
        DrawText(TextFormat("Time %d", (time)), 20, 15, 10, BLACK);

        EndDrawing();

    }

    CloseWindow();


}

int main(){
    Map map[45][30];
    HUD hud[6];
    initialiserMap(map,hud);
    affichage(map,hud);
}
