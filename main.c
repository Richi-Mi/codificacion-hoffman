#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "helpers.h"

int main() {
	
	//LECTURA DE ARCHIVOS POR BITS
	int tamanoArreglo, i;
	char nombreArchivo[20], nombreArchivoTab[20];
	
	printf("Ingresa el nombre del archivo a leer en bits: \n");
	scanf("%s", nombreArchivo);

    printf("Ingresa el nombre del archivo a leer en bits: \n");
	scanf("%s", nombreArchivoTab);
	
	NodoLista *p = cargarElementos(nombreArchivo, nombreArchivoTab );
	
	
	//AQUI ORDENAS LOS NODOS PAI
	
	NodoArbol *a = buildTree( &p );

    Pila *myStack = malloc( sizeof(Pila) );
    myStack -> tope = 0;
    myStack -> inicio = NULL;

    //arbolHuffman tree = buildTree( nodos, 6 );
    getByteCode( a, 'e', myStack );

    showElements( myStack );
    // getByteCode( tree, 'l' );
    return 0;
}
