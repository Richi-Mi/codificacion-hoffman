#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {

    int frecuencia;
    char caracter;

    struct Nodo *left; // Izquierdo 0
    struct Nodo *right; // Derecho 1

} Nodo;

Nodo* init( int frecuencia, char caracter );

void addToLeft( Nodo *p, int frecuencia, char caracter );

void addToRight( Nodo *p, int frecuencia, char caracter );

Nodo* buildTree( Nodo l[], int n );

void getByteCode( Nodo *tree, char letra );