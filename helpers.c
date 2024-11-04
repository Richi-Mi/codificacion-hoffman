#include<stdio.h>
#include<stdlib.h>
#include "arbol.h"
#include "helpers.h"

NodoLista* cargarElementos(char *nombreArchivo ) {

	int j, n;
	size_t tamanioArchivo, i;
	byte byteLeido;
	NodoLista *A;
	booleano cambios;
	
	FILE *archivo = fopen(nombreArchivo, "rb"); //Abrimos el archivo en modo binario
	if (archivo == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }
	
	// Mueve el puntero del archivo al final para obtener el tamaño
    fseek(archivo, 0, SEEK_END);
    tamanioArchivo = ftell(archivo); // Obtiene el tamaño del archivo en bytes
    rewind(archivo); // Regresa el puntero al inicio

	//En nuestra estructura elemento, ya tenemos el unsigned char como atributo, entonces
    A = (NodoLista*)malloc(256 * sizeof(NodoLista));
	//Arreglo de elementos, en estos vamos a guardar los bytes que ya conocemos y su frecuencia
    if (A == NULL) {
        printf("Error al asignar memoria para el arreglo de elementos");
        fclose(archivo);
        exit(1);
    }
	
	n = 0; //Guardamos cuantos bytes llevamos guardados, ya que puede suceder que se repitan o no
	// Lee cada byte del archivo y guárdalo en el campo `caracter` de cada estructura
    for (i = 0; i < tamanioArchivo; i++) {
        fread(&byteLeido, sizeof(byte), 1, archivo);
		//Hay que verificar si este byte, ya se encuentra dentro del arreglo, si es así, solo aumentamos su frecuencia
		//Se puede optimizar usando un mapa o multiset, sin embargo, que flojera implementarlo en C, entonces hacemos 
		//una búsqueda lineal, viendo si se encuentra el elemento
		if(n == 0){
			NodoLista *t = createElement( 1, byteLeido );
			A[0] = *t;
			n++;
		}else{
			cambios = FALSE;
			for(j = 0; j < n; j++){
				if(A[j].subTree -> caracter == byteLeido){
					A[j].subTree->frecuencia++;
					cambios = TRUE;
					break;
				}
			}
			if(cambios == FALSE){
				NodoLista *new = createElement( 1, byteLeido );
				A[n] = *new;
				n++;
			}
		}
    }
	fclose(archivo);

	NodoLista *B = NULL;

    for( i = 0; i < n; i++ ) {
        NodoLista *h = createElement( A[i].subTree->frecuencia, A[i].subTree->caracter );
        insertOrderedNode( &B, h );
    } 
	return B;
}