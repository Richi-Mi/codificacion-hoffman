#include <stdlib.h>
#include "arbol.c"

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
    getByteCode( tree, 'a' );
    printf("\n");
    return 0;
}