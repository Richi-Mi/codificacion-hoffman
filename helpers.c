#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "arbol.h"
#include "helpers.h"
#include "bit.h"


/*
  cargarElementos(const char *nombreArchivo, const char *nombreTab)
  
  Carga la frecuencia de cada byte presente en un archivo y las guarda en una lista de nodos ordenada.

  Descripción:
      La función abre un archivo binario especificado por 'nombreArchivo' y cuenta la frecuencia
      de cada byte (carácter) en el archivo. Luego, escribe esta información en un archivo de texto
      con nombre 'nombreTab' (al que se le añade la extensión ".tab"). Finalmente, crea una lista
      de nodos ordenada de caracteres según su frecuencia y la retorna.
  
  Entrada:
      - 'nombreArchivo': cadena de caracteres que representa el nombre del archivo binario a leer.
      - 'nombreTab': cadena de caracteres base para el nombre del archivo de salida, al cual se le
        agrega la extensión ".tab".
  
  Salida:
      - Retorna un puntero a la cabeza de una lista de nodos ('NodoLista') ordenada por frecuencia de caracteres.

  Precondiciones:
      - 'nombreArchivo' debe ser un archivo binario accesible en modo lectura.
      - 'nombreTab' debe ser una cadena de caracteres válida para nombrar el archivo de salida.
      - La función 'createElement' debe inicializar correctamente los nodos de la lista.
      - La función 'insertOrderedNode' debe manejar la inserción ordenada de nodos en la lista.
*/
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

/*
  obtenerFrecuencias(const char *nomb)
  
  Lee las frecuencias de caracteres desde un archivo de texto y las almacena en una lista de nodos ordenada.

  Descripción:
      La función abre un archivo de texto cuyo nombre se deriva de 'nomb' con la extensión ".tab".
      Lee cada línea en el archivo, que contiene pares de valores (carácter y frecuencia), crea un
      nodo con cada par de valores y lo inserta en una lista ordenada de nodos. Finalmente, retorna
      la lista de nodos ordenada por frecuencia.

  Entrada:
      - 'nomb': cadena de caracteres base para el nombre del archivo de texto, al que se le agrega
        la extensión ".tab".

  Salida:
      - Retorna un puntero a la cabeza de una lista de nodos ('NodoLista') que contiene los caracteres
        y sus frecuencias, ordenados de forma ascendente por frecuencia.

  Precondiciones:
      - 'nomb' debe ser una cadena válida que permita acceder al archivo de texto correspondiente.
      - El archivo ".tab" debe existir y contener líneas con el formato "carácter,frecuencia".
      - Las funciones 'createElement' e 'insertOrderedNode' deben estar implementadas correctamente
        para crear e insertar nodos en la lista ordenada.
*/
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

/*
  create_file_dat(NodoArbol *arbol, char *nombreArchivo, const char *archivoOrigen)
  
  Crea un archivo comprimido en formato ".dat" usando la codificación de Huffman basada en un árbol dado.

  Descripción:
      Esta función toma un árbol de Huffman (arbol) y utiliza un diccionario para obtener la codificación
      de cada byte en el archivo de entrada (archivoOrigen). Lee el archivo original byte por byte,
      convierte cada byte a su código binario de Huffman, y almacena los bits codificados en un buffer.
      Luego, escribe el contenido del buffer en el archivo comprimido de salida (nombreArchivo con extensión ".dat").

  Entrada:
      - 'arbol': puntero al nodo raíz del árbol de Huffman que contiene la codificación de los bytes.
      - 'nombreArchivo': nombre del archivo de salida que se creará, al cual se le agrega la extensión ".dat".
      - 'archivoOrigen': nombre del archivo de entrada que se va a comprimir.

  Salida:
      - Crea un archivo comprimido con la codificación de Huffman en el formato ".dat".

  Precondiciones:
      - 'arbol' debe ser un árbol de Huffman válido.
      - 'nombreArchivo' debe ser una cadena válida para crear un archivo de salida.
      - 'archivoOrigen' debe existir y ser accesible en modo lectura.
      - Las funciones 'getByteCode' y las macros 'PONE_1' y 'PONE_0' deben estar implementadas
        correctamente para asignar los bits en el buffer de salida.
*/

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
	printf("bits en el documento original: %d", bitsTotales);
	printf("bits escritos en .dat: %d", bitPos);
    // Escribir el buffer en el archivo de salida
    fwrite(buffer, sizeof(byte), (bitPos + 7) / 8, archivoDat);

    // Liberar memoria y cerrar archivos
    free(buffer);
    free(cad);
    fclose(archivoOri);
    fclose(archivoDat);
}

/*
  descomprimir_archivo(NodoArbol *arbol, char *nombreArchivo, const char *archivoDescomprimido)

  Descomprime un archivo codificado mediante Huffman y lo guarda en su formato original.

  Descripción:
      Esta función abre un archivo comprimido (.dat) y lo descomprime utilizando el árbol de Huffman proporcionado
      (arbol). Lee cada byte del archivo comprimido bit a bit, recorriendo el árbol de Huffman para reconstruir los
      caracteres originales. Cuando encuentra una hoja en el árbol (representando un carácter), escribe ese carácter 
      en el archivo de salida (archivoDescomprimido). El proceso se repite hasta que se han descomprimido todos los
      caracteres originales.

  Entrada:
      - 'arbol': puntero al nodo raíz del árbol de Huffman utilizado para la compresión.
      - 'nombreArchivo': nombre del archivo comprimido (sin la extensión ".dat").
      - 'archivoDescomprimido': nombre del archivo en el que se guardará la salida descomprimida.

  Salida:
      - Archivo descomprimido que contiene los datos originales antes de la compresión.

  Precondiciones:
      - 'arbol' debe ser un árbol de Huffman válido.
      - 'nombreArchivo' debe ser el nombre de un archivo comprimido existente sin la extensión ".dat".
      - 'archivoDescomprimido' debe ser una cadena válida para crear el archivo de salida.
      - Las funciones 'sumaFrecuencia' y las macros 'CONSULTARBIT' deben estar correctamente implementadas.
      - Los archivos deben abrirse sin errores.
*/
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


/** showTime
 * Imprime los tiempos de ejecución del programa.
 * @author Mendoza Castañeda José Ricardo y Edgardo Adrian Franco.
 * @param utime0
 * @param stime0
 * @param wtime0
 * @param utime1
 * @param stime1
 * @param wtime1
 */
void showTime(double utime0, double stime0, double wtime0, double utime1, double stime1, double wtime1)
{
  // Cálculo del tiempo de ejecución del programa
  printf("\n");
  printf("real (Tiempo total),  %.10f s\n", wtime1 - wtime0);
  printf("user (Tiempo de procesamiento en CPU), %.10f s\n", utime1 - utime0);
  printf("sys (Tiempo en acciónes de E/S),  %.10f s\n", stime1 - stime0);
  printf("CPU/Wall,   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
  printf("\n");

  // Mostrar los tiempos en formato exponecial
  printf("\n");
  printf("real (Tiempo total),  %.10e s\n", wtime1 - wtime0);
  printf("user (Tiempo de procesamiento en CPU), %.10e s\n", utime1 - utime0);
  printf("sys (Tiempo en acciónes de E/S),  %.10e s\n", stime1 - stime0);
  printf("CPU/Wall,   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
  printf("\n");
  //******************************************************************
}
