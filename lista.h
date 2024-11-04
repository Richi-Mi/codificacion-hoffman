#include "stack.h"

typedef struct NodoArbol
{
    
    int frecuencia;
    unsigned char caracter;
    unsigned char isLetter;

    struct NodoArbol *derecha;
    struct NodoArbol *izquierda;

} NodoArbol;

typedef struct NodoLista {

    NodoArbol *subTree;

    struct NodoLista *next;

} NodoLista;

void addElementToEnd( NodoLista **p, int frecuencia, unsigned char caracter );

void insertOrderedNode( NodoLista **p, NodoLista *h );

NodoLista* createElement( int frecuencia, unsigned char caracter );

NodoArbol* buildTree( NodoLista **p );

int getByteCode( NodoArbol *h, unsigned char letra, Pila *stack );

int isByteInTheList( NodoLista **p, unsigned char byteToRead );