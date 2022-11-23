//
// Created by Erwan Pillard on 08/11/2022.
//

#ifndef ECE_CITY_1_A_ELEMENT_H
#define ECE_CITY_1_A_ELEMENT_H

#define NOMBRE_HABITATION_MAX 100
#define NOMBRE_CENTRALE_MAX 50

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
    int elec;
    int eau;
    int compteur;
    int impots;
    float tempsBanni;
    float compteurEvolution;
    float tempsFuturEvolution;

}HABITATION;






#endif //ECE_CITY_1_A_ELEMENT_H
