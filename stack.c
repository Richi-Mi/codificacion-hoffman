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
void push( Pila *myStack, unsigned char value ) {
    NodoPila *aux = myStack -> inicio;

    // Creamos el nuevo NodoPila.
    NodoPila *nuevo = malloc( sizeof( NodoPila ) );
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
        NodoPila *aux;
        
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
        NodoPila *aux = myStack -> inicio;
        while ( aux != NULL ) {
            printf("%c", aux -> value );
            aux = aux -> siguiente;
        } 
    }   
    else {
        printf("La pila esta vacia\n");
    }
}
void liberarMemoria( Pila *myStack ) {
    NodoPila *inicio = myStack -> inicio;
    while( inicio != NULL ) {
        NodoPila *aux = inicio;
        inicio = inicio -> siguiente;

        free( aux );
    }
    myStack -> tope = 0;
}