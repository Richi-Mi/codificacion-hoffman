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


/* CÓDIGO DE PRUEBA
    int frecuencias[6] = { 5, 9, 12, 13, 16, 45 };
    char caracteres[6] = "fecbda";
    int i;
    Nodo nodos[6];

    for( i = 0; i < 6; i++ ) {
        nodos[i].e.frecuencia = frecuencias[i];
        //nodos[i].e.caracter = caracteres[i];    

        nodos[i].left = NULL;
        nodos[i].right = NULL;
    }
 */