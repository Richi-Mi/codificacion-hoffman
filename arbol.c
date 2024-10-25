#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {

    int frecuencia;
    char caracter;

    struct Nodo *left; // Izquierdo 0
    struct Nodo *right; // Derecho 1

} Nodo;

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
        // printf("(%c -> %d,%c -> %d): %d. \n", aux -> left -> caracter, aux -> left -> frecuencia, aux -> right -> caracter, aux -> left -> frecuencia, aux -> frecuencia );
    }
    return aux;
}
void getByteCode( Nodo *tree, char letra ) {
    // Verificamos que el arbol no sea nulo.
    if( tree == NULL )
        return;
    
    if( tree -> left != NULL && tree -> right != NULL ){
        printf("Hola");
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
void getByteCode2(Nodo *tree, char letra) {
    if (tree == NULL) {
        printf("Nodo nulo encontrado.\n");
        return;
    }

    printf("Visitando nodo con caracter: %c\n", tree->caracter);

    if (tree->caracter == letra) {
        printf("Caracter encontrado: %c\n", letra);
        return;
    }

    if (tree->left != NULL) {
        if (tree->left->caracter == letra) {
            printf("Caracter encontrado en hijo izquierdo: %c\n", letra);
            printf("0");
            return;
        }
        getByteCode(tree->left, letra);
    } else {
        printf("Hijo izquierdo nulo.\n");
    }

    if (tree->right != NULL) {
        if (tree->right->caracter == letra) {
            printf("Caracter encontrado en hijo derecho: %c\n", letra);
            printf("1");
            return;
        }
        getByteCode(tree->right, letra);
    } else {
        printf("Hijo derecho nulo.\n");
    }
}
