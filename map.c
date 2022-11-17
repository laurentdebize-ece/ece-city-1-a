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
            map[i][j].occupe = 0;
            map[i][j].habitation.id = 0;
            map[i][j].route = 0;
            map[i][j].habitation.viable = 1;
            map[i][j].habitation.evolution = 0;
            map[i][j].habitation.tempsFuturEvolution = 5;
            map[i][j].habitation.nombreHabitants = 0;
            map[0][0].idHabitation = 0;
            map[0][0].idCentrale = 0;
            map[0][0].nombreTotalHabitant = 0;
            map[i][j].centrale.id = 0;

        }
    }
}

Rectangle initialisationCaseMAP(){
    Rectangle MAP;

    MAP.x = POSITIONMAP_X;
    MAP.y = POSITIONMAP_Y;
    MAP.height=LARGEUR1CASE;
    MAP.width=LARGEUR1CASE;

    return MAP;
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
                case 2:{
                    DrawRectangle(caseMAP.x,caseMAP.y, 4 * LARGEUR1CASE,6 * LARGEUR1CASE, YELLOW);
                    break;
                }
            }
        }
    }
}

void placementElement(Vector2 mouseposition, Rectangle caseMAP, MAP map[45][35], HUD hud[NOMBRE_CASE_HUD], HABITATION habitation[NOMBRE_HABITATION_MAX], CENTRALE centrale[NOMBRE_CENTRALE_MAX]){
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
                        if (i < 45 - 2 && j < 35 - 2){
                        if (hud[1].etat == 1 && testMapOccupation(i, j, map, Habitation) == 1) {//conditions sur i et j sinon maison sort de la map
                            map[0][0].idHabitation++;
                            for (int a = 0; a < 3; a++) {
                                for (int b = 0; b < 3; b++) {
                                    map[i + a][j + b].occupe = 1;
                                    map[i][j].habitation.id = map[0][0].idHabitation;
                                    habitation[map[0][0].idHabitation].positionX = i;
                                    habitation[map[0][0].idHabitation].positionY = j;
                                    habitation[map[0][0].idHabitation].evolution = 0;
                                    habitation[map[0][0].idHabitation].compteurEvolution = 0;
                                }
                            }
                            }
                        }
                        if (i < 45 - 3 && j < 35 - 5) {
                            if (hud[2].etat == 1 && testMapOccupation(i, j, map, Centrale) == 1 ) { //conditions sur i et j sinon centrale sort de la map
                                map[0][0].idCentrale++;
                                for (int a = 0; a < 4; a++) {
                                    for (int b = 0; b < 6; b++) {
                                        map[i + a][j + b].occupe = 1;
                                        map[i][j].centrale.id = map[0][0].idCentrale;
                                        centrale[map[0][0].idCentrale].positionX = i;
                                        centrale[map[0][0].idCentrale].positionY = j;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void habitationViableElec(MAP map[45][35]){

    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if(map[0][0].nombreTotalHabitant > map[0][0].idCentrale * 5000){
                map[i][j].habitation.viable = 0;
            }
            else if(map[0][0].nombreTotalHabitant < map[0][0].idCentrale * 5000){
                map[i][j].habitation.viable = 1;
            }

        }
    }

}


void evolution(MAP map[45][35]){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id!=0 && map[i][j].habitation.evolution<4 && map[i][j].habitation.viable==1){
                map[i][j].habitation.compteurEvolution++;
                if ((map[i][j].habitation.compteurEvolution/60)==map[i][j].habitation.tempsFuturEvolution && map[i][j].habitation.compteurEvolution!=map[i][j].habitation.tempsBanni){
                    map[i][j].habitation.tempsFuturEvolution=map[i][j].habitation.tempsFuturEvolution+5;
                    map[i][j].habitation.tempsBanni=map[i][j].habitation.compteurEvolution;
                    map[i][j].habitation.evolution++;
                }

            }
            if(map[i][j].habitation.evolution == 0){
                map[i][j].habitation.nombreHabitants = 0;

            }
            if(map[i][j].habitation.evolution == 1){
                map[i][j].habitation.nombreHabitants = 10;
            }
            if(map[i][j].habitation.evolution == 2){
                map[i][j].habitation.nombreHabitants = 50;
            }
            if(map[i][j].habitation.evolution == 3){
                map[i][j].habitation.nombreHabitants = 100;
            }
            if(map[i][j].habitation.evolution == 4){
                map[i][j].habitation.nombreHabitants = 1000;
            }

        }
    }
}

void dessinerElement(MAP map[45][35]){ //Ajouter une condition pour les différents niveaux (0 1 2)
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if(map[i][j].habitation.id != 0){
                if (map[i][j].habitation.evolution==TERRAIN_VAGUE){
                    DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, 3 * LARGEUR1CASE, 3 * LARGEUR1CASE, GREEN);
                }
                if (map[i][j].habitation.evolution==CABANE){
                    DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, 3 * LARGEUR1CASE, 3 * LARGEUR1CASE, RED);
                }
                if (map[i][j].habitation.evolution==MAISON){
                    DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, 3 * LARGEUR1CASE, 3 * LARGEUR1CASE, VIOLET);
                }
                if (map[i][j].habitation.evolution==IMMEUBLE){
                    DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, 3 * LARGEUR1CASE, 3 * LARGEUR1CASE, BLUE);
                }
                if (map[i][j].habitation.evolution==GRATTE_CIEL){
                    DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, 3 * LARGEUR1CASE, 3 * LARGEUR1CASE, PINK);
                }
            }
            if (map[i][j].route == 1){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, BLACK);
            }
            if(map[i][j].centrale.id != 0){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, 4 * LARGEUR1CASE, 6 * LARGEUR1CASE, YELLOW);

            }
        }
    }
}

void nombreHabitant(MAP map[45][35]){
    int habitantTotal = 0;
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id != 0){
                habitantTotal = habitantTotal + map[i][j].habitation.nombreHabitants;
        }
        }
    }
    map[0][0].nombreTotalHabitant = habitantTotal;
}

void mapNiveau0(MAP map[45][35], HUD hud[NOMBRE_CASE_HUD], HABITATION habitation[NOMBRE_HABITATION_MAX], CENTRALE centrale[NOMBRE_CENTRALE_MAX], INFO infoPerm){

    Vector2 mapPosition = initialisationPositionMap();

    Rectangle HUD[NOMBRE_CASE_HUD];
    initialisationCaseHUD(HUD);
    Rectangle caseMAP = initialisationCaseMAP();

    float lifetime = 1.0f;
    Timer timer = {0};
    StartTimer(&timer, lifetime);

    Vector2 mouseposition = {0};

    while(!WindowShouldClose()){
        infoPerm.time = GetTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (TimerDone(timer)){ //Fonction execute toute les 1 seconde
            StartTimer(&timer, lifetime);

        }
        mouseposition = GetMousePosition();

        dessinerHUD(HUD); //Dessine les cases de la boite à outil
        HUDcollision(hud, HUD, mouseposition); //Test si surpassage de case et si clic dans une des cases
        nombreHabitant(map);
        habitationViableElec(map);
        dessinerMap(mapPosition); //Dessine le fond de map (possibilité de changer la texture de la map)
        evolution(map);
        placementElement(mouseposition, caseMAP, map, hud, habitation, centrale);
        dessinerElement(map); //Dessine toutes les maisons enregistrées en mémoire
        affichageInfo(infoPerm); //Affichage informations de la partie


        EndDrawing();
    }

    CloseWindow();


}

