#ifndef UNTITLED10_MAP_H
#define UNTITLED10_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "raylib.h"
#include "boiteoutil.h"
#include "element.h"

#define LARGUEUR 1024
#define HAUTEUR 678
#define LARGEUR1CASE 15//Distance entre le centre de deux carrés adjacent de la map

#define POSITIONMAP_X 180
#define POSITIONMAP_Y 105

enum type{NONOCCUPE, Route,Habitation, Central, ChateauEau};

typedef struct {

    int occupe; //Savoir si il y a deja quelque chose sur la case (ENUM)
    int route;
    HABITATION habitation;
    CHATEAUEAU chateaueau;
    CENTRALE centrale;


    int etat; //Construction present dessus (-1 rien, 0 route, 1 maison, 2 chateau d'eau, 3 centrales)
    int stade;//Stade d'évolution de la maison (état 1)
    int tempsBanni; // POur éviter les répétitions
}MAP;

typedef struct{
    int etat;
}HUD;


void initialiserMap(MAP map[45][35],HUD hud[6]);

void mapNiveau0(MAP map[45][35], HUD hud[6]);
#endif