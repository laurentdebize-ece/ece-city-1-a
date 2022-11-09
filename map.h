#ifndef UNTITLED10_MAP_H
#define UNTITLED10_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include <math.h>

typedef struct {
    int etat; //Construction present dessus (-1 rien, 0 route, 1 maison, 2 chateau d'eau, 3 centrale )
    int stade;//Stade d'evolution de la maison (etat 1)
    int occupe; //Savoir si il y a deja quelque chose sur la case
}Map;

typedef struct{
    int etat;

}HUD;


#endif