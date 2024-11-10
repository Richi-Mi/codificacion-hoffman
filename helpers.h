#include "lista.h"



NodoLista* cargarElementos( const char *nombreArchivo, const char *texto );
void create_file_dat(NodoArbol *arbol, char *nombreArchivoTab,  const char *archivoOrigen);
NodoLista* obtenerFrecuencias(const char *nomb);
void descomprimir_archivo(NodoArbol *arbol, char *nombreArchivo, const char *nombreArchivoTab);
void showTime(double utime0, double stime0, double wtime0, double utime1, double stime1, double wtime1);