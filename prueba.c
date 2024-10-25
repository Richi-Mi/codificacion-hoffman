#include<stdio.h>
#include<stdlib.h>
#include "ArbolHuffman.h"
#include "Heap.h"


int main() {
	int n = 6;
	int frecuencias[6] = { 45, 13, 12, 16, 9, 5 };
	int i;
	elemento e[n];
	for(i = 0; i < n; i++){
		e[i].frecuencia = frecuencias[i];
	}
	
	arbolHuffman A;
	
	A = CrearArbol(e, n);
	printf("frecuencia retornada: %d\n", A->e.frecuencia);
	
	
    return 0;
}