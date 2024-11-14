// DEFINICIÓN DE CONSTANTES
#define TRUE 1 // Valor para representar verdadero
#define FALSE 0 // Valor para representar falso

// DEFINICIÓN DE ESTRUCTURAS

// Estructura para representar un elemento de la tabla de Huffman
typedef unsigned char booleano; // Tipo para representar un valor booleano (TRUE o FALSE)
typedef unsigned char byte; // Tipo para representar un byte

// Estructura que almacena un carácter y su correspondiente código binario (en forma de cadena)
typedef struct elemento {
    byte caracter; // Carácter representado por el elemento
    char* bytes; // Código binario del carácter
} elemento;

// Estructura para representar un nodo de un árbol en el algoritmo de Huffman
typedef struct NodoArbol {
    int frecuencia; // Frecuencia de aparición del carácter
    unsigned char caracter; // Carácter almacenado en el nodo
    struct NodoArbol *derecha; // Puntero al subárbol derecho
    struct NodoArbol *izquierda; // Puntero al subárbol izquierdo
} NodoArbol;

// Estructura para representar un nodo de una lista vinculada que contiene un subárbol de Huffman
typedef struct NodoLista {
    NodoArbol *subTree; // Subárbol contenido en el nodo de la lista
    struct NodoLista *next; // Puntero al siguiente nodo en la lista
} NodoLista;

// FUNCIONES

// Agrega un elemento al final de la lista de nodos
void addElementToEnd( NodoLista **p, int frecuencia, unsigned char caracter );

// Inserta un nodo en la lista de nodos de manera ordenada por la frecuencia del subárbol
void insertOrderedNode( NodoLista **p, NodoLista *h );

// Crea un nuevo nodo de la lista con un subárbol de Huffman
NodoLista* createElement( int frecuencia, unsigned char caracter );

// Construye el árbol de Huffman a partir de la lista de nodos
NodoArbol* buildTree( NodoLista **p );

// Genera el código binario (en forma de cadena) para cada carácter en el árbol de Huffman
void getByteCode( NodoArbol *h, elemento *dic[256], char** cad);

// Verifica si un byte ya está en la lista de nodos
int isByteInTheList( NodoLista **p, unsigned char byteToRead );

// Suma las frecuencias de todos los nodos en un árbol de Huffman
int sumaFrecuencia( NodoArbol *h);

