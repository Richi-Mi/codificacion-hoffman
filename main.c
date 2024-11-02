#include <stdio.h>
#include <stdlib.h>

#include "arbol.c"

void addTreeLef( NodoArbol **p, int f, char c ){

    NodoArbol *new = (NodoArbol *) malloc(sizeof(NodoArbol));

    new -> frecuencia = f;
    new -> caracter = c;
    new -> sig = NULL;

    if (*p == NULL){
        *p = new;
    }

    else{
        
        // aux -> Accede al valor al que apunta 'p' (dirección de estructura)
        NodoArbol *aux = *p;

        // Pregunta sobre el nodo siguiente al que esta apunta
        while (aux -> sig != NULL){
            // aux apunta al siguiente NODO
            aux = aux->sig;
        }
        // Lo enlazamos como siguiente de 'aux'
        aux->sig = new;

    }
}

int main() {

    int frecuencias[6] = { 1, 1, 1, 3, 3, 9 };
    char caracteres[6] = "glza!o";
    int i;
    NodoArbol *p = NULL;

    for( i = 0; i < 6; i++ ) {
        addTreeLef( &p, frecuencias[i], caracteres[i] );
    }

    // Construccion del arbol
    buildTree( p );

    mostrar( p );

    // NodoArbol *tree = buildTree( nodos, 6 );
    //getByteCode( p, '0' );
    printf("\n");
    return 0;
}