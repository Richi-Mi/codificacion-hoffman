#include <stdio.h>
#include <stdlib.h>
//#include "arbol.h"
#include "helpers.h"

int main() {
	
	
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

			printf("Ingresa el nuevo nombre del archivo comprimido: \n");
			scanf("%s", nombreArchivoTab);

			//LECTURA DE ARCHIVOS POR BITS
			NodoLista *p = cargarElementos(nombreArchivo, nombreArchivoTab );
				
			NodoArbol *a = buildTree( &p );

			//Una vez creado el arbol, vamos a crear el archivo .dat (archivo comprimido)
			
			create_file_dat(a, nombreArchivoTab, nombreArchivo);
			
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
		
		break;
	}
	
    return 0;
}
