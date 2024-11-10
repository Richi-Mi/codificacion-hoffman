#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "helpers.h"

#include "lista.h"

NodoArbol* buildTree( NodoLista **p ) {

    if( *p == NULL ) 
        return NULL;
    
    while ( (*p) -> next != NULL ) {
        NodoArbol *newTree = malloc( sizeof( NodoArbol ) );
        //newTree -> isLetter = 0;
        newTree -> frecuencia = ( (*p) -> subTree -> frecuencia ) + ( (*p) -> next -> subTree -> frecuencia );

        newTree -> izquierda = (*p) -> subTree;
        newTree -> derecha = (*p) -> next -> subTree;

        NodoLista *listItem = malloc( sizeof( NodoLista ) );
        listItem -> subTree = newTree;
        
        insertOrderedNode( p, listItem );

        NodoLista *aux = *p;

        (*p) = (*p) -> next -> next;
        free( aux -> next );
        free( aux );
    }

    return (*p) -> subTree;
    

}
void insertOrderedNode(NodoLista **p, NodoLista *h) {
    if( *p == NULL ) {
        *p = h;
        return;
    }
    NodoLista *aux = *p;
    NodoLista *ant = NULL;

    // Recorrer la lista hasta encontrar la posición correcta para h
    while (aux != NULL && (aux->subTree->frecuencia) <= (h->subTree->frecuencia)) {
        ant = aux;
        aux = aux->next;
    }

    // insertar al inicio de la lista o antes del primer elemento
    if (ant == NULL) {
        h->next = *p;
        *p = h;
    }
    // insertar entre nodos o al final de la lista
    else {
        ant->next = h;
        h->next = aux;
    }
}


NodoLista* createElement( int frecuencia, unsigned char caracter ) {
    // Crear el elemento a agregar.
    NodoArbol *na = malloc( sizeof( NodoArbol ) );
    na -> caracter = caracter;
    //na -> isLetter = 1;
    na -> frecuencia = frecuencia;

    na -> derecha = NULL;
    na -> izquierda = NULL;

    NodoLista *nl = malloc( sizeof( NodoLista ) );
    nl -> subTree = na;
    nl -> next = NULL;

    return nl;
}

void addElementToEnd( NodoLista **p, int frecuencia, unsigned char caracter ) {
    NodoLista *nl = createElement( frecuencia, caracter );
    // Comprobamos si es el primer elemento.
    if( *p == NULL ) 
        *p = nl;
    else {
        NodoLista *aux = *p;
        
        while( aux -> next != NULL ) 
            aux = aux -> next;
        
        aux -> next = nl;
    }

}

void agregarCaracter(char** cadena, char caracter) {
    size_t longitud = strlen(*cadena);

    // Reasignar memoria para la cadena con espacio adicional
    *cadena = realloc(*cadena, longitud + 2);  // +2 para el nuevo carácter y '\0'
    if (*cadena == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(1);
    }

    // Añadir el nuevo carácter y el terminador de cadena
    (*cadena)[longitud] = caracter;
    (*cadena)[longitud + 1] = '\0';
}

void getByteCode( NodoArbol *h, elemento *dic[256], char** cad){
	if (h == NULL) {
        return;
    }
	// Caso Base
    if( h -> izquierda == NULL && h -> derecha == NULL ){ //Significa que es una hoja
		elemento *e = malloc(sizeof(elemento));
		e->caracter = h->caracter;
		e->bytes = strdup(*cad);
		dic[e->caracter] = e;
		//printf("%c - %s\n", e->caracter, e->bytes);
        return;
	}
	//Hacemos recursión a la izquierda y a la derecha
	if(h->izquierda != NULL){
		agregarCaracter(cad, '0');
		//printf("%s\n", *cad);
		getByteCode(h->izquierda, dic, cad);
		(*cad)[strlen(*cad) - 1] = '\0';
	}
		
	if(h->derecha != NULL){
		agregarCaracter(cad, '1');
		//printf("%s\n", *cad);
		getByteCode(h->derecha, dic, cad);
		(*cad)[strlen(*cad) - 1] = '\0';
	}
}


/*
int getByteCode( NodoArbol *h, unsigned char letra, Pila *stack ) {

    // Caso Base
    if( h -> izquierda == NULL && h -> derecha == NULL )
        return 0;
    
    if( h -> izquierda -> caracter == letra ) {
        push( stack, '0');
        return 1;
    }
    if( h -> derecha -> caracter == letra ) {
        push( stack, '1' );
        return 1;
    }

    // Recursiòn.
    push(stack, '0');
    int ri = getByteCode( h -> izquierda, letra, stack);

    if( ri != 1 )
        pop( stack );
        
    push( stack, '1');
    int rd = getByteCode( h -> derecha, letra, stack);
    
    if( rd != 1 )
        pop( stack );
        
    if( rd == 1 || ri == 1 )
        return 1;
        
    else 
        return 0;
}
int isByteInTheList( NodoLista **p, unsigned char byteToRead ) {
    NodoLista *aux = *p;
        
    while( aux != NULL ) {
        if( aux -> subTree -> caracter == byteToRead ) {
            aux -> subTree -> frecuencia += 1;
            return 1;
        }
        aux = aux -> next;
    }

    return 0;
}*/