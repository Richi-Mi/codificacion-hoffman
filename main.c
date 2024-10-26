#include<stdio.h>
#include<stdlib.h>
#include "arbol.h"
#include "helpers.h"

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
	
	Nodo nodos[tamanoArreglo];

    for( i = 0; i < tamanoArreglo; i++ ) {
        nodos[i].e.frecuencia = arreglo[i].frecuencia;
        nodos[i].e.caracter = arreglo[i].caracter;

        nodos[i].left = NULL;
        nodos[i].right = NULL;
    }
	
	//AQUI ORDENAS LOS NODOS PAI
	
	
    //arbolHuffman tree = buildTree( nodos, 6 );

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