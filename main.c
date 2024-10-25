#include<stdio.h>
#include<stdlib.h>
#include "ArbolHuffman.h"
#include "Heap.h"
#include "arbol.h"

int main() {

    int frecuencias[6] = { 5, 9, 12, 13, 16, 45 };
    char caracteres[6] = "fecbda";
    int i;
    Nodo nodos[6];

    for( i = 0; i < 6; i++ ) {
        nodos[i].frecuencia = frecuencias[i];
        nodos[i].caracter = caracteres[i];    

        nodos[i].left = NULL;
        nodos[i].right = NULL;
    }

    Nodo *tree = buildTree( nodos, 6 );

    // getByteCode( tree, 'l' );
    return 0;
}