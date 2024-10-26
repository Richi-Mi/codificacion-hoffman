
//DEFINICIÓN DE CONSTANTES
#define TRUE 1
#define FALSE 0

//DEFINICIÓN DE ESTRUCTURAS
typedef unsigned char booleano;
typedef unsigned char byte;

typedef struct elemento
{
	int frecuencia;
	byte caracter;
	void *apellido;
} elemento;

typedef struct Nodo {

	elemento e;

    struct Nodo *left; // Izquierdo 0
    struct Nodo *right; // Derecho 1

} Nodo;

typedef Nodo* posicion;

typedef posicion arbolHuffman;

//DEFINICIÓN DE FUNCIONES

arbolHuffman init( elemento e );

void addToLeft( arbolHuffman p, elemento E );

void addToRight( arbolHuffman p, elemento E );

arbolHuffman buildTree( Nodo l[], int n );

void getByteCode( arbolHuffman tree, byte letra );