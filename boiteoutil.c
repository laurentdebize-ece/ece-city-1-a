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

Rectangle initialisationMAP(){
    Rectangle MAP;

    MAP.x = LARGEUR1CASE*3;
    MAP.y = LARGEUR1CASE*3;
    MAP.height=LARGEUR1CASE;
    MAP.width=LARGEUR1CASE;

    return MAP;
}
