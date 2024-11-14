#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "helpers.h"

#include "lista.h"

/*
  
  NodoArbol* buildTree(NodoLista **p)
  
  Construye un árbol de Huffman a partir de una lista de nodos ordenada por frecuencia.

  Descripción:
      Esta función toma una lista enlazada de nodos (NodoLista) ordenada por frecuencia
      y construye un árbol de Huffman combinando los nodos de menor frecuencia
      en subárboles hasta que solo queda uno. Cada nuevo subárbol se crea sumando
      las frecuencias de dos nodos consecutivos y es insertado nuevamente en la lista.
      Al finalizar, el árbol resultante es devuelto.

  Entrada:
      - 'p' es un puntero doble a la cabeza de una lista enlazada de nodos de tipo NodoLista.
        Cada nodo de la lista debe contener un subárbol de tipo NodoArbol.

  Salida:
      - Devuelve un puntero al árbol de Huffman construido (NodoArbol*).

  Precondiciones:
      - La lista enlazada indicada por '*p' debe estar ordenada por frecuencia
        de menor a mayor.
      - '*p' debe ser una lista válida (no NULL).
*/
NodoArbol* buildTree( NodoLista **p ) {

    if( *p == NULL ) 
        return NULL;
    
    while ( (*p) -> next != NULL ) {
        NodoArbol *newTree = malloc( sizeof( NodoArbol ) );
        //newTree -> isLetter = 0;
        newTree -> frecuencia = ( (*p) -> subTree -> frecuencia ) + ( (*p) -> next -> subTree -> frecuencia );

        newTree -> izquierda = (*p) -> subTree;
        newTree -> derecha = (*p) -> next -> subTree;

        NodoLista *listItem = malloc( sizeof( NodoLista ) );
        listItem -> subTree = newTree;
        
        insertOrderedNode( p, listItem );

        NodoLista *aux = *p;

        (*p) = (*p) -> next -> next;
        free( aux -> next );
        free( aux );
    }

    return (*p) -> subTree;
}

/*
  
  void insertOrderedNode(NodoLista **p, NodoLista *h)
  
  Inserta un nodo en una lista enlazada de forma ordenada según la frecuencia.

  Descripción:
      Esta función inserta un nodo en una lista enlazada de nodos (NodoLista) 
      de manera que la lista se mantenga ordenada de menor a mayor en función 
      de la frecuencia del subárbol (subTree->frecuencia) contenido en cada nodo.
      Recorre la lista hasta encontrar la posición adecuada para insertar el nuevo nodo.

  Entrada:
      - 'p' es un puntero doble a la cabeza de una lista enlazada de nodos de tipo NodoLista.
      - 'h' es un puntero al nodo que se insertará en la lista enlazada.

  Salida:
      - La lista enlazada apuntada por '*p' contendrá el nuevo nodo 'h' en la posición
        correspondiente, manteniendo el orden por frecuencia.

  Precondiciones:
      - '*p' debe ser una lista enlazada válida (puede ser NULL si la lista está vacía).
      - 'h' debe apuntar a un nodo NodoLista válido con una frecuencia inicializada en
        subTree->frecuencia.
*/

void insertOrderedNode(NodoLista **p, NodoLista *h) {
    if( *p == NULL ) {
        *p = h;
        return;
    }
    NodoLista *aux = *p;
    NodoLista *ant = NULL;

    // Recorrer la lista hasta encontrar la posición correcta para h
    while (aux != NULL && (aux->subTree->frecuencia) <= (h->subTree->frecuencia)) {
        ant = aux;
        aux = aux->next;
    }

    // insertar al inicio de la lista o antes del primer elemento
    if (ant == NULL) {
        h->next = *p;
        *p = h;
    }
    // insertar entre nodos o al final de la lista
    else {
        ant->next = h;
        h->next = aux;
    }
}

/*
  
  NodoLista* createElement(int frecuencia, unsigned char caracter)
  
  Crea un nuevo nodo de tipo NodoLista que contiene un árbol con un nodo de tipo NodoArbol.

  Descripción:
      Esta función crea un nuevo elemento de la lista enlazada, el cual contiene un nodo de árbol 
      (NodoArbol) con la frecuencia y el carácter proporcionado. El nodo de árbol es inicializado 
      con las propiedades correspondientes y se inserta en un nuevo NodoLista. 
      El NodoLista creado es retornado al final de la ejecución.

  Entrada:
      - 'frecuencia' es un valor entero que indica la frecuencia del carácter en el archivo.
      - 'caracter' es un valor de tipo unsigned char que representa el carácter a asociar con el nodo.

  Salida:
      - La función retorna un puntero a un NodoLista que contiene el NodoArbol con el carácter y la frecuencia dados.

  Precondiciones:
      - 'frecuencia' debe ser un valor entero válido.
      - 'caracter' debe ser un valor de tipo unsigned char representando un carácter.
*/
NodoLista* createElement( int frecuencia, unsigned char caracter ) {
    // Crear el elemento a agregar.
    NodoArbol *na = malloc( sizeof( NodoArbol ) );
    na -> caracter = caracter;
    //na -> isLetter = 1;
    na -> frecuencia = frecuencia;

    na -> derecha = NULL;
    na -> izquierda = NULL;

    NodoLista *nl = malloc( sizeof( NodoLista ) );
    nl -> subTree = na;
    nl -> next = NULL;

    return nl;
}

/*
  
  void addElementToEnd(NodoLista **p, int frecuencia, unsigned char caracter)
  
  Agrega un nuevo nodo al final de la lista enlazada.

  Descripción:
      Esta función agrega un nuevo nodo de tipo NodoLista al final de la lista proporcionada. 
      El nuevo nodo contiene un NodoArbol, que es creado con la frecuencia y el carácter dados. 
      Si la lista está vacía, el nuevo nodo se convierte en el primer elemento de la lista. 
      Si la lista ya tiene elementos, se recorre hasta el último nodo y se agrega el nuevo nodo.

  Entrada:
      - 'p' es un puntero doble a la lista de tipo NodoLista, donde se agregará el nuevo elemento.
      - 'frecuencia' es un valor entero que indica la frecuencia del carácter en el archivo.
      - 'caracter' es un valor de tipo unsigned char que representa el carácter a asociar con el nodo.

  Salida:
      - No tiene valor de retorno. Modifica la lista original agregando un nuevo nodo al final.

  Precondiciones:
      - 'p' debe ser un puntero válido a la lista de nodos.
      - 'frecuencia' debe ser un valor entero válido.
      - 'caracter' debe ser un valor de tipo unsigned char representando un carácter.
*/
void addElementToEnd( NodoLista **p, int frecuencia, unsigned char caracter ) {
    NodoLista *nl = createElement( frecuencia, caracter );
    // Comprobamos si es el primer elemento.
    if( *p == NULL ) 
        *p = nl;
    else {
        NodoLista *aux = *p;
        
        while( aux -> next != NULL ) 
            aux = aux -> next;
        
        aux -> next = nl;
    }

}

/*
  
  void agregarCaracter(char** cadena, char caracter)
  
  Añade un carácter al final de una cadena de caracteres.

  Descripción:
      Esta función agrega un nuevo carácter al final de la cadena de caracteres proporcionada, 
      redimensionando dinámicamente la memoria de la cadena para acomodar el nuevo carácter y el terminador nulo ('\0'). 
      Si la reasignación de memoria falla, se muestra un mensaje de error y el programa termina.

  Entrada:
      - 'cadena' es un puntero a la cadena de caracteres (tipo char*), a la que se le agregará un nuevo carácter.
      - 'caracter' es el valor de tipo char que se añadirá al final de la cadena.

  Salida:
      - No tiene valor de retorno. Modifica la cadena original al agregarle el nuevo carácter.

  Precondiciones:
      - 'cadena' debe ser un puntero válido que apunte a una cadena de caracteres.
      - 'caracter' debe ser un valor válido de tipo char.
*/
void agregarCaracter(char** cadena, char caracter) {
    size_t longitud = strlen(*cadena);

    // Reasignar memoria para la cadena con espacio adicional
    *cadena = realloc(*cadena, longitud + 2);  // +2 para el nuevo carácter y '\0'
    if (*cadena == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(1);
    }

    // Añadir el nuevo carácter y el terminador de cadena
    (*cadena)[longitud] = caracter;
    (*cadena)[longitud + 1] = '\0';
}

/*
  
  void getByteCode(NodoArbol *h, elemento *dic[256], char** cad)
  
  Genera el código binario asociado a cada carácter en el árbol de Huffman.

  Descripción:
      Esta función recorre de manera recursiva el árbol de Huffman, generando el código binario para cada carácter.
      Cuando llega a una hoja del árbol, guarda el carácter y su secuencia de bits en un arreglo de diccionarios.
      El código binario se construye añadiendo '0' al recorrer hacia la izquierda y '1' al recorrer hacia la derecha.
      
  Entrada:
      - 'h' es un puntero a la raíz del nodo actual del árbol de Huffman.
      - 'dic' es un arreglo de 256 elementos de tipo `elemento*` donde se almacenarán los códigos binarios de cada carácter.
      - 'cad' es un puntero a la cadena de caracteres que acumula la secuencia binaria (de longitud variable) que representa el código.

  Salida:
      - No tiene valor de retorno. Modifica el arreglo `dic` con los códigos binarios de los caracteres.
  
  Precondiciones:
      - 'h' debe ser un puntero válido a un nodo del árbol de Huffman.
      - 'dic' debe ser un arreglo válido de 256 punteros a `elemento`.
      - 'cad' debe ser un puntero a una cadena de caracteres válida, inicialmente vacía.
*/
void getByteCode( NodoArbol *h, elemento *dic[256], char** cad){
	if (h == NULL) {
        return;
    }
	// Caso Base
    if( h -> izquierda == NULL && h -> derecha == NULL ){ //Significa que es una hoja
		elemento *e = malloc(sizeof(elemento));
		e->caracter = h->caracter;
		e->bytes = strdup(*cad);
		dic[e->caracter] = e;
		//printf("%c - %s\n", e->caracter, e->bytes);
        return;
	}
	//Hacemos recursión a la izquierda y a la derecha
	if(h->izquierda != NULL){
		agregarCaracter(cad, '0');
		//printf("%s\n", *cad);
		getByteCode(h->izquierda, dic, cad);
		(*cad)[strlen(*cad) - 1] = '\0';
	}
		
	if(h->derecha != NULL){
		agregarCaracter(cad, '1');
		//printf("%s\n", *cad);
		getByteCode(h->derecha, dic, cad);
		(*cad)[strlen(*cad) - 1] = '\0';
	}
}

/*
  
  int sumaFrecuencia(NodoArbol *h)
  
  Calcula la suma de las frecuencias de todos los caracteres en el árbol de Huffman.

  Descripción:
      Esta función recorre de manera recursiva el árbol de Huffman, sumando las frecuencias de los nodos hoja (caracteres).
      Si el nodo actual es una hoja (sin hijos), devuelve su frecuencia. Si no, realiza la suma recursiva de las frecuencias de sus subárboles izquierdo y derecho.

  Entrada:
      - 'h' es un puntero a la raíz del nodo actual del árbol de Huffman.
  
  Salida:
      - Devuelve un valor entero que es la suma de las frecuencias de todos los caracteres en el árbol.
  
  Precondiciones:
      - 'h' debe ser un puntero válido a un nodo del árbol de Huffman.
*/
int sumaFrecuencia( NodoArbol *h){
	if(h == NULL) return 0;
	
	if(h -> izquierda == NULL && h -> derecha == NULL) return h -> frecuencia;
	
	return sumaFrecuencia(h->izquierda) + sumaFrecuencia(h->derecha);
}


/*
//no funciono como se esperaba pero con correcciones tal vez pueda funcionar
int getByteCode( NodoArbol *h, unsigned char letra, Pila *stack ) {

    // Caso Base
    if( h -> izquierda == NULL && h -> derecha == NULL )
        return 0;
    
    if( h -> izquierda -> caracter == letra ) {
        push( stack, '0');
        return 1;
    }
    if( h -> derecha -> caracter == letra ) {
        push( stack, '1' );
        return 1;
    }

    // Recursiòn.
    push(stack, '0');
    int ri = getByteCode( h -> izquierda, letra, stack);

    if( ri != 1 )
        pop( stack );
        
    push( stack, '1');
    int rd = getByteCode( h -> derecha, letra, stack);
    
    if( rd != 1 )
        pop( stack );
        
    if( rd == 1 || ri == 1 )
        return 1;
        
    else 
        return 0;
}
int isByteInTheList( NodoLista **p, unsigned char byteToRead ) {
    NodoLista *aux = *p;
        
    while( aux != NULL ) {
        if( aux -> subTree -> caracter == byteToRead ) {
            aux -> subTree -> frecuencia += 1;
            return 1;
        }
        aux = aux -> next;
    }

    return 0;
}*/
