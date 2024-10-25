/*
LIBRERIA: Cabecera de el TAD MONTICULO (ARBOL BINARIO)
AUTOR: 

DESCRIPCI�N: TAD heap
*/

//DEFINICI�N DE CONSTANTES
#define TRUE 1
#define FALSE 0

//DEFINICI�N DE ESTRUCTURAS
typedef unsigned char booleano;

typedef arbolHuffman* heap;

//DECLARACI�N DE FUNCIONES

void Inicializar(heap *A, int n);
void Insertar(heap A, arbolHuffman valor);
arbolHuffman Extraer(heap A);
void actualizarNodos(heap A, int indice);
int size(heap A);