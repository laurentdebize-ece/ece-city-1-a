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

    InitWindow(LARGUEUR, HAUTEUR, "ECE city");
    //InitAudioDevice();

    SetTargetFPS(60);

    //Fonction executé
    accueil(&choixmode);
    mapECECITY(map, hud,infoPerm, choixmode);

    return 0;
}