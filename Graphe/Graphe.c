#include "Graphe.h"
#include "fifo.h"

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet *sommet, int num) {

    printf(" sommet %d :\n", num);

    pArc arc = sommet[num]->arc;

    while (arc != NULL) {
        int compteur = 0;
        printf("%d ", arc->sommet);
        arc = arc->arc_suivant;
    }

}

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet *CreerArete(pSommet *sommet, int s1, int s2, int valeur) {
    if (sommet[s1]->arc == NULL) {
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->valeur = valeur;
        Newarc->arc_suivant = NULL;
        sommet[s1]->arc = Newarc;
        return sommet;
    } else {
        pArc temp = sommet[s1]->arc;
        while(!(temp->arc_suivant == NULL)) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc) malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->valeur = valeur;
        Newarc->arc_suivant = NULL;

        if (temp->sommet > s2) {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->sommet = temp->sommet;
            temp->sommet = s2;
            temp->arc_suivant = Newarc;
            return sommet;
        }

        temp->arc_suivant = Newarc;
        return sommet;
    }
}

// creer le graphe
Graphe *CreerGraphe(int ordre) {
    Graphe *Newgraphe = (Graphe *) malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet *) malloc(ordre * sizeof(pSommet));


    for (int i = 0; i < ordre; i++) {
        Newgraphe->pSommet[i] = (pSommet) malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }
    return Newgraphe;
}

/* La construction du reseau peut se faire a partir d'un fichier dont le nom est passe en parametre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe *lire_graphe(char *nomFichier) {
    Graphe *graphe;
    FILE *ifs = fopen(nomFichier, "r");
    int taille, orientation, ordre, s1, s2, valeur;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);

    graphe = CreerGraphe(ordre); // creer le graphe d'ordre sommets

    fscanf(ifs, "%d", &taille);
    fscanf(ifs, "%d", &orientation);

    graphe->orientation = orientation;
    graphe->ordre = ordre;

    // creer les aretes du graphe
    for (int i = 0; i < taille; ++i) {
        fscanf(ifs, "%d%d%d", &s1, &s2, &valeur);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, valeur);

        if (!orientation)
            graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, valeur);
    }

    fclose(ifs);
    return graphe;
}

int lireGraphe(int s1, int s2, int valeur, Graphe *graphe) {
    // creer les aretes du graphe
    graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, valeur);

    if (!graphe->orientation){
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, valeur);
    }
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe *graphe) {
    printf("graphe\n");

    if (graphe->orientation)
        printf("oriente\n");
    else
        printf("non oriente\n");

    printf("ordre = %d\n", graphe->ordre);

    printf("listes d'adjacence :\n");

    for (int i = 0; i < graphe->ordre; i++) {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}

//fonction donnee a titre d'exemple d'utilisation de file
File exemple_remplir_file() {
    //initialisation
    File file = fileVide();
    //on remplit avec les entiers de 1 à 10
    int i;
    printf("Etat de la file : ");
    afficherFile(file);
    for (i = 1; i < 10; i++) {
        enfiler(file, i);
        printf("Etat de la file : ");
        afficherFile(file);
    }
    return file;
}

//fonction donnee a titre d'exemple d'utilisation de file
void exemple_vider_file(File file) {
    //tant que la file n'est pas vide, on défile
    while (!fileEstVide(file)) {
        int element = defiler(file);
        printf("element defile : %d\n", element);
        printf("Etat de la file : ");
        afficherFile(file);
    }
}