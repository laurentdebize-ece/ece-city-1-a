#ifndef UNTITLED10_MAP_H
#define UNTITLED10_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "raylib.h"
#include "boiteoutil.h"
#include "element.h"
#include "time.h"
#include "informationPerm.h"
#include "menu.h"

#define LARGUEUR 1024
#define HAUTEUR 768
#define LARGEUR1CASE 15//Distance entre le centre de deux carrés adjacent de la map

#define POSITIONMAP_X 180
#define POSITIONMAP_Y 105

enum type{NONOCCUPE, Route,Habitation, Centrale, ChateauEau};

typedef struct {

    int occupe; //Savoir si il y a deja quelque chose sur la case (ENUM)
    int route;
    int connexite;
    int idHabitation;
    int idCentrale;
    int idChateauEau;
    int nombreTotalHabitant;
    HABITATION habitation;
    CHATEAUEAU chateaueau;
    CENTRALE centrale;
}MAP;

void initialisationMap(MAP map[45][35]);

void mapNiveau0(MAP map[45][35], HUD hud[6], HABITATION habitation[NOMBRE_HABITATION_MAX], CENTRALE centrale[NOMBRE_CENTRALE_MAX], INFO infoPerm);




#endif