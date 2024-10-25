#include <stdio.h>
#include <stdlib.h>
#include "ArbolHuffman.h"
#include "Heap.h"
/*
 Monticulo :)

*/
//Para acceder al elemento : A[]->e.frecuencia
int tam;

void Inicializar(heap *A, int n){
	tam = 0;
	
	*A = malloc(n * sizeof(arbolHuffman));
	if (*A == NULL) {
        printf("\nError al intentar reservar memoria para %d elementos\n", n);      
        exit(1);
    }
}

void Intercambio(heap A, int i){
	arbolHuffman temp;
	while(i !=0 && A[(i - 1) / 2]->e.frecuencia > A[i]->e.frecuencia){ //Si el padre es mayor que el hijo
	//entonces intercambiamos al numero mayor a la posición del hijo, esto se repite hasta que
	//el padre no sea mayor al hijo o el valor que agregamos se encuentre en la raiz
	temp = A[i];
	A[i] = A[(i-1) / 2]; //cambiamos a la posicion del hijo al padre
	A[(i-1)/2] = temp; //subimos el hijo
	i = (i-1)/2; //actualizamos el valor de i	
	}
}

void Insertar(heap A, arbolHuffman valor){
	int i = tam;
	A[tam++] = valor; // colocamos dentro del heap en la siguiente posición del arreglo
	Intercambio(A, i);
}

arbolHuffman Extraer(heap A){ // Se saca el elemento de la raizel arbol
	if(tam <= 0){
		printf("\nError: Extraer(heap) subdesbordamiento de heap");
		exit(1);
	}
	if(tam == 1){
		tam--;
		return A[0];
	}
	printf("Estoy en extraer\n");
	arbolHuffman elementoRaiz = A[0]; //Obtenemos el número que se encuentra en la raiz (este deberia ser el menor dentro del arbol)
	A[0] = A[tam-1]; //sustituimos la raiz con la ultima hoja que agregamos
	tam--;
	
	actualizarNodos(A, 0); //se encarga de reorganizar los elementos que se encuentren dentro del heap
	
	return elementoRaiz;
}

void actualizarNodos(heap A, int indice){
	int auxindice = indice; //guardamos en indice en el que nos encontramos en este momento
	int izquierda = 2 * indice + 1; // guardamos la posicion en la que se encuentra nuestro hijo izquierdo
	int derecha = 2 * indice + 2; // guardamos la posicion en la que se encuentra nuestro hijo derecho
	arbolHuffman temp;
	
	if(izquierda < tam && A[izquierda]->e.frecuencia < A[auxindice]->e.frecuencia){ //verificamos que tengamos un hijo izquierdo y que este hijo sea menor al que tenemos en el indice
		auxindice = izquierda;
	}
	//Ahora verificamos con nuestro hijo derecho, asi mismo si este hijo es más pequeño que el actual (auxiliar)
	if(derecha < tam && A[derecha]->e.frecuencia < A[auxindice]->e.frecuencia){ //verificamos que tengamos un hijo derecho y que este hijo sea menor al que tenemos en el indice
		auxindice = derecha;
	}
	//Si después de haber hecho las anteriores comparaciones el indice sigue siendo el número más pequeño
	//No se cumple la condición, debido a que ya se encuentra ordenado el heap
	if(auxindice != indice){
		//subimos el valor menor que se encuentre en el hijo al nodo padre, dejando hasta arriba al menor
		temp = A[indice];
		A[indice] = A[auxindice];
		A[auxindice] = temp;
		
		actualizarNodos(A, auxindice); //llamamos recursivamente a la función
		//Esto se va a repetir hasta que se encuentren todos los nodos acomodados
	}
}

int size(heap A){
	return tam;
}