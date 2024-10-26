#include<stdio.h>
#include<stdlib.h>
#include "ArbolHuffman.h"
#include "Heap.h"


int main() {
	//LECTURA DE ARCHIVOS POR BITS
	int tamanoArreglo, i;
	char nombreArchivo[20];
	
	printf("Ingresa el nombre del archivo a leer en bits: \n");
	scanf("%s", nombreArchivo);
	
	elemento *arreglo = cargarElementos(nombreArchivo, &tamanoArreglo);
	
	for(i = 0; i < tamanoArreglo; i++){
		printf("Elemento %d: caracter = %02X\n Y frecuencia: %d\n", i, arreglo[i].caracter, arreglo[i].frecuencia);
	}
	/*
	arbolHuffman A;
	
	A = CrearArbol(arreglo, tamanoArreglo);
	printf("frecuencia retornada: %d\n", A->e.frecuencia);
	*/
	
    return 0;
}
