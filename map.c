#include "map.h"

//

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
            map[i][j].type = 0;
            map[i][j].route.id = 0;
            map[i][j].route.visite = 0;
            map[i][j].route.color = BLACK;
            map[i][j].habitation.viable = 0;
            map[i][j].habitation.evolution = 0;
            map[i][j].habitation.tempsFuturEvolution = 5;
            map[i][j].habitation.tempsFuturArgent = 5;
            map[i][j].habitation.nombreHabitants = 0;
            map[i][j].habitation.visite = 0;
            map[0][0].idHabitation = 0;
            map[0][0].idCentrale = 0;
            map[0][0].idChateauEau = 0;
            map[0][0].nombreTotalHabitant = 0;
            map[i][j].centrale.id = 0;
            map[i][j].chateaueau.id = 0;
            map[i][j].habitation.connex = 0;
            map[i][j].habitation.elec = 1;
            map[i][j].habitation.eau = 1;

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

void initialiserGraphe(Graphe *g, TAB_GRAPHE tabGraphe[NOMBRE_ARETES_TABGRAPHE]){
    g->orientation = 0;
    g->ordre = 0;
    g->taille = 0;

    for (int i = 0; i < NOMBRE_ARETES_TABGRAPHE; i++) {
        tabGraphe[i].s1 = 0;
        tabGraphe[i].s2 = 0;
        tabGraphe[i].valeur = 0;
        tabGraphe[i].last_id = 0;
    }
}


void dessinerMap(Vector2 mapPosition){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            DrawRectangle((int)mapPosition.x + i * LARGEUR1CASE,(int)mapPosition.y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, BEIGE);
            DrawRectangleLines((int)mapPosition.x + i * LARGEUR1CASE,(int)mapPosition.y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, BROWN);
        }
    }
}

void ecrireFichierTexte(int s1, int s2, int compteur, Graphe *g){
    FILE *ifs = fopen("..//graphe.txt", "w");
    int taille, orientation, ordre, valeur;
    int l1, l2, l3;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }
    fprintf(ifs, "%d\n", g->ordre);

    fprintf(ifs, "%d\n", g->taille);
    fprintf(ifs, "%d\n", g->orientation);

    for (int i = 0; i < g->taille; ++i) {
        fscanf(ifs, "%d%d%d", &l1, &l2, &l3);
    }

    fprintf(ifs, "%d %d %d\n", s1, s2, compteur);
    g->taille++;

    fclose(ifs);
}

int verifDoublonArete(TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE], int s1, int s2, int valeur, Graphe *g){
    for (int i = 0; i < tab_Graphe[0].last_id + 1; i++) {
        if ((tab_Graphe[i].s1 == s1 && tab_Graphe[i].s2 == s2) || (tab_Graphe[i].s1 == s2 && tab_Graphe[i].s2 == s1)){
            if (valeur <= tab_Graphe[i].valeur){
                tab_Graphe[i].valeur = valeur;
                return 0;
            }
        }
    }
    tab_Graphe[tab_Graphe[0].last_id].s1 = s1;
    tab_Graphe[tab_Graphe[0].last_id].s2 = s2;
    tab_Graphe[tab_Graphe[0].last_id].valeur = valeur;
    tab_Graphe[0].last_id += 1;
    g->taille++;
}

int verifNonAdjacentRouteMaison(MAP map[45][35], int x, int y, int numHabitation){
    if (map[x + 1][y].habitation.id == numHabitation || map[x - 1][y].habitation.id == numHabitation || map[x][y + 1].habitation.id == numHabitation || map[x][y - 1].habitation.id == numHabitation){
        return 0;
    }
    else{
        return 1;
    }
}

void parcourirRoute(MAP map[45][35], int x, int y, int compteur, int s1, Graphe *g, TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE], int numHabitation){
    for (int i = -1; i < 2; i++) {
        if ((x + i) > 0 && (x + i) < 45 && i != 0 && map[x + i][y].route.id == 1 && map[x + i][y].route.visite == 0 && verifNonAdjacentRouteMaison(map, x+i, y, numHabitation)){
            map[x + i][y].route.visite = 1;
            map[x + i][y].route.color = ORANGE;

            parcourirRoute(map,x + i, y, compteur+1, s1, g, tab_Graphe, numHabitation);
        }
        else if ((x + i) > 0 && (x + i) < 45 && i != 0 && map[x + i][y].habitation.id != s1 && map[x + i][y].habitation.id != 0){
            //printf("%d %d %d\n", s1, map[x + i][y].habitation.id, compteur);
            //ecrireFichierTexte(s1, map[x + i][y].habitation.id, compteur, g);
            //lireGraphe(s1, map[x + i][y].habitation.id, compteur, g);
            verifDoublonArete(tab_Graphe, s1, map[x + i][y].habitation.id, compteur, g);
        }
    }
    for (int i = -1; i < 2; i++) {
        if ((y + i) > 0 && (y + i) < 35 && i != 0 && map[x][y + i].route.id == 1 && map[x][y + i].route.visite == 0 && verifNonAdjacentRouteMaison(map, x, y+i, numHabitation)){
            map[x][y + i].route.visite = 1;
            map[x][y + i].route.color = ORANGE;

            parcourirRoute(map,x, y + i, compteur+1, s1, g, tab_Graphe, numHabitation);
        }
        else if ((y + i) > 0 && (y + i) < 35 && i != 0 && map[x][y + i].habitation.id != 0 && map[x][y + i].habitation.id != s1){
            //printf("%d %d %d\n", s1, map[x][y + i].habitation.id, compteur);
            //ecrireFichierTexte(s1, map[x][y + i].habitation.id, compteur, g);
            //lireGraphe(s1, map[x][y + i].habitation.id, compteur, g);
            verifDoublonArete(tab_Graphe, s1, map[x][y + i].habitation.id, compteur, g);
        }
    }
}

int validationParcourContourMaison(int k, int l){
    if (k == -1 && l == -1){
        return 0;
    }
    else if (k == -1 && l == 1){
        return 0;
    }
    else if (k == 1 && l == -1){
        return 0;
    }
    else if (k == 1 && l == 1){
        return 0;
    }
    else{
        return 1;
    }

}

void connexRoute(MAP map[45][35], Graphe *g, TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE]){
    for (int j = 0; j < 35; j++) {
        for (int i = 0; i < 45; i++) {
            if (map[i][j].habitation.id != 0 && map[i][j].habitation.visite == 0){
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        if (map[i + l][j + k].route.id == 1 && validationParcourContourMaison(k,l)){
                            map[i][j].habitation.connex = 1;
                            map[i+l][j+k].route.visite = 1;
                            map[i+l][j+k].route.color = ORANGE;
                            map[i][j].habitation.visite = 1;
                            parcourirRoute(map, i+l, j+k, 1, map[i][j].habitation.id, g, tab_Graphe, map[i][j].habitation.id);
                            for (int m = 0; m < 45; m++) {
                                for (int n = 0; n < 35; n++) {
                                    map[m][n].route.visite = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void habitationViable(MAP map[45][35]){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id!=0){
                if (map[i][j].habitation.elec == 1 && map[i][j].habitation.connex == 1){
                    map[i][j].habitation.viable = 1;
                }
                else {
                    map[i][j].habitation.viable = 0;
                }
            }
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
        case ChateauEau:{
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
    DrawRectangle(caseMAP.x,caseMAP.y, LARGEUR1CASE,LARGEUR1CASE, BROWN);
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
                case 3:{
                    DrawRectangle(caseMAP.x,caseMAP.y, 4 * LARGEUR1CASE,6 * LARGEUR1CASE, BLUE);
                    break;
                }
            }
        }
    }
}

void placementElement(Vector2 mouseposition, Rectangle caseMAP, MAP map[45][35], INFO *infoPerm,HUD hud[NOMBRE_CASE_HUD], HABITATION habitation[NOMBRE_HABITATION_MAX], CENTRALE centrale[NOMBRE_CENTRALE_MAX], Graphe *graphe, TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE]){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            caseMAP.x = POSITIONMAP_X + LARGEUR1CASE * i;
            caseMAP.y = POSITIONMAP_Y + LARGEUR1CASE * j;
            if (CheckCollisionPointRec(mouseposition, caseMAP)){

                dessinerSurPassage(caseMAP, hud);

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                    for (int k = 0; k < NOMBRE_CASE_HUD; k++) {
                        if (hud[0].etat == 1 && testMapOccupation(i, j, map, Route) && infoPerm->ECEFlouz >= infoPerm->prixRoute) { //conditions sur i et j sinon maison sort de la map
                            infoPerm->ECEFlouz = infoPerm->ECEFlouz - infoPerm->prixRoute;
                            map[i][j].occupe = 1;
                            map[i][j].route.id = 1;
                            connexRoute(map, graphe, tab_Graphe);
                        }
                        if (i < 45 - 2 && j < 35 - 2){
                            if (hud[1].etat == 1 && testMapOccupation(i, j, map, Habitation) == 1 && infoPerm->ECEFlouz >= infoPerm->prixHabitation) {//conditions sur i et j sinon maison sort de la ma
                                map[0][0].idHabitation++;
                                infoPerm->ECEFlouz = infoPerm->ECEFlouz - infoPerm->prixHabitation;
                                graphe->ordre++;
                                for (int a = 0; a < 3; a++) {
                                    for (int b = 0; b < 3; b++) {
                                        map[i + a][j + b].occupe = 1;
                                        map[i + a][j + b].habitation.id = map[0][0].idHabitation;
                                        map[i][j].type = Habitation;
                                        habitation[map[0][0].idHabitation].positionX = i;
                                        habitation[map[0][0].idHabitation].positionY = j;
                                        habitation[map[0][0].idHabitation].evolution = 0;
                                        habitation[map[0][0].idHabitation].compteurEvolution = 0;

                                        connexRoute(map, graphe, tab_Graphe);
                                    }
                                }
                            }
                        }

                        if (i < 45 - 3 && j < 35 - 5) {
                            if (hud[2].etat == 1 && testMapOccupation(i, j, map, Centrale) == 1 && infoPerm->ECEFlouz >= infoPerm->prixCentrale) { //conditions sur i et j sinon centrale sort de la map
                                map[0][0].idCentrale++;
                                infoPerm->ECEFlouz = infoPerm->ECEFlouz - infoPerm->prixCentrale;
                                graphe->ordre++;
                                for (int a = 0; a < 4; a++) {
                                    for (int b = 0; b < 6; b++) {
                                        map[i + a][j + b].occupe = 1;
                                        map[i+a][j+b].centrale.id = map[0][0].idCentrale;
                                        map[i][j].type = Centrale;
                                        centrale[map[0][0].idCentrale].positionX = i;
                                        centrale[map[0][0].idCentrale].positionY = j;

                                        connexRoute(map, graphe, tab_Graphe);
                                    }
                                }
                            }
                        }

                        if (i < 45 - 3 && j < 35 - 5) {
                            if (hud[3].etat == 1 && testMapOccupation(i, j, map, ChateauEau) == 1 && infoPerm->ECEFlouz >= infoPerm->prixChateauEau) { //conditions sur i et j sinon centrale sort de la map
                                map[0][0].idChateauEau++;
                                infoPerm->ECEFlouz = infoPerm->ECEFlouz - infoPerm->prixChateauEau;
                                graphe->ordre++;
                                for (int a = 0; a < 4; a++) {
                                    for (int b = 0; b < 6; b++) {
                                        map[i + a][j + b].occupe = 1;
                                        map[i][j].type = ChateauEau;
                                        map[i+a][j+b].chateaueau.id = map[0][0].idChateauEau;
                                        centrale[map[0][0].idChateauEau].positionX = i;
                                        centrale[map[0][0].idChateauEau].positionY = j;

                                        connexRoute(map, graphe, tab_Graphe);
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
                map[i][j].habitation.elec = 0;
            }
            else if(map[0][0].nombreTotalHabitant < map[0][0].idCentrale * 5000){
                map[i][j].habitation.elec = 1;
            }

        }
    }

}

void evolution(MAP map[45][35], INFO *infoPerm){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id != 0 && map[i][j].habitation.evolution < 4){
                map[i][j].habitation.compteurEvolution++;
                if ((map[i][j].habitation.compteurEvolution/60)==map[i][j].habitation.tempsFuturArgent && map[i][j].habitation.compteurEvolution!=map[i][j].habitation.tempsBanniArgent){
                    map[i][j].habitation.tempsFuturArgent=map[i][j].habitation.tempsFuturArgent+5;
                    map[i][j].habitation.tempsBanniArgent=map[i][j].habitation.compteurEvolution;

                    infoPerm->ECEFlouz = infoPerm->ECEFlouz + map[i][j].habitation.nombreHabitants * 10;
                }
                if (map[i][j].habitation.viable == 1){


                if ((map[i][j].habitation.compteurEvolution/60)==map[i][j].habitation.tempsFuturEvolution && map[i][j].habitation.compteurEvolution!=map[i][j].habitation.tempsBanniEvolution){
                    map[i][j].habitation.tempsFuturEvolution=map[i][j].habitation.tempsFuturEvolution+5;
                    map[i][j].habitation.tempsBanniEvolution=map[i][j].habitation.compteurEvolution;
                    map[i][j].habitation.evolution++;
                }
                for (int k = 0; k < 45; k++) {
                    for (int l = 0; l < 35; l++) {
                        if (map[k][l].habitation.id == map[i][j].habitation.id){
                            if (map[k][l].habitation.evolution < map[i][j].habitation.evolution){
                                map[k][l].habitation.evolution = map[i][j].habitation.evolution;
                                map[k][l].habitation.compteurEvolution = map[i][j].habitation.compteurEvolution;
                            }

                        }
                    }
                }
            }}
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

void dessinerElement(MAP map[45][35], Texture2D cabane, Texture2D maison, Texture2D immeuble, Texture2D gratteciel, Texture2D terrain){ //Ajouter une condition pour les différents niveaux (0 1 2)

    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if(map[i][j].type != 0){
                if (map[i][j].habitation.evolution==TERRAIN_VAGUE){
                    DrawTexture(terrain, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j *  LARGEUR1CASE, WHITE);
                }
                if (map[i][j].habitation.evolution==CABANE){

                    DrawTexture(cabane, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j *  LARGEUR1CASE, WHITE);

                    //DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, RED);
                }
                if (map[i][j].habitation.evolution==MAISON){

                    DrawTexture(maison, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);
                    //DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, VIOLET);
                }
                if (map[i][j].habitation.evolution==IMMEUBLE){

                    DrawTexture(immeuble, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);
                    //DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, BLUE);
                }
                if (map[i][j].habitation.evolution==GRATTE_CIEL){

                    DrawTexture(gratteciel, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);
                    //DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, PINK);
                }

            }
            if (map[i][j].route.id == 1){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, map[i][j].route.color);
            }
            if(map[i][j].centrale.id != 0){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, YELLOW);

            }
            if(map[i][j].chateaueau.id != 0){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, BLUE);

            }
        }
    }
}

void nombreHabitant(MAP map[45][35]){
    int habitantTotal = 0;
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id != 0){
                habitantTotal = habitantTotal + map[i][j].habitation.nombreHabitants/9;
        }
        }
    }
    map[0][0].nombreTotalHabitant = habitantTotal;
}

void test(MAP map[45][35]){
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            map[9 + a][11 + b].occupe = 1;
            map[9 + a][11 + b].habitation.id = 1;
            map[9][11].type = Habitation;
        }
    }

    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            map[16 + a][9 + b].occupe = 1;
            map[16 + a][9 + b].habitation.id = 2;
            map[16][9].type = Habitation;
        }
    }
/*
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            map[16 + a][6 + b].occupe = 1;
            map[16 + a][6 + b].habitation.id = 3;
            map[16][6].type = Habitation;
        }
    }*/

    map[9][10].route.id = 1;
    map[10][10].route.id = 1;
    map[11][10].route.id = 1;
    map[12][10].route.id = 1;
    map[13][10].route.id = 1;
    map[14][10].route.id = 1;
    map[15][10].route.id = 1;
    /*
    map[15][12].route.id = 1;
    map[16][12].route.id = 1;
    map[16][13].route.id = 1;

    map[15][10].route.id = 1;
    map[15][9].route.id = 1;
    map[15][8].route.id = 1;
*/
}

void mapECECITY(MAP map[45][35], HUD hud[NOMBRE_CASE_HUD], HABITATION habitation[NOMBRE_HABITATION_MAX], CENTRALE centrale[NOMBRE_CENTRALE_MAX], INFO infoPerm){

    TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE];
    Graphe *graphe = CreerGraphe(0);
    initialiserGraphe(graphe, tab_Graphe);

    Vector2 mapPosition = initialisationPositionMap();

    Texture2D terrain;
    Texture2D cabane;
    Texture2D maison;
    Texture2D immeuble;
    Texture2D gratteciel;
    Texture2D fondmap;

    terrain = LoadTexture("../images/Constructions /terrainvague2.png");
    cabane = LoadTexture("../images/Constructions /cabane2.png");
    maison = LoadTexture("../images/Constructions /maison2.png");
    immeuble = LoadTexture("../images/Constructions /immeuble2.png");
    gratteciel = LoadTexture("../images/Constructions /gratteciel2.png");
    fondmap = LoadTexture("../images/Menu/fond.png");

    Rectangle HUD[NOMBRE_CASE_HUD];
    initialisationCaseHUD(HUD);
    Rectangle caseMAP = initialisationCaseMAP();

    float lifetime = 1.0f;
    Timer timer = {0};
    StartTimer(&timer, lifetime);

    Vector2 mouseposition = {0};

    //test(map);

    while(!WindowShouldClose()){
        infoPerm.time = GetTime();

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(fondmap, 0, 0, WHITE);

        if (TimerDone(timer)){ //Fonction execute toute les 1 seconde
            StartTimer(&timer, lifetime);

        }
        mouseposition = GetMousePosition();

        dessinerHUD(HUD); //Dessine les cases de la boite à outil
        HUDcollision(hud, HUD, mouseposition); //Test si surpassage de case et si clic dans une des cases

        //nombreHabitant(map);
        connexRoute(map, graphe, tab_Graphe);
        //habitationViableElec(map);
        //habitationViable(map);

        //Map

        dessinerMap(mapPosition); //Dessine le fond de map (possibilité de changer la texture de la map)
        evolution(map,&infoPerm);
        placementElement(mouseposition, caseMAP, map, &infoPerm, hud, habitation, centrale, graphe, tab_Graphe);
        for (int i = 0; i < 45; i++) {
            for (int j = 0; j < 35; j++) {
                map[i][j].habitation.visite = 0;
                map[i][j].route.visite = 0;
            }
        }
        dessinerElement(map,cabane,maison,immeuble,gratteciel,terrain); //Dessine toutes les maisons enregistrées en mémoire
        affichageInfo(&infoPerm); //Affichage informations de la partie

        if (IsKeyDown(KEY_A)){
            lireGraphe(tab_Graphe, graphe);
            graphe_afficher(graphe);
        }

        EndDrawing();
    }

    UnloadTexture(fondmap);
    UnloadTexture(cabane);
    UnloadTexture(maison);
    UnloadTexture(immeuble);
    UnloadTexture(gratteciel);

    CloseWindow();

    for (int i = 0; i < tab_Graphe[0].last_id; i++) {
        printf("%d %d %d\n", tab_Graphe[i].s1, tab_Graphe[i].s2, tab_Graphe[i].valeur);
    }

}

