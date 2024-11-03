#include<stdio.h>
#include<stdlib.h>

#include "lista.h"

//DEFINICIÓN DE CONSTANTES
#define TRUE 1
#define FALSE 0

//DEFINICIÓN DE ESTRUCTURAS
typedef unsigned char boolean;
typedef unsigned char byte;

/**
 * @author Rodriquez Mendoza Cristofer.
 * @author Mendoza Castañeda José Ricardo.
 * 
 * Carga un arreglo de NodoLista ordenados y listos para construir el arbol.
 */
void cargarElementos( NodoLista **p, char *nombreArchivo, int *tamanoArreglo){

	size_t tamanioArchivo, i;
	byte byteLeido;
	NodoLista *A;
	boolean cambios;
	
	FILE *archivo = fopen( nombreArchivo, "rb" ); //Abrimos el archivo en modo binario
	if (archivo == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }
	
	// Mueve el puntero del archivo al final para obtener el tamaño
    fseek(archivo, 0, SEEK_END);
    tamanioArchivo = ftell(archivo); // Obtiene el tamaño del archivo en bytes
    rewind(archivo); // Regresa el puntero al inicio

	*tamanoArreglo = 0; //Guardamos cuantos bytes llevamos guardados, ya que puede suceder que se repitan o no
	// Lee cada byte del archivo y guárdalo en el campo `caracter` de cada estructura
    for (i = 0; i < tamanioArchivo; i++) {

        fread(&byteLeido, sizeof(byte), 1, archivo);
		//Hay que verificar si este byte, ya se encuentra dentro del arreglo, si es así, solo aumentamos su frecuencia
		//Se puede optimizar usando un mapa o multiset, sin embargo, que flojera implementarlo en C, entonces hacemos 
		//una búsqueda lineal, viendo si se encuentra el elemento

		if(*tamanoArreglo == 0){
			addElementToEnd( p, 1, byteLeido );
			(*tamanoArreglo)++;
		}
		else{
			cambios = isByteInTheList( p, byteLeido );

			if(cambios == FALSE){
				addElementToEnd( p, 1, byteLeido );
				(*tamanoArreglo)++;
			}
		}
    }
	fclose(archivo);
}