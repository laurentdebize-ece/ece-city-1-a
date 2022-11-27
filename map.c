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
            map[i][j].type = 0;
            map[i][j].route.id = 0;
            map[i][j].route.visite = 0;
            map[i][j].route.color = BLACK;
            map[i][j].habitation.viable = 0;
            map[i][j].habitation.evolution = 0;
            map[i][j].habitation.tempsFuturEvolution = 15;
            map[i][j].habitation.tempsFuturArgent = 15;
            map[i][j].habitation.nombreHabitants = 0;
            map[i][j].habitation.centraleQuiAlimente = 0;
            map[i][j].habitation.visite = 0;
            map[0][0].id = 0;
            map[0][0].idHabitation = 0;
            map[0][0].idCentrale = 0;
            map[0][0].idChateauEau = 0;
            map[0][0].nombreTotalHabitant = 0;
            map[i][j].centrale.id = 0;
            map[i][j].centrale.visite = 0;
            map[i][j].chateaueau.id = 0;
            map[i][j].chateaueau.visite = 0;
            map[i][j].habitation.connex = 0;
            map[i][j].habitation.viableElec = 0;
            map[i][j].habitation.viableEau = 0;

            map[i][j].centrale.capacite = 5000; //test
            map[i][j].chateaueau.capacite = 5000;

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

void initialiserTABGRAPHE(TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE]){
    for (int i = 0; i < NOMBRE_ARETES_TABGRAPHE; i++) {
        tab_Graphe[i].s1 = 0;
        tab_Graphe[i].s2 = 0;
        tab_Graphe[i].valeur = 0;
        tab_Graphe[i].last_id = 0;
        tab_Graphe[i].type = 0;

    }
}

void initialiserGraphe(Graphe *g){
    g->orientation = 0;
    g->ordre = 0;
    g->taille = 0;
    for (int i = 0; i < NOMBRE_MAX_ELEMENT; i++) {
        g->pSommet[i]->type = 0;
        g->pSommet[i]->habitation.viableEau = 0;
        g->pSommet[i]->habitation.viableElec = 0;
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

int verifDoublonArete(TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE], int s1, int s2, int valeur){
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
}

int verifNonAdjacentRouteMaison(MAP map[45][35], int x, int y, int numHabitation){
    printf("%d", numHabitation);
    if (map[x + 1][y].habitation.id == numHabitation || map[x - 1][y].habitation.id == numHabitation || map[x][y + 1].habitation.id == numHabitation || map[x][y - 1].habitation.id == numHabitation){
        return 0;
    }
    else{
        return 1;
    }
}

void parcourirRoute(MAP map[45][35], int x, int y, int compteur, int s1, Graphe *g, TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE]){
    for (int i = -1; i < 2; i++) {
        if ((x + i) > 0 && (x + i) < 45 && i != 0 && map[x + i][y].route.id == 1 && map[x + i][y].route.visite == 0 && map[x + i + 1][y].habitation.id != s1 && map[x + i - 1][y].habitation.id != s1 && map[x][y + 1].habitation.id != s1 && map[x][y - 1].habitation.id != s1){
            map[x + i][y].route.visite = 1;
            map[x + i][y].route.color = ORANGE;

            parcourirRoute(map,x + i, y, compteur+1, s1, g, tab_Graphe);
        }
        else if ((x + i) > 0 && (x + i) < 45 && i != 0 && map[x + i][y].habitation.id != s1 && map[x + i][y].habitation.id != 0){
            //printf("%d %d %d\n", s1, map[x + i][y].habitation.id, compteur);
            //ecrireFichierTexte(s1, map[x + i][y].habitation.id, compteur, g);
            //lireGraphe(s1, map[x + i][y].habitation.id, compteur, g);
            verifDoublonArete(tab_Graphe, s1, map[x + i][y].habitation.id, compteur);
        }
        else if ((x + i) > 0 && (x + i) < 45 && i != 0 && map[x + i][y].centrale.id != 0){
            verifDoublonArete(tab_Graphe, s1, map[x + i][y].centrale.id, compteur);
        }
        else if ((x + i) > 0 && (x + i) < 45 && i != 0 && map[x + i][y].chateaueau.id != 0){
            verifDoublonArete(tab_Graphe, s1, map[x + i][y].chateaueau.id, compteur);
        }
    }
    for (int i = -1; i < 2; i++) {
        if ((y + i) > 0 && (y + i) < 35 && i != 0 && map[x][y + i].route.id == 1 && map[x][y + i].route.visite == 0 && map[x + 1][y].habitation.id != s1 && map[x - 1][y].habitation.id != s1 && map[x][y + i + 1].habitation.id != s1 && map[x][y + i - 1].habitation.id != s1){
            map[x][y + i].route.visite = 1;
            map[x][y + i].route.color = ORANGE;

            parcourirRoute(map,x, y + i, compteur+1, s1, g, tab_Graphe);
        }
        else if ((y + i) > 0 && (y + i) < 35 && i != 0 && map[x][y + i].habitation.id != s1 && map[x][y + i].habitation.id != 0){
            //printf("%d %d %d\n", s1, map[x][y + i].habitation.id, compteur);
            //ecrireFichierTexte(s1, map[x][y + i].habitation.id, compteur, g);
            //lireGraphe(s1, map[x][y + i].habitation.id, compteur, g);
            verifDoublonArete(tab_Graphe, s1, map[x][y + i].habitation.id, compteur);
        }
        else if ((y + i) > 0 && (y + i) < 35 && i != 0 && map[x][y + i].centrale.id != 0){
            verifDoublonArete(tab_Graphe, s1, map[x][y + i].centrale.id, compteur);
        }
        else if ((y + i) > 0 && (y + i) < 35 && i != 0 && map[x][y + i].chateaueau.id != 0){
            verifDoublonArete(tab_Graphe, s1, map[x][y + i].chateaueau.id, compteur);
            tab_Graphe[tab_Graphe[0].last_id-1].type=3;

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
                for (int k = 0; k < 3; k++) {
                    if ((i - 2)>=0 && (j - 2)<=45 && (i + 4)<=0 && (j + 4)>=35 &&map[i + k][j - 2].route.id == 1 && map[i + k][j - 2 + 1].route.id == 1){ //3 cases superieurs

                        map[i][j].habitation.connex = 1;
                        map[i + k][j - 2].route.visite = 1;
                        map[i + k][j - 2 + 1].route.visite = 1;

                        map[i + k][j - 2].route.color = ORANGE;
                        map[i + k][j - 2 + 1].route.color = ORANGE;

                        for (int l = 0; l < 3; l++) {
                            for (int m = 0; m < 3; m++) {
                                map[i + l][j + m].habitation.visite = 1;
                            }
                        }

                        parcourirRoute(map, i + k, j - 2, 2, map[i][j].habitation.id, g, tab_Graphe);
                    }
                    if (map[i + k][j + 4].route.id == 1 && map[i + k][j + 4 - 1].route.id == 1){ //3 cases inférieur
                        map[i][j].habitation.connex = 1;

                        map[i + k][j + 4].route.visite = 1;
                        map[i + k][j + 4 - 1].route.visite = 1;

                        map[i + k][j + 4].route.color = ORANGE;
                        map[i + k][j + 4 - 1].route.color = ORANGE;

                        for (int l = 0; l < 3; l++) {
                            for (int m = 0; m < 3; m++) {
                                map[i + l][j + m].habitation.visite = 1;
                            }
                        }

                        parcourirRoute(map, i + k, j + 4, 2, map[i][j].habitation.id, g, tab_Graphe);
                    }
                    if (map[i - 2][j + k].route.id == 1 && map[i - 2 + 1][j + k].route.id == 1){ //3 cases gauche
                        map[i][j].habitation.connex = 1;

                        map[i - 2 + 1][j + k].route.visite = 1;
                        map[i - 2 + 1][j + k].route.visite = 1;

                        map[i - 2][j + k].route.color = ORANGE;
                        map[i - 2 + 1][j + k].route.color = ORANGE;

                        for (int l = 0; l < 3; l++) {
                            for (int m = 0; m < 3; m++) {
                                map[i + l][j + m].habitation.visite = 1;
                            }
                        }

                        parcourirRoute(map, i - 2 , j + k, 2, map[i][j].habitation.id, g, tab_Graphe);
                    }

                    if (map[i + 4][j + k].route.id == 1 && map[i + 4 - 1][j + k].route.id == 1){ //3 cases droite
                        map[i][j].habitation.connex = 1;

                        map[i + 4][j + k].route.visite = 1;
                        map[i + 4 - 1][j + k].route.visite = 1;

                        map[i + 4][j + k].route.color = ORANGE;
                        map[i + 4 - 1][j + k].route.color = ORANGE;

                        for (int l = 0; l < 3; l++) {
                            for (int m = 0; m < 3; m++) {
                                map[i + l][j + m].habitation.visite = 1;
                            }
                        }

                        parcourirRoute(map, i + 4, j + k, 2, map[i][j].habitation.id, g, tab_Graphe);
                    }
                }
                if ((i - 1) >= 0 && (j - 1) >= 0 && map[i - 1][j - 1].route.id == 1 && (map[i][j - 1].route.id == 1 || map[i - 1][j].route.id == 1)){ //coins haut gauche
                    map[i][j].habitation.connex = 1;

                    map[i - 1][j - 1].route.visite = 1;
                    map[i - 1][j - 1].route.color = ORANGE;
                    map[i][j - 1].route.visite = 1;
                    map[i - 1][j].route.visite = 1;

                    if(map[i][j - 1].route.id == 1){
                        map[i][j - 1].route.color = ORANGE;
                    }
                    else if(map[i - 1][j].route.id == 1){
                        map[i - 1][j].route.color = ORANGE;
                    }

                    for (int l = 0; l < 3; l++) {
                        for (int m = 0; m < 3; m++) {
                            map[i + l][j + m].habitation.visite = 1;
                        }
                    }
                    parcourirRoute(map, i - 1, j - 1, 2, map[i][j].habitation.id, g, tab_Graphe);
                }
                if ((i + 3) <= 45 && (j + 3) <= 35 && map[i + 3][j + 3].route.id == 1 && (map[i + 3 - 1][j + 3].route.id == 1 || map[i + 3][j + 3 - 1].route.id == 1)){ //coins bas droite
                    map[i][j].habitation.connex = 1;

                    map[i + 3][j + 3].route.visite = 1;
                    map[i + 3][j + 3].route.color = ORANGE;
                    map[i + 3][j + 3 - 1].route.visite = 1;
                    map[i + 3 - 1][j + 3].route.visite = 1;

                    if(map[i + 3][j + 3 - 1].route.id == 1){
                        map[i + 3][j + 3 - 1].route.color = ORANGE;
                    }
                    else if(map[i + 3 - 1][j + 3].route.id == 1){
                        map[i + 3 - 1][j + 3].route.color = ORANGE;
                    }

                    for (int l = 0; l < 3; l++) {
                        for (int m = 0; m < 3; m++) {
                            map[i + l][j + m].habitation.visite = 1;
                        }
                    }
                    parcourirRoute(map, i + 3, j + 3, 2, map[i][j].habitation.id, g, tab_Graphe);
                }
                if ((i - 1) >= 0 && (j + 3) <= 35 && map[i - 1][j + 3].route.id == 1 && (map[i][j + 3].route.id == 1 || map[i - 1][j + 3 - 1].route.id == 1)){ //coins bas gauche
                    map[i][j].habitation.connex = 1;

                    map[i - 1][j + 3].route.visite = 1;
                    map[i - 1][j + 3].route.color = ORANGE;
                    map[i - 1][j + 3 - 1].route.visite = 1;
                    map[i][j + 3].route.visite = 1;

                    if(map[i - 1][j + 3 - 1].route.id == 1){
                        map[i - 1][j + 3 - 1].route.color = ORANGE;
                    }
                    else if(map[i][j + 3].route.id == 1){
                        map[i][j + 3].route.color = ORANGE;
                    }

                    for (int l = 0; l < 3; l++) {
                        for (int m = 0; m < 3; m++) {
                            map[i + l][j + m].habitation.visite = 1;
                        }
                    }
                    parcourirRoute(map, i - 1, j + 3, 2, map[i][j].habitation.id, g, tab_Graphe);
                }
                if ((i + 3) <= 45 && (j - 1) > 0 && map[i + 3][j - 1].route.id == 1 && (map[i + 3][j].route.id == 1 || map[i + 3 - 1][j - 1].route.id == 1)){ //coins haut droite
                    map[i][j].habitation.connex = 1;

                    map[i + 3][j - 1].route.visite = 1;
                    map[i + 3][j - 1].route.color = ORANGE;
                    map[i + 3][j].route.visite = 1;
                    map[i + 3 - 1][j - 1].route.visite = 1;

                    if(map[i + 3][j].route.id == 1){
                        map[i + 3][j].route.color = ORANGE;
                    }
                    else if(map[i + 3 - 1][j - 1].route.id == 1){
                        map[i + 3 - 1][j - 1].route.color = ORANGE;
                    }

                    for (int l = 0; l < 3; l++) {
                        for (int m = 0; m < 3; m++) {
                            map[i + l][j + m].habitation.visite = 1;
                        }
                    }
                    parcourirRoute(map, i + 3, j - 1, 2, map[i][j].habitation.id, g, tab_Graphe);
                }



                /*
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        if (map[i + l][j + k].route.id == 1 && validationParcourContourMaison(k,l)){
                            map[i][j].habitation.connex = 1;
                            map[i+l][j+k].route.visite = 1;
                            map[i+l][j+k].route.color = ORANGE;
                            map[i][j].habitation.visite = 1;
                            parcourirRoute(map, i+l, j+k, 1, map[i][j].habitation.id, g, tab_Graphe);
                            for (int m = 0; m < 45; m++) {
                                for (int n = 0; n < 35; n++) {
                                    map[m][n].route.visite = 0;
                                }
                            }
                        }
                    }
                }
*/
            }
        }
    }
}

void viabiliteEau(MAP map[45][35],TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE], Graphe *graphe){
    int s1[100];
    int s2[100];
    int valeur[100];
    int type[100];
    int sommet1 = 0;
    int sommet2 = 0;
    int distance = 0;
    int p = 0;
    for (int z=0;z<tab_Graphe[0].last_id;z++){
        s1[z] = tab_Graphe[z].s1;
        s2[z] = tab_Graphe[z].s2;
        valeur[z] = tab_Graphe[z].valeur;
        type[z] = tab_Graphe[z].type;
    }
    for(int i=0;i<tab_Graphe[0].last_id-1;i++)
        for(int j=i+1;j<tab_Graphe[0].last_id;j++)
            if ( valeur[i] > valeur[j] ) {
                distance = valeur[i];
                valeur[i] = valeur[j];
                valeur[j] = distance;

                sommet1 = s1[i];
                s1[i] = s1[j];
                s1[j] = sommet1;

                sommet2 = s2[i];
                s2[i] = s2[j];
                s2[j] = sommet2;

                p = type[i];
                type[i] = type[j];
                type[j] = p;

            }

    for (int i=0;i<tab_Graphe[0].last_id;i++){
        if (type[i] == 3){
            for (int j = 0; j < 35; j++) {
                for (int k = 0; k < 45; k++) {
                    if (map[k][j].habitation.id == s1[i] && map[k][j].habitation.viableEau == 0){
                        for (int a = 0; a < 35; a++) {
                            for (int b = 0; b < 45; b++) {
                                if(map[b][a].chateaueau.id == s2[i] && map[b][a].chateaueau.capacite>=map[k][j].habitation.nombreHabitants ){
                                    map[b][a].chateaueau.capacite = map[b][a].chateaueau.capacite - map[k][j].habitation.nombreHabitants;
                                    map[k][j].habitation.viableEau = 1;
                                    graphe->pSommet[map[k][j].habitation.id]->habitation.viableEau = 1;
                                }
                            }
                        }
                    }
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

void placementElement(Vector2 mouseposition, Rectangle caseMAP, MAP map[45][35], INFO *infoPerm,HUD hud[NOMBRE_CASE_HUD], Graphe *graphe, TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE]){
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
                            //connexRoute(map, graphe, tab_Graphe);
                        }
                        if (i < 45 - 2 && j < 35 - 2){
                            if (hud[1].etat == 1 && testMapOccupation(i, j, map, Habitation) == 1 && infoPerm->ECEFlouz >= infoPerm->prixHabitation) {//conditions sur i et j sinon maison sort de la ma
                                map[0][0].id++;
                                map[0][0].idHabitation++;
                                infoPerm->ECEFlouz = infoPerm->ECEFlouz - infoPerm->prixHabitation;
                                graphe->ordre++;
                                for (int a = 0; a < 3; a++) {
                                    for (int b = 0; b < 3; b++) {
                                        map[i + a][j + b].occupe = 1;
                                        map[i + a][j + b].habitation.id = map[0][0].id;
                                        map[i][j].type = Habitation;
                                    }
                                }
                                graphe->pSommet[map[0][0].id]->valeur = map[0][0].id;
                                graphe->pSommet[map[0][0].id]->habitation.id = map[0][0].id;
                                graphe->pSommet[map[0][0].id]->habitation.nombreHabitants = 0;
                                graphe->pSommet[map[0][0].id]->habitation.viableElec = 0;
                                graphe->pSommet[map[0][0].id]->habitation.viable = 0;
                                graphe->pSommet[map[0][0].id]->habitation.viableEau = 0;
                                graphe->pSommet[map[0][0].id]->habitation.evolution = 0;
                                graphe->pSommet[map[0][0].id]->type = 1;

                                //connexRoute(map, graphe, tab_Graphe);
                            }
                        }

                        if (i < 45 - 3 && j < 35 - 5) {
                            if (hud[2].etat == 1 && testMapOccupation(i, j, map, Centrale) == 1 && infoPerm->ECEFlouz >= infoPerm->prixCentrale) { //conditions sur i et j sinon centrale sort de la map
                                map[0][0].id++;
                                infoPerm->ECEFlouz = infoPerm->ECEFlouz - infoPerm->prixCentrale;
                                graphe->ordre++;
                                for (int a = 0; a < 4; a++) {
                                    for (int b = 0; b < 6; b++) {
                                        map[i + a][j + b].occupe = 1;
                                        map[i+a][j+b].centrale.id = map[0][0].id;
                                        map[i][j].type = Centrale;

                                    }
                                }
                                graphe->pSommet[map[0][0].id]->valeur = map[0][0].id;
                                graphe->pSommet[map[0][0].id]->centrale.id = map[0][0].id;
                                graphe->pSommet[map[0][0].id]->centrale.capacite = 5000;
                                graphe->pSommet[map[0][0].id]->centrale.quantiteDistribue = 0;
                                graphe->pSommet[map[0][0].id]->type = 2;

                                //connexRoute(map, graphe, tab_Graphe);
                            }
                        }
                        if (i < 45 - 3 && j < 35 - 5) {
                            if (hud[3].etat == 1 && testMapOccupation(i, j, map, ChateauEau) == 1 && infoPerm->ECEFlouz >= infoPerm->prixChateauEau) { //conditions sur i et j sinon centrale sort de la map
                                map[0][0].id++;
                                map[0][0].idChateauEau++;
                                infoPerm->ECEFlouz = infoPerm->ECEFlouz - infoPerm->prixChateauEau;
                                graphe->ordre++;
                                for (int a = 0; a < 4; a++) {
                                    for (int b = 0; b < 6; b++) {
                                        map[i + a][j + b].occupe = 1;
                                        map[i][j].type = ChateauEau;
                                        map[i+a][j+b].chateaueau.id = map[0][0].id;
                                    }
                                }
                                graphe->pSommet[map[0][0].id]->valeur = map[0][0].id;
                                graphe->pSommet[map[0][0].id]->chateaueau.id = map[0][0].id;
                                graphe->pSommet[map[0][0].id]->chateaueau.capacite = 5000;
                                graphe->pSommet[map[0][0].id]->chateaueau.quantiteDistribue = 0;
                                graphe->pSommet[map[0][0].id]->type = 3;

                                //connexRoute(map, graphe, tab_Graphe);
                            }
                        }
                    }
                }
            }
        }
    }
}

void evolutionV2(MAP map[45][35], INFO *infoPerm){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id != 0 && map[i][j].habitation.viable == 1){
                map[i][j].habitation.compteur++;
                if(map[i][j].habitation.compteur == 15){
                    if (map[i][j].habitation.evolution < 4){map[i][j].habitation.evolution++;}
                    map[i][j].habitation.compteur = 0;
                    infoPerm->ECEFlouz = infoPerm->ECEFlouz + (float)map[i][j].habitation.nombreHabitants * 10;
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

void evolution(MAP map[45][35], INFO *infoPerm){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id != 0 && map[i][j].habitation.evolution < 4){
                map[i][j].habitation.compteurEvolution++;
                if ((map[i][j].habitation.compteurEvolution/60)==map[i][j].habitation.tempsFuturArgent && map[i][j].habitation.compteurEvolution!=map[i][j].habitation.tempsBanniArgent){
                    map[i][j].habitation.tempsFuturArgent=map[i][j].habitation.tempsFuturArgent+15;
                    map[i][j].habitation.tempsBanniArgent=map[i][j].habitation.compteurEvolution;
                }
                if (map[i][j].habitation.viable == 1){


                    if ((map[i][j].habitation.compteurEvolution/60)==map[i][j].habitation.tempsFuturEvolution && map[i][j].habitation.compteurEvolution!=map[i][j].habitation.tempsBanniEvolution){
                        map[i][j].habitation.tempsFuturEvolution=map[i][j].habitation.tempsFuturEvolution+15;
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

void dessinerElement(MAP map[45][35], Texture2D cabane, Texture2D maison, Texture2D immeuble, Texture2D gratteciel, Texture2D terrain, Texture2D route,Texture2D chateaudeau, Texture2D centrale, int niveauAffichage){

    for (int j = 0; j < 35; j++) {
        for (int i = 0; i < 45; i++) {
            if(map[i][j].type == Habitation){
                if (map[i][j].habitation.evolution==TERRAIN_VAGUE){
                    DrawTexture(terrain, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j *  LARGEUR1CASE, WHITE);
                }
                if (map[i][j].habitation.evolution==CABANE){

                    DrawTexture(cabane, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j *  LARGEUR1CASE, WHITE);

                }
                if (map[i][j].habitation.evolution==MAISON){

                    DrawTexture(maison, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);

                }
                if (map[i][j].habitation.evolution==IMMEUBLE){

                    DrawTexture(immeuble, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);

                }
                if (map[i][j].habitation.evolution==GRATTE_CIEL){

                    DrawTexture(gratteciel, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);

                }

            }
            if (map[i][j].route.id == 1 && niveauAffichage == 0){
                //DrawTexture(route, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, map[i][j].route.color);
            }
            if (map[i][j].route.id == 1 && niveauAffichage == 1){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, BLUE);
            }
            if (map[i][j].route.id == 1 && niveauAffichage == 2){
                DrawRectangle(POSITIONMAP_X + i * LARGEUR1CASE, POSITIONMAP_Y + j * LARGEUR1CASE, LARGEUR1CASE, LARGEUR1CASE, YELLOW);
            }
            if(map[i][j].centrale.id != 0 && map[i][j].centrale.visite == 0 && (niveauAffichage == 2 || niveauAffichage == 0)){

                DrawRectangleLines(POSITIONMAP_X + i * LARGEUR1CASE,POSITIONMAP_Y + j * LARGEUR1CASE, 4 * LARGEUR1CASE, 6 * LARGEUR1CASE, YELLOW);
                DrawTexture(centrale, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);
                for (int k = 0; k < 4; k++) {
                    for (int l = 0; l < 6; l++) {
                        map[i + k][j + l].centrale.visite = 1;
                    }
                }
                //quantite distribuée en fonction de la capacité
                DrawText(TextFormat("%d/%d", map[i][j].centrale.quantiteDistribue,map[i][j].centrale.capacite), POSITIONMAP_X + i * LARGEUR1CASE + 15,POSITIONMAP_Y + j * LARGEUR1CASE -20, 15, YELLOW);
            }
            if(map[i][j].chateaueau.id != 0 && map[i][j].chateaueau.visite == 0 && (niveauAffichage == 1 || niveauAffichage == 0)){
                DrawRectangleLines(POSITIONMAP_X + i * LARGEUR1CASE,POSITIONMAP_Y + j * LARGEUR1CASE, 4 * LARGEUR1CASE, 6 * LARGEUR1CASE, SKYBLUE);
                DrawTexture(chateaudeau, POSITIONMAP_X + i * LARGEUR1CASE , POSITIONMAP_Y + j * LARGEUR1CASE, WHITE);
                for (int k = 0; k < 4; k++) {
                    for (int l = 0; l < 6; l++) {
                        map[i + k][j + l].chateaueau.visite = 1;
                    }
                }
                DrawText(TextFormat("%d/%d", map[i][j].chateaueau.quantiteDistribue,map[i][j].chateaueau.capacite), POSITIONMAP_X + i * LARGEUR1CASE + 15,POSITIONMAP_Y + j * LARGEUR1CASE -20, 15, SKYBLUE);
            }
        }
    }
}

void nombreHabitant(MAP map[45][35],INFO *infoPerm){
    int habitantTotal = 0;
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++) {
            if (map[i][j].habitation.id != 0){
                habitantTotal = habitantTotal + map[i][j].habitation.nombreHabitants/9 + 1;
        }
        }
    }

    map[0][0].nombreTotalHabitant = habitantTotal;
    infoPerm->habitants = habitantTotal;
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

void viabEau(Graphe *graphe, MAP map[45][35]){
    int s0;
    for (int j = 0; j < 35; j++) {
        for (int i = 0; i < 45; i++) {
            s0 = map[i][j].habitation.id;
            if (s0 != 0){
                struct Arc *arc = graphe->pSommet[s0]->arc;
                while (arc != NULL && !(graphe->pSommet[s0]->habitation.viableEau)){
                    int s = arc->sommet;

                    if (arc->arc_suivant == NULL){ //si plus arc on conserve s comme plus cours chemin
                        break;
                    }
                    else if(graphe->pSommet[s]->arc->valeur > graphe->pSommet[arc->arc_suivant->sommet]->arc->valeur && graphe->pSommet[s]->couleur == 0 && graphe->pSommet[arc->arc_suivant->sommet]->couleur == 0){
                        s = arc->arc_suivant->sommet;
                    }
                    graphe->pSommet[s]->couleur = 1;

                    if (graphe->pSommet[s]->type == 3 && graphe->pSommet[s]->centrale.capacite >= graphe->pSommet[s0]->habitation.nombreHabitants){
                        graphe->pSommet[s]->centrale.capacite -= graphe->pSommet[s0]->habitation.nombreHabitants;
                        graphe->pSommet[s0]->habitation.viableElec = 1;
                        graphe->pSommet[s0]->habitation.centraleQuiAlimente = s;
                    }
                    arc = arc->arc_suivant;
                }
            }
        }
    }
}

void viabiliteElectricite(Graphe *graphe, MAP map[45][35]){
    int s0;
    for (int j = 0; j < 35; j++) {
        for (int i = 0; i < 45; i++) {
            s0 = map[i][j].habitation.id;
            if (s0 != 0){
                struct Arc *arc = graphe->pSommet[s0]->arc;
                while (arc != NULL && !(graphe->pSommet[s0]->habitation.viableElec)){

                    int s = arc->sommet;
                    if (graphe->pSommet[s]->type == 2 && graphe->pSommet[s]->centrale.capacite >= graphe->pSommet[s0]->habitation.nombreHabitants){
                        graphe->pSommet[s]->centrale.capacite -= graphe->pSommet[s0]->habitation.nombreHabitants;
                        graphe->pSommet[s0]->habitation.viableElec = 1;
                        map[i][j].habitation.viableElec = 1;
                        graphe->pSommet[s0]->habitation.centraleQuiAlimente = s;
                    }
                    arc = arc->arc_suivant;
                }
            }
        }
    }
}

void testViabilite(Graphe *graphe, MAP map[45][35]){
    for (int i = 0; i < 45; i++) {
        for (int j = 0; j < 35; j++){
            if (map[i][j].habitation.viableElec == 1 && map[i][j].habitation.viableEau == 1){
                printf("%d\n", map[i][j].habitation.id);
                graphe->pSommet[i]->habitation.viable = 1;
                map[i][j].habitation.viable = 1;

            }
        }
    }
}

void testRegression(MAP map[45][35]){
    for (int j = 0; j < 35; j++) {
        for (int i = 0; i < 45; i++) {
            if (map[i][j].habitation.id != 0 && map[i][j].habitation.viable == 0 && map[i][j].habitation.evolution > 0){
                map[i][j].habitation.evolution--;
            }
        }
    }
}

void mapECECITY(MAP map[45][35], HUD hud[NOMBRE_CASE_HUD], INFO infoPerm, int choixMode){
    TAB_GRAPHE tab_Graphe[NOMBRE_ARETES_TABGRAPHE];
    initialiserTABGRAPHE(tab_Graphe);


    Graphe *graphe = CreerGraphe(NOMBRE_MAX_ELEMENT);
    initialiserGraphe(graphe);

    Vector2 mapPosition = initialisationPositionMap();

    Texture2D terrain = LoadTexture("../images/Constructions /terrain3.png");
    Texture2D cabane = LoadTexture("../images/Constructions /cabane3.png");
    Texture2D maison = LoadTexture("../images/Constructions /maison3.png");
    Texture2D immeuble = LoadTexture("../images/Constructions /immeuble3.png");
    Texture2D gratteciel = LoadTexture("../images/Constructions /gratteciel3.png");
    Texture2D fondmap = LoadTexture("../images/Menu/fond.png");
    Texture2D route = LoadTexture("../images/Constructions /route.png");
    Texture2D chateaudeau = LoadTexture("../images/Constructions /chateaudeau.png");
    Texture2D centrale = LoadTexture("../images/Constructions /centrale .png");

    Texture2D eau = LoadTexture("../images/Hud/eau2.png");
    Texture2D elec = LoadTexture("../images/Hud/elec2.png");
    Texture2D road = LoadTexture("../images/Hud/road2.png");
    Texture2D house = LoadTexture("../images/Hud/house2.png");

    Rectangle HUD[NOMBRE_CASE_HUD];
    initialisationCaseHUD(HUD);
    Rectangle caseMAP = initialisationCaseMAP();

    int niveauAffichage = 0;

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
        DrawText("ECE CITY", 320, 12, 70, BROWN);

        if (TimerDone(timer)){ //Fonction execute toute les 1 seconde
            StartTimer(&timer, lifetime);
            evolutionV2(map, &infoPerm);
        }
        mouseposition = GetMousePosition();

        dessinerHUD(HUD); //Dessine les cases de la boite à outil
        HUDcollision(hud, HUD, mouseposition, &niveauAffichage); //Test si surpassage de case et si clic dans une des cases

        dessinerimgHud(road, house, elec, eau);

        //nombreHabitant(map);
        //connexRoute(map, graphe, tab_Graphe);
        lireGraphe(tab_Graphe, graphe);

        switch (niveauAffichage) {
            case 0:{
                for (int m = 0; m < 45; m++) {
                    for (int n = 0; n < 35; n++) {
                        map[m][n].route.visite = 0;
                        map[m][n].route.color = BLACK;
                    }
                }
                connexRoute(map, graphe, tab_Graphe);


                //Map
                dessinerMap(mapPosition); //Dessine le fond de map (possibilité de changer la texture de la map)
                placementElement(mouseposition, caseMAP, map, &infoPerm, hud,graphe, tab_Graphe);
                for (int i = 0; i < 45; i++) {
                    for (int j = 0; j < 35; j++) {
                        map[i][j].habitation.visite = 0;
                        map[i][j].route.visite = 0;
                    }
                }
                dessinerElement(map,cabane,maison,immeuble,gratteciel,terrain,route, chateaudeau, centrale, niveauAffichage); //Dessine toutes les maisons enregistrées en mémoire
                affichageInfo(&infoPerm); //Affichage informations de la partie
                break;
            }
            case 1:{
                dessinerMap(mapPosition); //Dessine le fond de map (possibilité de changer la texture de la map)
                dessinerElement(map,cabane,maison,immeuble,gratteciel,terrain,route, chateaudeau, centrale, niveauAffichage); //Dessine toutes les maisons enregistrées en mémoire
                affichageInfo(&infoPerm); //Affichage informations de la partie
                break;
            }
            case 2:{
                dessinerMap(mapPosition); //Dessine le fond de map (possibilité de changer la texture de la map)
                dessinerElement(map,cabane,maison,immeuble,gratteciel,terrain,route, chateaudeau, centrale, niveauAffichage); //Dessine toutes les maisons enregistrées en mémoire
                affichageInfo(&infoPerm); //Affichage informations de la partie
               break;
            }
        }

        viabiliteElectricite(graphe, map);
        viabiliteEau(map, tab_Graphe, graphe);
        testViabilite(graphe, map);

        impots(map, &infoPerm);
        testRegression(map);

        for (int k = 0; k < 45; k++) {
            for (int l = 0; l < 35; l++) {
                map[k][l].chateaueau.visite = 0;
                map[k][l].centrale.visite = 0;
            }
        }

        //nombreHabitant(map);

        EndDrawing();

        if (IsKeyPressed(KEY_A)){
            for (int i = 0; i < NOMBRE_MAX_ELEMENT; i++) {
                if (graphe->pSommet[i]->habitation.viableElec != 0){
                    printf("i=%d | %d viable(%d) est alimenté par %d = %d / il reste %d €\n", i,graphe->pSommet[i]->valeur,graphe->pSommet[i]->habitation.viableElec, graphe->pSommet[i]->habitation.centraleQuiAlimente,graphe->pSommet[graphe->pSommet[i]->habitation.centraleQuiAlimente]->centrale.id,graphe->pSommet[graphe->pSommet[i]->habitation.centraleQuiAlimente]->centrale.capacite);
                }
            }
            graphe_afficher(graphe);
        }
    }

    UnloadTexture(terrain);
    UnloadTexture(cabane);
    UnloadTexture(maison);
    UnloadTexture(immeuble);
    UnloadTexture(gratteciel);
    UnloadTexture(route);
    UnloadTexture(chateaudeau);
    UnloadTexture(centrale);
    UnloadTexture(fondmap);

    UnloadTexture(eau);
    UnloadTexture(elec);
    UnloadTexture(road);
    UnloadTexture(house);

    CloseWindow();
/*
    for (int i = 0; i < NOMBRE_ARETES_TABGRAPHE; i++) {
        printf("%d %d %d\n", tab_Graphe[i].s1, tab_Graphe[i].s2, tab_Graphe[i].valeur);
    }*/
}

