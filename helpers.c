#include<stdio.h>
#include<stdlib.h>
#include "arbol.h"

elemento* cargarElementos(char *nombreArchivo, int *tamanoArreglo){
	int j;
	size_t tamanioArchivo, i;
	byte byteLeido;
	elemento *A;
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
    A = (elemento*)malloc(256 * sizeof(elemento));
	//Arreglo de elementos, en estos vamos a guardar los bytes que ya conocemos y su frecuencia
    if (A == NULL) {
        printf("Error al asignar memoria para el arreglo de elementos");
        fclose(archivo);
        exit(1);
    }
	
	*tamanoArreglo = 0; //Guardamos cuantos bytes llevamos guardados, ya que puede suceder que se repitan o no
	// Lee cada byte del archivo y guárdalo en el campo `caracter` de cada estructura
    for (i = 0; i < tamanioArchivo; i++) {
        fread(&byteLeido, sizeof(byte), 1, archivo);
		//Hay que verificar si este byte, ya se encuentra dentro del arreglo, si es así, solo aumentamos su frecuencia
		//Se puede optimizar usando un mapa o multiset, sin embargo, que flojera implementarlo en C, entonces hacemos 
		//una búsqueda lineal, viendo si se encuentra el elemento
		if(*tamanoArreglo == 0){
			A[0].caracter = byteLeido;
			A[0].frecuencia = 1;
			(*tamanoArreglo)++;
		}else{
			cambios = FALSE;
			for(j = 0; j < *tamanoArreglo; j++){
				if(A[j].caracter == byteLeido){
					A[j].frecuencia++;
					cambios = TRUE;
					break;
				}
			}
			if(cambios == FALSE){
				A[*tamanoArreglo].caracter = byteLeido;
				A[*tamanoArreglo].frecuencia = 1;
				(*tamanoArreglo)++;
			}
		}
    }
	fclose(archivo);
	return A;
}