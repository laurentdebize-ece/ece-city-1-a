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
#include "Graphe/Graphe.h"
#include "menu.h"

#define LARGUEUR 1024
#define HAUTEUR 768
#define LARGEUR1CASE 15//Distance entre le centre de deux carrés adjacent de la map

#define POSITIONMAP_X 190
#define POSITIONMAP_Y 130

enum type{NONOCCUPE, Route,Habitation, Centrale, ChateauEau};

typedef struct {

    int type;
    int occupe; //Savoir si il y a deja quelque chose sur la case (ENUM)
    int id;
    int idHabitation;
    int idCentrale;
    int idChateauEau;
    int nombreTotalHabitant;
    ROUTE route;
    HABITATION habitation;
    CHATEAUEAU chateaueau;
    CENTRALE centrale;
}MAP;

void initialisationMap(MAP map[45][35]);

void mapECECITY(MAP map[45][35], HUD hud[6],INFO infoPerm, int choixMode);




#endif