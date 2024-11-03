#include "stack.h"

typedef struct NodoArbol
{
    
    int frecuencia;
    char caracter;

    struct NodoArbol *derecha;
    struct NodoArbol *izquierda;

} NodoArbol;

typedef struct NodoLista {

    NodoArbol *subTree;

    struct NodoLista *next;

} NodoLista;

void addElementToEnd( NodoLista **p, int frecuencia, char caracter );

void insertOrderedNode( NodoLista **p, NodoLista *h );

NodoLista* createElement( int frecuencia, char caracter );

NodoArbol* buildTree( NodoLista **p );

int getByteCode( NodoArbol *h, char letra, Pila *stack );

int isByteInTheList( NodoLista **p, char byteToRead );