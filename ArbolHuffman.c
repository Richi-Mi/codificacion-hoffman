/*
IMPLEMENTACION DE LA LIBRERIA DEL ARBOL BINARIO PARA HUFFMAN (ArbolHuffman.c)
AUTOR: Rodriguez Mendoza Christopher
VERSIÓN: 1.0

	Definición de los métodos

*/

#include<stdio.h>
#include <stdlib.h>
#include "ArbolHuffman.h"
#include "Heap.h"

void init (arbolHuffman *A, elemento E){
	*A = malloc(sizeof(nodo));
	if (*A == NULL) {
        printf("\nError al intentar reservar memoria\n");      
        exit(1);
    }
	(*A)->e = E;
	(*A)->izq = NULL;
	(*A)->der = NULL;
}

//El código queda de la siguiente manera utilizando ayuda de un heap para no estar ordenando en cada momento
arbolHuffman CrearArbol(elemento *A, int n){//Recibe el arreglo de elementos y retorna la raiz del arbol
	int i, frecuencias;
	elemento e;
	heap minimos;
	Inicializar(&minimos, n);
	//Metemos los elementos, no es necesario que esten ordenador, ya que el heap los ordena por si mismo
	for(i = 0; i < n; i++){
		arbolHuffman arbol;
		init(&arbol, A[i]);
		Insertar(minimos, arbol);
	}
	/*
	for(i = 0; i < n-1; i++){
		arbolHuffman arbol = Extraer(minimos);
		printf("\n%d ", arbol->e.frecuencia);
	}
	*/
	while(size(minimos)>1){
		arbolHuffman arbolIzq, arbolDer, nuevo;
		arbolIzq = Extraer(minimos);
		arbolDer = Extraer(minimos);
		
		frecuencias = arbolIzq->e.frecuencia + arbolDer->e.frecuencia;
		
		//printf("\n%d ", frecuencias);
		e.frecuencia = frecuencias;
		//e.caracter = NULL;
		
		init(&nuevo, e);
		nuevo->der = arbolDer;
		nuevo->izq = arbolIzq;
		
		Insertar(minimos, nuevo);
	}
	return Extraer(minimos);
}

/*

void AddHijoIzquierdo(arbolHuffman *A, elemento E){
	init(&((*A)->izq), E);
}

void AddHijoDerecho(arbolHuffman *A, elemento E){
	init(&((*A)->der), E);
}
*/