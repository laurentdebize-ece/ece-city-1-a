//
// Created by Erwan Pillard on 08/11/2022.
//

#ifndef ECE_CITY_1_A_ELEMENT_H
#define ECE_CITY_1_A_ELEMENT_H

#define NOMBRE_HABITATION_MAX 100
#define NOMBRE_CENTRALE_MAX 50
#define NOMBRE_CHATEAUEAU_MAX 50

#include "raylib.h"

enum evolution {TERRAIN_VAGUE, CABANE, MAISON, IMMEUBLE, GRATTE_CIEL};

typedef struct{

    int id;
    int positionX;
    int positionY;
    int capacite;
    int quantiteDistribue;

}CENTRALE;


typedef struct{

    int id;
    int positionX;
    int positionY;
    int capacite;
    int quantiteDistribue;

}CHATEAUEAU;

typedef struct{

    int id;
    int positionX;
    int positionY;
    int evolution; //0 : ruine, 1 : cabane,...
    int nombreHabitants;
    int viable;
    int connex;
    int viableElec;
    int viableEau;
    int compteur;
    int impots;
    float tempsBanniEvolution;
    float compteurEvolution;
    float tempsFuturEvolution;
    float tempsBanniArgent;
    float tempsFuturArgent;
    int visite;

}HABITATION;


typedef struct {
    int visite;
    int id;
    Color color;
}ROUTE;



#endif //ECE_CITY_1_A_ELEMENT_H
