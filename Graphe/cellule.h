#ifndef TP2_CHARGEMENT_GRAPHE_C_CELLULE_H
#define TP2_CHARGEMENT_GRAPHE_C_CELLULE_H
typedef int typage;

struct _cellule {
    typage element;
    struct _cellule *suivant;
};

typedef struct _cellule* Cellule;
#endif //TP2_CHARGEMENT_GRAPHE_C_CELLULE_H
