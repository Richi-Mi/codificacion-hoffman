#include <stdio.h>
#include <stdlib.h>
//#include "arbol.h"
#include "helpers.h"
#include "tiempo.h"
/*
descripcion:
Este programa implementa la codificación y decodificación de archivos utilizando el algoritmo de Huffman.
Permite al usuario comprimir y descomprimir archivos binarios a través de dos opciones:
1. Comprimir un archivo: Se carga el archivo, se construye el árbol de Huffman y se guarda el archivo comprimido en formato .dat.
2. Descomprimir un archivo: Se lee un archivo comprimido, se construye el árbol de Huffman y se obtiene el archivo original.
El programa mide el tiempo de ejecución de cada operación y lo muestra al final.
*/
int main() {
	double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medicion de tiempos
	
	int tamanoArreglo, i, opcion;
	char nombreArchivo[20], nombreArchivoTab[20];
	
	printf("Bienvenido a nuestra codificación por hoffman");
	printf("\n¿Qué deseas hacer?");
	printf("\n1. Comprimir un archivo");
	printf("\n2. Descomprimir un archivo\n");
	scanf("%d", &opcion);
	switch(opcion){
		case 1:
			printf("Ingresa el nombre del archivo a leer en bits: \n");
			scanf("%s", nombreArchivo);

			printf("Ingresa el nuevo nombre del archivo comprimido sin extensión: \n");
			scanf("%s", nombreArchivoTab); //Donde se guardara
			
			
			uswtime(&utime0, &stime0, &wtime0);
			
			//LECTURA DE ARCHIVOS POR BITS
			NodoLista *p = cargarElementos(nombreArchivo, nombreArchivoTab );
				
			NodoArbol *a = buildTree( &p );

			//Una vez creado el arbol, vamos a crear el archivo .dat (archivo comprimido)
			
			create_file_dat(a, nombreArchivoTab, nombreArchivo);
			
			uswtime(&utime1, &stime1, &wtime1);
			//Terminamos de medir el tiempo
			/*
			Pila *myStack = malloc( sizeof(Pila) );
			myStack -> tope = 0;
			myStack -> inicio = NULL;

			//arbolHuffman tree = buildTree( nodos, 6 );
			getByteCode( a, 'e', myStack );

			showElements( myStack );
			// getByteCode( tree, 'l' );*/
		break;
		case 2:
			printf("Ingresa el nombre del archivo a descomprimir sin extensión: \n");
			scanf("%s", nombreArchivo);
			
			printf("Ingresa el nombre del archivo descomprimido con extensión: \n");
			scanf("%s", nombreArchivoTab);
			uswtime(&utime0, &stime0, &wtime0);
			//Obtenemos las frecuencias y caracteres del archivo tab
			NodoLista *listas = obtenerFrecuencias(nombreArchivo);
			//Construimos el arbol
			NodoArbol *arbol = buildTree( &listas );
			//Con ayuda del arbol, leemos el archivo dat
			descomprimir_archivo(arbol, nombreArchivo, nombreArchivoTab);
			uswtime(&utime1, &stime1, &wtime1);
			
		break;
	}
	showTime(utime0, stime0, wtime0, utime1, stime1, wtime1); // Imprime los tiempos
    return 0;
}
