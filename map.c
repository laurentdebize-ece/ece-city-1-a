#include "map.h"

Vector2 initialisationPositionMap(){
    Vector2 mapPosition;

    mapPosition.x = POSITIONMAP_X;
    mapPosition.y = POSITIONMAP_Y;

    return mapPosition;
}

void initialisationMap(MAP map[45][35]){

    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            map[i][j].occupe = NONOCCUPE;
            map[i][j].habitation.id = 0;
            map[i][j].route = 0;

        }
    }

    for (int i=0;i<45;i++){
        for (int j=0;j<35;j++){
            map[i][j].occupe=0;
        }
    }
}

void dessinerMap(Vector2 mapPosition){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            DrawRectangle((int)mapPosition.x + i * LARGEUR1CASE,(int)mapPosition.y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, GRAY);
        }
    }
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
        case Centrale:{
            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 6; l++) {
                    if (map[i + k][j + l].occupe == 1){
                        return 0;
                    }
                }
            }
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

void evolutionElement(MAP map[45][35]){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.viable == 1){

            }
        }
    }
}

void placementElement(Vector2 mouseposition, Rectangle caseMAP, MAP map[45][35], HUD hud[NOMBRE_CASE_HUD], HABITATION habitation[NOMBRE_HABITATION_MAX], int IDHabitation){
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
                        if (hud[1].etat == 1 && testMapOccupation(i, j, map, Habitation) == 1 && i < 45 - 2 && j < 35 - 2) { //conditions sur i et j sinon maison sort de la map
                            for (int a = 0; a < 3; a++) {
                                for (int b = 0; b < 3; b++) {
                                    map[i + a][j + b].occupe = 1;
                                    map[i][j].habitation.id = 1;
                                    habitation[IDHabitation].positionX = i;
                                    habitation[IDHabitation].positionY = j;
                                    habitation[IDHabitation].viable = 0;
                                    habitation[IDHabitation].evolution = 0;
                                    habitation[IDHabitation].compteur = 0;
                                }
                            }
                        }
                        if (hud[1].etat == 1 && testMapOccupation(i, j, map, Centrale) == 1 && i < 45 - 3 && j < 35 - 5) { //conditions sur i et j sinon centrale sort de la map
                            for (int a = 0; a < 4; a++) {
                                for (int b = 0; b < 6; b++) {
                                    map[i + a][j + b].occupe = 1;
                                    //...
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


void evolution(MAP map[45][35],Timer timer,float lifetime){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id==1 && map[i][j].habitation.evolution<4){
                if (TimerDone(timer)) { //Fonction execute toute les 1 seconde
                    StartTimer(&timer,lifetime);
                    map[i][j].habitation.evolution++;
                    printf("r");
                }//Savoir si temps est un multiple de 15 pour l'evolution
                }

            }
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

void mapNiveau0(MAP map[45][35], HUD hud[NOMBRE_CASE_HUD], HABITATION habitation[NOMBRE_HABITATION_MAX], CENTRALE centrale[NOMBRE_CENTRALE_MAX]){

    int lastID_habitation = 0;

    Vector2 mapPosition = initialisationPositionMap();

    Rectangle HUD = initialisationCaseHUD();
    Rectangle caseMAP = initialisationCaseMAP();

    int time;

    float lifetime = 1.0f;
    Timer timer = {0};
    StartTimer(&timer, lifetime);

    Vector2 mouseposition = {0};

    while(!WindowShouldClose()){
        time = GetTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (TimerDone(timer)){ //Fonction execute toute les 1 seconde
            StartTimer(&timer, lifetime);

        }
        mouseposition = GetMousePosition();

        dessinerHUD(HUD); //Dessine les cases de la boite à outil
        HUDcollision(hud, HUD, mouseposition); //Test si surpassage de case et si clic dans une des cases
        evolution(map,timer,lifetime);
        dessinerMap(mapPosition); //Dessine le fond de map (possibilité de changer la texture de la map)
        placementElement(mouseposition, caseMAP, map, hud, habitation, lastID_habitation++);
        dessinerElement(map); //Dessine toutes les maisons enregistrées en mémoire
        affichageInfo(time); //Affichage informations de la partie

        EndDrawing();
    }

    CloseWindow();


}

