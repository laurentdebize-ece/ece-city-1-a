#include "map.h"
#include "menu.h"
#include "Graphe/Graphe.h"

int main(){

    Graphe *graphe;

    int choixmode = 0;

    MAP map[45][35];
    HUD hud[NOMBRE_CASE_HUD];
    INFO infoPerm;

    initialisationMap(map);
    initialisationHUD(hud);
    initialisationInfo(&infoPerm);

    ELEMENT element[NOMBRE_MAX_ELEMENT];

    InitWindow(LARGUEUR, HAUTEUR, "ECE city");

    SetTargetFPS(60);

    //Fonction executé
    //accueil();
    //modeJeu(&choixmode);

    mapECECITY(map, hud,element,infoPerm);

    for (int j=0;j<35;j++){
        for(int i=0;i<45;i++){
            printf("%d", map[i][j].habitation.id);
        }
        printf("\n");
    }
    for (int j=0;j<35;j++){
        for(int i=0;i<45;i++){
            printf("%d", map[i][j].centrale.id);
        }
        printf("\n");
    }
    printf("%d\n",map[0][0].habitation.connex);
    //infoPerm.ECEFlouz = infoPerm.ECEFlouz -1000;
    printf("%f ",infoPerm.ECEFlouz);

    return 0;
}