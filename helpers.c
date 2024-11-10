#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "arbol.h"
#include "helpers.h"
#include "bit.h"

void createFileTab( const char *nombreArchivo, char *texto ) {
    FILE *file = fopen(nombreArchivo, "a");
    if (file == NULL) {
        printf("Error al abrir el archivo");
        return;
    }

    // Escribimos el texto deseado en el archivo
    fprintf( file, "%s\n", texto );

    // Cerramos el archivo después de escribir
    fclose(file);
}


NodoLista* cargarElementos( const char *nombreArchivo, const char *nombreTab ) {
	int j, n;
	size_t tamanioArchivo, i;
	byte byteLeido;
	NodoLista *A;
	booleano cambios;
	char aux[20];
	strcpy(aux, nombreTab);
	strcat(aux, ".tab");  // Aseguramos que el nombre incluya la extensión ".tab"
	FILE *archivo = fopen( nombreArchivo, "rb"); // Abrimos el archivo en modo binario
	FILE *archivoTab = fopen( aux, "w" );

	if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

	if (archivoTab == NULL) {
        printf("Error al abrir el archivo .tab para escribir\n");
        fclose(archivo);
        return NULL;
    }

	// Mueve el puntero del archivo al final para obtener el tamaño
    fseek(archivo, 0, SEEK_END);
    tamanioArchivo = ftell(archivo); // Obtiene el tamaño del archivo en bytes
    rewind(archivo); // Regresa el puntero al inicio

	// Creamos el arreglo de elementos
    A = (NodoLista*)malloc(256 * sizeof(NodoLista));
    if (A == NULL) {
        printf("Error al asignar memoria para el arreglo de elementos\n");
        fclose(archivo);
        fclose(archivoTab);
        exit(1);
    }
	
	for(i = 0; i < 256; i++){
		NodoLista *t = createElement(0, i);
		A[i] = *t;
	}
	
    for (i = 0; i < tamanioArchivo; i++) {
        fread(&byteLeido, sizeof(byte), 1, archivo);
		A[byteLeido].subTree->frecuencia++;
		/*
		if (n == 0) {
			NodoLista *t = createElement( 1, byteLeido );
			A[0] = *t;
			n++;
		} else {
			cambios = FALSE;
			for (j = 0; j < n; j++) {
				if (A[j].subTree->caracter == byteLeido) {
					A[j].subTree->frecuencia++;
					cambios = TRUE;
					break;
				}
			}
			if (cambios == FALSE) {
				NodoLista *new = createElement( 1, byteLeido );
				A[n] = *new;
				n++;
			}
		}*/
    }
	fclose(archivo);

	NodoLista *B = NULL;
    for (i = 0; i < 256; i++) {
		if(A[i].subTree->frecuencia != 0){
			NodoLista *h = createElement(A[i].subTree->frecuencia, A[i].subTree->caracter);
			fprintf(archivoTab, "%u,%d\n", h->subTree->caracter, h->subTree->frecuencia);
			insertOrderedNode(&B, h);
		}
    }
	
	fclose(archivoTab);  // Cerramos el archivo .tab después de escribir
	return B;
}

NodoLista* obtenerFrecuencias(const char *nomb){
	int j, i, numero;
	byte byteLeido;
	NodoLista *A;
	char archivo_tab[20];
	strcpy(archivo_tab, nomb);
	strcat(archivo_tab, ".tab");
	FILE *archivo = fopen(archivo_tab, "r");
	
	NodoLista *B = NULL;
	
	while(fscanf(archivo, "%u,%d\n", &byteLeido, &numero) == 2){
		NodoLista *h = createElement(numero, byteLeido);
		insertOrderedNode( &B, h );
		//printf("%c - %d\n", byteLeido, numero);
	}
	fclose(archivo);
	return B;
}

void create_file_dat(NodoArbol *arbol, char *nombreArchivo, const char *archivoOrigen) {
    // Abrimos el archivo
    strcat(nombreArchivo, ".dat");
    FILE *archivoOri = fopen(archivoOrigen, "rb"); // Modo lectura en bits
    FILE *archivoDat = fopen(nombreArchivo, "wb"); // Modo escritura en bits

    // Obtenemos la codificación de cada byte
    elemento *diccionario[256] = {NULL};
    char *cad = malloc(1);
    cad[0] = '\0';

    getByteCode(arbol, diccionario, &cad); // Buscamos en todo el árbol y guardamos en el diccionario

    // Mueve el puntero al final para obtener el tamaño
    fseek(archivoOri, 0, SEEK_END);
    size_t tamanioArchivo = ftell(archivoOri); // Obtiene el tamaño en bytes
    rewind(archivoOri);

    // Reserva para 8 bits por cada byte en el archivo
    size_t bitsTotales = tamanioArchivo * 8;  
    byte *buffer = malloc((bitsTotales / 8) + 1);  // Espacio para la codificación completa
    if (buffer == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }

    size_t bitPos = 0;
    byte byteLeido;

    // Construir la codificación en una sola pasada
    for (size_t i = 0; i < tamanioArchivo; i++) {
        fread(&byteLeido, sizeof(byte), 1, archivoOri);
        const char *codigo = diccionario[byteLeido]->bytes;

        // Insertar cada bit en el buffer de salida
        for (size_t j = 0; j < strlen(codigo); j++) {
            if (codigo[j] == '1'){
				PONE_1(buffer[bitPos / 8], 7 - (bitPos % 8));//byte, posición
                //buffer[bitPos / 8] |= (1 << (7 - (bitPos % 8)));
			}else{
				PONE_0(buffer[bitPos / 8], 7 - (bitPos % 8));//byte, posición
			}
            bitPos++;
        }
    }

    // Escribir el buffer en el archivo de salida
    fwrite(buffer, sizeof(byte), (bitPos + 7) / 8, archivoDat);

    // Liberar memoria y cerrar archivos
    free(buffer);
    free(cad);
    fclose(archivoOri);
    fclose(archivoDat);
}



void descomprimir_archivo(NodoArbol *arbol, char *nombreArchivo, const char *archivoDescomprimido){
	//Abrimos el archivo dat y en escritura el archivo original
	strcat(nombreArchivo, ".dat");
	FILE *archivoDat = fopen(nombreArchivo, "rb");
	FILE *archivo = fopen(archivoDescomprimido, "wb");
	 // Validar apertura de archivos
    if (archivoDat == NULL || archivo == NULL) {
        perror("Error al abrir los archivos");
        return;
    }
	//Empezamos a leer bit por bit, y vamos mandando a nuestro arbol, hasta llegar a una hoja e imprimimos la letra
	//obtenida en ese momento
	// Mueve el puntero del archivo al final para obtener el tamaño
    fseek(archivoDat, 0, SEEK_END);
    size_t tamanioArchivo = ftell(archivoDat); // Obtiene el tamaño del archivo en bytes
    rewind(archivoDat); // Regresa el puntero al inicio
	int i, j;
	byte byteLeido;
	NodoArbol *raiz = arbol;
	NodoArbol *nodoActual = arbol;
	//Obtenemos el número de caracteres que vamos a imprimir
	int frecuencias = sumaFrecuencia(arbol);
	//printf("%d\n", frecuencias);
	//Leemos la cadena, hasta haber impreso todos los caracteres
	int contadorCaracteres = 0;
	for (i = 0; i < tamanioArchivo && contadorCaracteres < frecuencias; i++) {
		fread(&byteLeido, sizeof(byte), 1, archivoDat);
		
		for(j = 7; j >= 0 && contadorCaracteres < frecuencias; j--){
			
			if(nodoActual -> izquierda == NULL && nodoActual -> derecha == NULL){//Encontramos un caracter
				//fprintf(archivo ,"%u", nodoActual->caracter);
				fputc(nodoActual -> caracter, archivo);
				nodoActual = raiz;
				contadorCaracteres++;
				//printf("%d\n", contadorCaracteres);
			}
			int bit = CONSULTARBIT(byteLeido,j);
			if(bit == 0){//El bit es cero por lo que recorremos en el arbol izquierdo 
				nodoActual = nodoActual -> izquierda;
			}else{
				nodoActual = nodoActual -> derecha;
			}
			//printf("%d", CONSULTARBIT(byteLeido, j));
		}
		
	}
	fclose(archivoDat);
	fclose(archivo);
}