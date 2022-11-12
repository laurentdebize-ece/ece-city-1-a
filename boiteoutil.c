//
// Created by Erwan Pillard on 09/11/2022.
//

#include "boiteoutil.h"
#include "map.h"

Rectangle initialisationHUD(){
    Rectangle HUD;

    HUD.height=50;
    HUD.width=50;
    HUD.x=10;
    HUD.y=50;

    return HUD;
}

Rectangle initialisationCaseMAP(){
    Rectangle MAP;

    MAP.x = POSITIONMAP_X;
    MAP.y = POSITIONMAP_Y;
    MAP.height=LARGEUR1CASE;
    MAP.width=LARGEUR1CASE;

    return MAP;
}
