// Implementación de pilas dinamicas
typedef struct Nodo { 
    char value;
    struct Nodo *siguiente;
} Nodo;

typedef struct Pila {
    struct Nodo *inicio;
    int tope;
} Pila;

int isEmpty( Pila *myStack );

void push( Pila *myStack, char value );

void pop( Pila *myStack );

void showElements( Pila *myStack );

void liberarMemoria( Pila *myStack );