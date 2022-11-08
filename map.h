#ifndef UNTITLED10_MAP_H
#define UNTITLED10_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h>

typedef struct {
    double x,y;
    int etat; //Construction present dessus (0 rien, 1 route, 2 centrale, 3 chateau d'eau, 4 terrain vague?)

}Map;

typedef struct{
    double x,y;
    int etat;

}HUD;

#endif