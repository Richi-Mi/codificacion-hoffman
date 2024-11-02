#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/**
 * @param Pila Pila a evaluar.
 * Evalua si la pila esta vacia o no
 * @return 0 o 1
*/
int isEmpty( Pila *myStack ) {
    return myStack -> tope == 0;
}
void push( Pila *myStack, char value ) {
    Nodo *aux = myStack -> inicio;

    // Creamos el nuevo Nodo.
    Nodo *nuevo = malloc( sizeof( Nodo ) );
    nuevo -> value = value;

    if( aux == NULL ) {
        nuevo -> siguiente = NULL;
        myStack -> inicio = nuevo;
    }
    else {
        nuevo -> siguiente = aux;
        myStack -> inicio = nuevo;
    }
    myStack -> tope++;
}
void pop( Pila *myStack ) {
    if( !isEmpty( myStack ) ) {
        Nodo *aux;
        
        aux = myStack -> inicio;

        myStack -> inicio = myStack -> inicio -> siguiente;

        free( aux );   
    }
    else {
        printf("La pila esta vacia\n");
    }
}
void showElements( Pila *myStack ) {
    if( !isEmpty( myStack ) ) {
        Nodo *aux = myStack -> inicio;
        while ( aux != NULL ) {
            printf("%c, ", aux -> value );
            aux = aux -> siguiente;
        } 
    }   
    else {
        printf("La pila esta vacia\n");
    }
}
void liberarMemoria( Pila *myStack ) {
    Nodo *inicio = myStack -> inicio;
    while( inicio != NULL ) {
        Nodo *aux = inicio;
        inicio = inicio -> siguiente;

        free( aux );
    }
    myStack -> tope = 0;
}