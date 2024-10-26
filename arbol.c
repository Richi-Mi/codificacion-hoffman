#include "arbol.h"
#include<stdio.h>
#include <stdlib.h>
arbolHuffman init( elemento e ){

    // Creamos el nodo a agregar.
    arbolHuffman s = malloc( sizeof( Nodo ) );
    s -> e = e;

    s -> left = NULL;
    s -> right = NULL;

    return s;
}

void addToLeft( arbolHuffman p, elemento E ){
    p -> left = init( E );
}
void addToRight( arbolHuffman p, elemento E ){
    p -> right = init( E );
}
arbolHuffman buildTree( Nodo l[], int n ) {
    int i;
    
    arbolHuffman aux = NULL, new; 
	elemento e;

    for( i = 1; i < n; i++ ) {
        if( i == 1 ) {
            int nuevaFrecuencia = l[0].e.frecuencia + l[i].e.frecuencia;
			e.frecuencia = nuevaFrecuencia;
			//e.caracter = NULL; //Aqui hay que poner cual va a ser el valor nulo del byte
            new = init( e );

            new -> right = (l + 1);
            new -> left = l;

            aux = new;
        }
        else {
            int nuevaFrecuencia = aux ->e.frecuencia + l[i].e.frecuencia;
			e.frecuencia = nuevaFrecuencia;
			//e.caracter = NULL; //Aqui hay que poner cual va a ser el valor nulo del byte
            new = init( e );

            if( aux ->e.frecuencia > ( l + i )->e. frecuencia ) {
                new -> right = aux;
                new -> left = l + i;    
            }
            else {
                new -> right = l + i;
                new -> left = aux;
            }
            aux = new;
            
        }
        // Comprobación del arbol
        //printf("(%c -> %d,%c -> %d): %d. \n", aux -> left -> e.caracter, aux -> left -> e.frecuencia, aux -> right ->e.caracter, aux -> right ->e. frecuencia, aux -> frecuencia );
        printf("(%d, %d): %d. \n", aux -> left -> e.frecuencia, aux -> right ->e. frecuencia, aux ->e. frecuencia );
    }
    return aux;
}
void getByteCode( arbolHuffman tree, byte letra ) {
    // Verificamos que el arbol no sea nulo.
    if( tree == NULL )
        return;
    // Significa que no es una hoja del arbol.
    if( tree -> left != NULL && tree -> right != NULL ){
        // Caso Base.
        if( tree -> left ->e. caracter == letra ) {
            printf("0");
            return;
        }
        if( tree -> right -> e.caracter == letra ) {
            printf("1");
            return;
        }
        // Recursión
        if( tree -> left -> e.caracter == 0 ){ //suponiendo que nuestro byte nulo es cero
            printf("0");   
            getByteCode( tree -> left, letra ); 
        }
        else {
            printf("1");
            getByteCode( tree -> right, letra );
        }
    }
}