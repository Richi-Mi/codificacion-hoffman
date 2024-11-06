// Implementación de pilas dinamicas
typedef struct NodoPila { 
    unsigned char value;
    struct NodoPila *siguiente;
} NodoPila;

typedef struct Pila {
    struct NodoPila *inicio;
    int tope;
} Pila;

int isEmpty( Pila *myStack );

void push( Pila *myStack, unsigned char value );

void pop( Pila *myStack );

void showElements( Pila *myStack );

void liberarMemoria( Pila *myStack );