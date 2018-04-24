#include "tree.h"

Liste *create(int var, int val, int visit){

    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));
    if (liste == NULL || element == NULL){
		exit(EXIT_FAILURE);
    }
    element->var = var;
	element->val = val;
	element->visited = visit;
    element->suivant = NULL;
    liste->premier = element;
    return liste;
}

void addElem(Liste *liste, int var, int val, int visit){
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL){
        exit(EXIT_FAILURE);
    }
    nouveau->var = var;
	nouveau->val = val;
	nouveau->visited = visit;
    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void removeElem(Liste *liste){
    if (liste == NULL){
        exit(EXIT_FAILURE);
    }
    if (liste->premier != NULL){
        Element *toRemove = liste->premier;
        liste->premier = liste->premier->suivant;
        free(toRemove);
    }
}

void print(Liste *liste){
    if (liste == NULL){
        exit(EXIT_FAILURE);
    }
    Element *actuel = liste->premier;
    while (actuel != NULL){
        printf("Q%d:R%d_V=%d <--- ", actuel->var, actuel->val, actuel->visited);
        actuel = actuel->suivant;
    }
    printf("START\n");

}

void showSolution(Liste *tree, int sizeVar){
	int solution[sizeVar];
	int i = sizeVar-1;
	Element *actuel = tree->premier;
    while (actuel != NULL){
		if(actuel->visited)
			solution[i--] = actuel->val;
		if(actuel->var == 1)
			solution[i--] = actuel->val;
        actuel = actuel->suivant;
    }
	printf("[ ");
	for(i = 1; i < sizeVar; i++)
		printf("%d, ", solution[i]);
	printf("]");
	printf("\n");
}

