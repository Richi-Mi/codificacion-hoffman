/*
LIBRERIA: Cabecera de el TAD MONTICULO (ARBOL BINARIO)
AUTOR: 

DESCRIPCIÓN: TAD heap
*/

//DEFINICIÓN DE CONSTANTES
#define TRUE 1
#define FALSE 0

//DEFINICIÓN DE ESTRUCTURAS
typedef unsigned char booleano;

typedef arbolHuffman* heap;

//DECLARACIÓN DE FUNCIONES

void Inicializar(heap *A, int n);
void Insertar(heap A, arbolHuffman valor);
arbolHuffman Extraer(heap A);
void actualizarNodos(heap A, int indice);
int size(heap A);