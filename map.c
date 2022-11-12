#include "map.h"

Vector2 initialisationMap(){
    Vector2 mapPosition;

    mapPosition.x = POSITIONMAP_X;
    mapPosition.y = POSITIONMAP_Y;

    return mapPosition;
}

void initialiserMap(MAP map[45][35],HUD hud[6]){

    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            map[i][j].occupe == NONOCCUPE;
            map[i][j].habitation.id = 0;
            map[i][j].route = 0;

        }
    }


    for (int i=0;i<45;i++){
        for (int j=0;j<35;j++){
            map[i][j].occupe=0;
        }
    }
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

void dessinerMap(Vector2 mapPosition){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            DrawRectangle((int)mapPosition.x + i * LARGEUR1CASE,(int)mapPosition.y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, GRAY);
        }
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

void affichageInfo(int time){ //Temps, argent etc...
    DrawRectangleLines(10, 10, 100, 20, BLUE);
    DrawText(TextFormat("Time: %d", (time)), 20, 15, 10, BLACK);
}

int testMapOccupation(int i, int j, MAP map[45][35], int type){ //type habitation,central,...
    switch (type) {
        case Route:{
            if (map[i][j].occupe == 1){
                return 0;
            }
            return 1;
        }
        case Habitation:{
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (map[i + k][j + l].occupe == 1){
                        return 0;
                    }
                }
            }
            return 1;
        }
    }
    return 1;
}

void dessinerSurPassage(Rectangle caseMAP, HUD hud[NOMBRE_CASE_HUD]){
    DrawRectangle(caseMAP.x,caseMAP.y, LARGEUR1CASE,LARGEUR1CASE, RED);
    for (int k = 0; k < NOMBRE_CASE_HUD; k++) {
        if (hud[k].etat == 1){
            switch (k) {
                case 0:{
                    DrawRectangle(caseMAP.x,caseMAP.y, LARGEUR1CASE,LARGEUR1CASE, BLACK);
                    break;
                }
                case 1:{
                    DrawRectangle(caseMAP.x,caseMAP.y, 3 * LARGEUR1CASE,3 * LARGEUR1CASE, GREEN);
                    break;
                }
            }
        }
    }
}

void placementElement(Vector2 mouseposition, Rectangle caseMAP, MAP map[45][35], HUD hud[NOMBRE_CASE_HUD]){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            caseMAP.x = POSITIONMAP_X + LARGEUR1CASE * i;
            caseMAP.y = POSITIONMAP_Y + LARGEUR1CASE * j;
            if (CheckCollisionPointRec(mouseposition, caseMAP)){

                dessinerSurPassage(caseMAP, hud);

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    for (int k = 0; k < 6; k++) {
                        if (hud[0].etat == 1 && testMapOccupation(i, j, map, Route)) { //conditions sur i et j sinon maison sort de la map
                            map[i][j].occupe = 1;
                            map[i][j].route = 1;
                        }
                        if (hud[1].etat == 1 && testMapOccupation(i, j, map, Habitation) == 1 && i < 43 && j < 33) { //conditions sur i et j sinon maison sort de la map
                            for (int a = 0; a < 3; a++) {
                                for (int b = 0; b < 3; b++) {
                                    map[i + a][j + b].occupe = 1;
                                    map[i][j].habitation.id = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void dessinerHUD(Rectangle HUD){
    for (int i = 0; i < 6; i++) {
        DrawRectangleLines((int)HUD.x, (int)HUD.y + (int)HUD.height * i, (int)HUD.width, (int)HUD.height, BLUE);
    }
}

void dessinerElement(MAP map[45][35]){ //Ajouter une condition pour les différents niveaux (0 1 2)
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if(map[i][j].habitation.id != 0){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, 3 * LARGEUR1CASE, 3 * LARGEUR1CASE, GREEN);
            }
            if (map[i][j].route == 1){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, BLACK);
            }
        }
    }
}

void mapNiveau0(MAP map[45][35], HUD hud[NOMBRE_CASE_HUD]){

    Vector2 mapPosition = initialisationMap();

    Rectangle HUD = initialisationHUD();
    Rectangle caseMAP = initialisationCaseMAP();

    int time;

    Vector2 mouseposition = {0};

    while(!WindowShouldClose()){
        time = GetTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        mouseposition = GetMousePosition();

        dessinerHUD(HUD); //Dessine les cases de la boite à outil
        HUDcollision(hud, HUD, mouseposition); //Test si surpassage de case et si clic dans une des cases
        dessinerMap(mapPosition); //Dessine le fond de map (possibilité de changer la texture de la map)
        placementElement(mouseposition, caseMAP, map, hud);
        dessinerElement(map); //Dessine toutes les maisons enregistrées en mémoire
        affichageInfo(time); //Affichage informations de la partie

        EndDrawing();
    }

    CloseWindow();


}

