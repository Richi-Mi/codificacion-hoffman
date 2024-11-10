#include "stack.h"

//DEFINICIÓN DE CONSTANTES
#define TRUE 1
#define FALSE 0

//DEFINICIÓN DE ESTRUCTURAS
typedef unsigned char booleano;
typedef unsigned char byte;

typedef struct elemento
{
	//int frecuencia;
	byte caracter;
	char* bytes;
} elemento;

typedef struct NodoArbol
{
    
    int frecuencia;
    unsigned char caracter;
    //unsigned char isLetter;

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

//int getByteCode( NodoArbol *h, unsigned char letra, Pila *stack );
void getByteCode( NodoArbol *h, elemento *dic[256], char** cad);

int isByteInTheList( NodoLista **p, unsigned char byteToRead );
