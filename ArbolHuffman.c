/*
IMPLEMENTACION DE LA LIBRERIA DEL ARBOL BINARIO PARA HUFFMAN (ArbolHuffman.c)
AUTOR: Rodriguez Mendoza Christopher
VERSIÓN: 1.0

	Definición de los métodos

*/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include"TADABB.h"

arbolHuffman Inicializar (elemento E){
	arbolHuffman A = malloc(sizeof(elemento));
	(A->e)->frecuencia = E->frecuencia;
	(A->e)->caracter = E->caracter;
}

//Recibe los elementos ya ordenados
arbolHuffman CrearArbol (elemento * A, int n){
	posicion auxiliar, nuevoN, actual;
	arbolHuffman arbolesIndividuales[];
	for(int i = 0; i < n; i++){
		actual.AñadirHijo(arbolesIndividuales[i], )
	}
	
	
}

void AñadirHijo(arbolHuffman *A, izq, elemento E);