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
	strcat(aux, ".tab");
	FILE *archivo = fopen( nombreArchivo, "rb"); //Abrimos el archivo en modo binario
	FILE *archivoTab = fopen( aux, "w" );

	if (archivo == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }
	
	// Mueve el puntero del archivo al final para obtener el tamaño
    fseek(archivo, 0, SEEK_END);
    tamanioArchivo = ftell(archivo); // Obtiene el tamaño del archivo en bytes
    rewind(archivo); // Regresa el puntero al inicio

	//En nuestra estructura elemento, ya tenemos el unsigned char como atributo, entonces
    A = (NodoLista*)malloc(256 * sizeof(NodoLista));
	//Arreglo de elementos, en estos vamos a guardar los bytes que ya conocemos y su frecuencia
    if (A == NULL) {
        printf("Error al asignar memoria para el arreglo de elementos");
        fclose(archivo);
        exit(1);
    }
	
	n = 0; //Guardamos cuantos bytes llevamos guardados, ya que puede suceder que se repitan o no
	// Lee cada byte del archivo y guárdalo en el campo `caracter` de cada estructura
    for (i = 0; i < tamanioArchivo; i++) {

        fread(&byteLeido, sizeof(byte), 1, archivo);
		//Hay que verificar si este byte, ya se encuentra dentro del arreglo, si es así, solo aumentamos su frecuencia
		//Se puede optimizar usando un mapa o multiset, sin embargo, que flojera implementarlo en C, entonces hacemos 
		//una búsqueda lineal, viendo si se encuentra el elemento
		if(n == 0){
			NodoLista *t = createElement( 1, byteLeido );
			A[0] = *t;
			n++;
		}else{
			cambios = FALSE;
			for(j = 0; j < n; j++){
				if(A[j].subTree -> caracter == byteLeido){
					A[j].subTree->frecuencia++;
					cambios = TRUE;
					break;
				}
			}
			if(cambios == FALSE){
				NodoLista *new = createElement( 1, byteLeido );
				A[n] = *new;
				n++;
			}
		}
    }
	fclose(archivo);

	NodoLista *B = NULL;

    for( i = 0; i < n; i++ ) {
        NodoLista *h = createElement( A[i].subTree->frecuencia, A[i].subTree->caracter );
		
		fprintf( archivoTab, "%u,%d\n", h->subTree->caracter, h->subTree->frecuencia );

        insertOrderedNode( &B, h );
    } 
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

void create_file_dat(NodoArbol *arbol, char *nombreArchivo, const char *archivoOrigen){
	//Abrimos el archivo
	strcat(nombreArchivo, ".dat");
	FILE *archivoOri = fopen( archivoOrigen, "rb"); //Modo lectura en bits
	FILE *archivoDat = fopen( nombreArchivo, "wb"); //Modo escritura en bits
	//Obtenemos la codificación de cada byte
	//Para eso vamos a hacer uso de un diccionario de elementos, esto debido a que queremos guardar 
	//la cadena  de bytes, correspondiente a cada caracter, aprovechamos que conocemos el número máximo
	//de caracteres que podemos tomar y creamos un arreglo del tamaño de estos, esto con la finalidad,
	//de hacer la búsqueda de cada elemento casi constante, usando solo un poco más de memoria
	elemento *diccionario[256] = {NULL};
	char* cad = malloc(1);
	cad[0] = '\0';
	
	getByteCode(arbol, diccionario, &cad); //Lo que realizamos es buscar en todo el arbol, hasta las hojas y guardar en el diccionario
	//el valor de la cadena
	
	//Una vez que ya tenemos el diccionario, hay que empezar a escribir el archivo dat, para esto vamos a leer el archivo original
	//por byte, dependiendo del byte que tengamos
	
	// Mueve el puntero del archivo al final para obtener el tamaño
    fseek(archivoOri, 0, SEEK_END);
    size_t tamanioArchivo = ftell(archivoOri); // Obtiene el tamaño del archivo en bytes
    rewind(archivoOri); // Regresa el puntero al inicio
	int i, j;
	byte byteLeido;
	
	//Primero creamos el string con la configuración
	char *res = malloc(1 * sizeof(char));
	res[0] = '\0';
	for (i = 0; i < tamanioArchivo; i++) {
        fread(&byteLeido, sizeof(byte), 1, archivoOri);
		res = realloc(res, strlen(res) + strlen(diccionario[byteLeido] -> bytes) + 1);
		strcat(res, diccionario[byteLeido] -> bytes);
	}
	//int tam = (int) strlen(res)/8 + (strlen(res) % 8 != 0);
	int tam = (int) strlen(res)/8 + 1;
	//Ahora imprimimos en el archivo los bytes
	//printf("%s\n\n", res);
	byte cero = 0;
	int aux = 0;
	//Ya que conocemos el número de bytes, recorremos este mismo y vamos imprimiendo cada byte
	//según la cadena, previamente hecha
	while(tam--){
		for(j = 7; j >= 0; j--, aux++){
			if(aux < strlen(res)){
				if(res[aux] == '0') PONE_0(cero, j);
				else PONE_1(cero, j);
			}
		}
		
		fputc(cero, archivoDat);
		
		cero = 0;
	}
	
	free(res);
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