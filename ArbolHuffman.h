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
} elemento;

typedef struct nodo
{
	struct nodo *izq;
	struct nodo *der;
	elemento e;
}nodo;

typedef nodo* posicion;

typedef posicion arbolHuffman;

arbolHuffman Inicializar (elemento E);

void CrearArbol (arbolHuffman *A);

void AñadirHijo(arbolHuffman *A, izq, elemento E);
