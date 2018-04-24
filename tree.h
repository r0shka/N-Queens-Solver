#ifndef __TREE__
#define __TREE__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Element Element;
struct Element
{
    int var;
	int val;
	int visited;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};

Liste *create(int var, int val, int visit);
void addElem(Liste *liste, int var, int val, int visit);
void removeElem(Liste *liste);
void print(Liste *liste);
void showSolution(Liste *tree, int sizeVar);

#endif
