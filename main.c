#include "map.h"
#include "menu.h"


int main(){
    int choixmode = 0;

    accueil();
    modeJeu(&choixmode);

    MAP map[45][35];
    HUD hud[NOMBRE_CASE_HUD];
    INFO infoPerm;

    initialisationMap(map);
    initialisationHUD(hud);
    initialisationInfo(&infoPerm);

    HABITATION habitation[100]; //créé si possible un tableau dynamique avec redimensionnement
    CENTRALE centrale[100]; //créé si possible un tableau dynamique avec redimensionnement

    InitWindow(LARGUEUR, HAUTEUR, "ECE city");

    SetTargetFPS(60);


    //Fonction executé
    mapNiveau0(map, hud, habitation, centrale, infoPerm);
    for (int j=0;j<35;j++){
        for(int i=0;i<45;i++){
            printf("%d ",map[i][j].habitation.viable);
        }
        printf("\n");
    }
    printf("%d\n",map[0][0].habitation.connex);
    //infoPerm.ECEFlouz = infoPerm.ECEFlouz -1000;
    printf("%f ",infoPerm.ECEFlouz);

}
