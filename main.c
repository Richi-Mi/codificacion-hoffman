#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

int main() {
    int  n = 6, i;
    int frecuencias[] = { 5, 9, 12, 13, 16, 45 };
    char caracteres[] = { 'f', 'e', 'c', 'b', 'd', 'a'};

    NodoLista *p = NULL;
    // Llenar el arreglo,
    for( i = 0; i < n; i++ )
        addElementToEnd( &p, frecuencias[i], caracteres[i] );
    
    NodoLista *aux = p;

    printf("Lista - pre.\n");
    while( aux != NULL ) {
        printf("| %c - %d |\n", aux -> subTree -> caracter, aux -> subTree -> frecuencia );
        aux = aux -> next;
    }
    
    NodoArbol *a = buildTree( &p );

    Pila *myStack = malloc( sizeof(Pila) );
    myStack -> tope = 0;
    myStack -> inicio = NULL;

    printf("%d\n",  a -> frecuencia );

    int b = getByteCode( a, 'f', myStack );

    showElements( myStack );
    
}