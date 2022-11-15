#include "map.h"


int main(){
    MAP map[45][35];
    HUD hud[NOMBRE_CASE_HUD];
    initialisationMap(map);
    initialisationHUD(hud);

    HABITATION habitation[100]; //créé si possible un tableau dynamique avec redimensionnement
    CENTRALE centrale[100]; //créé si possible un tableau dynamique avec redimensionnement

    InitWindow(LARGUEUR, HAUTEUR, "ECE city");

    SetTargetFPS(60);

    //Fonction executé
    mapNiveau0(map, hud, habitation, centrale);
}
