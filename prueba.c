#include<stdio.h>
#include<stdlib.h>
#include "ArbolHuffman.h"
#include "Heap.h"


/*
void InOrden(arbolbin *a, posicion p);
Descripción: Recibe un arbol y una posicion, recorre y guarda dentro de un arreglo 
Recibe: arbolbin * A (referencia al arbol a operar), posicion P (posicion en la que se realizara el recorrido)
Devuelve:
Observaciones: El arbol no debe estar vacio
*/
void InOrden(arbolHuffman *a, posicion p){ //izquierda - yo - derecha
	if(p != NULL && *a != NULL){
		InOrden(a, (*a)->izq);
		printf(" %d -", (*a)->e.frecuencia);
		InOrden(a, (*a)->izq);
	}
}

int main() {
	int n = 6;
	int frecuencias[6] = { 3, 1, 9, 3, 1, 1 };
	int i;
	elemento e[n];
	for(i = 0; i < n; i++){
		e[i].frecuencia = frecuencias[i];
	}
	
	arbolHuffman A;
	
	printf("Hola\n");
	A = CrearArbol(e, n);
	printf("Hola3\n");
	InOrden(&A, A);
	
    return 0;
}