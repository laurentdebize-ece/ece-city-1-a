#ifndef UNTITLED10_MAP_H
#define UNTITLED10_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "raylib.h"
#include "boiteoutil.h"

#define LARGUEUR 1024
#define HAUTEUR 678
#define LARGEUR1CASE 15//Distance entre le centre de deux carré adjacent de la map

typedef struct {
    int etat; //Construction present dessus (-1 rien, 0 route, 1 maison, 2 chateau d'eau, 3 centrale )
    int stade;//Stade d'evolution de la maison (etat 1)
    int occupe; //Savoir si il y a deja quelque chose sur la case
    int tempsBanni; // POur éviter les répétitions
}Map;

typedef struct{
    int etat;

}HUD;


void initialiserMap(Map map[45][35],HUD hud[6]);
void boucle(Map map[45][35],HUD hud[6],Vector2 mapPosition,Vector2 mapSize,Vector2 mousePosition,int evolution,int time,int collisionHUD,int collisionMAP);


#endif