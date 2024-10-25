#include "arbol.h"

Nodo* init( int frecuencia, char caracter ) {

    // Creamos el nodo a agregar.
    Nodo *s = malloc( sizeof( int ) );
    s -> frecuencia = frecuencia;
    s -> caracter = caracter;

    s -> left = NULL;
    s -> right = NULL;

    return s;
}

void addToLeft( Nodo *p, int frecuencia, char caracter ) {
    p -> left = init( frecuencia, caracter );
}
void addToRight( Nodo *p, int frecuencia, char caracter ) {
    p -> right = init( frecuencia, caracter );
}
Nodo* buildTree( Nodo l[], int n ) {
    int i;
    
    Nodo *aux = NULL, *new; 

    for( i = 1; i < n; i++ ) {
        if( i == 1 ) {
            int nuevaFrecuencia = l[0].frecuencia + l[i].frecuencia;
            new = init( nuevaFrecuencia, ' ' );

            new -> right = (l + 1);
            new -> left = l;

            aux = new;
        }
        else {
            int nuevaFrecuencia = aux -> frecuencia + l[i].frecuencia;
            new = init( nuevaFrecuencia, ' ');

            if( aux -> frecuencia > ( l + i ) -> frecuencia ) {
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
        printf("(%c -> %d,%c -> %d): %d. \n", aux -> left -> caracter, aux -> left -> frecuencia, aux -> right -> caracter, aux -> right -> frecuencia, aux -> frecuencia );
    }
    return aux;
}
void getByteCode( Nodo *tree, char letra ) {
    // Verificamos que el arbol no sea nulo.
    if( tree == NULL )
        return;
    // Significa que no es una hoja del arbol.
    if( tree -> left != NULL && tree -> right != NULL ){
        // Caso Base.
        if( tree -> left -> caracter == letra ) {
            printf("0");
            return;
        }
        if( tree -> right -> caracter == letra ) {
            printf("1");
            return;
        }
        // Recursión
        if( tree -> left -> caracter == ' ' ){
            printf("0");   
            getByteCode( tree -> left, letra ); 
        }
        else {
            printf("1");
            getByteCode( tree -> right, letra );
        }
    }
}