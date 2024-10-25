#include<stdio.h>
#include<stdlib.h>
#include "ArbolHuffman.h"
#include "Heap.h"

int main() {

    int frecuencias[6] = { 1, 1, 1, 3, 3, 9 };
    char caracteres[6] = "glza!o";
    int i;
    Nodo nodos[6];

    for( i = 0; i < 6; i++ ) {
        nodos[i].frecuencia = frecuencias[i];
        nodos[i].caracter = caracteres[i];    
    }

    Nodo *tree = buildTree( nodos, 6 );
    getByteCode2( tree, 'a' );
    return 0;
}