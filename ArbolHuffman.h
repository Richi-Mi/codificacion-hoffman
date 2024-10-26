/*
IMPLEMENTACION DE LA LIBRERIA DEL ARBOL BINARIO PARA HUFFMAN (ArbolHuffman.h)
AUTOR: Rodriguez Mendoza Christopher
VERSIÓN: 1.0


*/

//DEFINICIÓN DE CONSTANTES
#define TRUE 1
#define FALSE 0

//DEFINICIÓN DE ESTRUCTURAS
typedef unsigned char booleano;
typedef unsigned char byte;

typedef struct elemento
{
	int frecuencia;
	byte caracter;
	void *apellido;
} elemento;

typedef struct nodo
{
	struct nodo *izq;
	struct nodo *der;
	elemento e;
}nodo;

typedef nodo* posicion;

typedef posicion arbolHuffman;

void init (arbolHuffman *A,elemento E);

arbolHuffman CrearArbol (elemento *A, int n);

void AddHijoIzquierdo(arbolHuffman *A, elemento E);

void AddHijoDerecho(arbolHuffman *A, elemento E);
