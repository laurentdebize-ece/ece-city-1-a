//
// Created by Erwan Pillard on 08/11/2022.
//

#ifndef ECE_CITY_1_A_ELEMENT_H
#define ECE_CITY_1_A_ELEMENT_H

#define NOMBRE_HABITATION_MAX 100
#define NOMBRE_CENTRALE_MAX 50

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
    int compteur;
    int impots;
}HABITATION;





#endif //ECE_CITY_1_A_ELEMENT_H
