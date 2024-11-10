#include <stdio.h>
/**
 * @author Rodriguez Mendoza Cristofer. 
 * Esta macro genera un n�mero en el cual solo el bit en la posici�n bpos
 * est� en 1. Por ejemplo, si bpos = 3, el resultado ser�a 00001000, que en
 * decimal es 8. Esto se logra con el desplazamiento de bits a la izquierda: 1 << bpos.
*/
#define PESOBIT( bpos ) 1<<bpos

/**
 * @author Rodriguez Mendoza Cristofer. 
 * Esta macro verifica el valor del bit en la posici�n bpos de la variable var. Usa una
 * conversi�n a puntero unsigned* para trabajar a nivel de bits sin problemas de tipos.
 * Luego, hace una operaci�n AND con el resultado de PESOBIT(bpos) para ver si el bit en
 * esa posici�n es 1 o 0, y regresa 1 o 0 seg�n corresponda.
*/
#define CONSULTARBIT( var, bpos ) (*(unsigned*)&var & PESOBIT(bpos))?1:0

/**
 * @author Rodriguez Mendoza Cristofer. 
 * Esta macro pone el bit en la posici�n bpos de var en 1. Se realiza una operaci�n OR
 * entre la variable y el valor devuelto por PESOBIT(bpos). La operaci�n OR garantiza
 * que solo el bit en la posici�n bpos se establezca en 1 sin modificar otros bits.
*/
#define PONE_1( var, bpos ) *(unsigned*)&var |= PESOBIT(bpos)

/**
 * @author Rodriguez Mendoza Cristofer. 
 * Similar a PONE_1, pero aqu� se pone el bit en la posici�n bpos en 0. Se usa una m�scara
 * negada (~) para asegurarse de que solo el bit espec�fico se apague, mientras los dem�s
 * permanecen sin cambios.
*/
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))

/**
 * @author Rodriguez Mendoza Cristofer. 
 * Esta macro niega el bit en la posici�n bpos de var. Usa la operaci�n XOR, que cambia el
 * bit de 1 a 0 o de 0 a 1.
*/
#define CAMBIA( var, bpos ) *(unsigned*)&var ^= PESOBIT(bpos)
/*
int main(void)
{
	int i,n_bits, a; //Auxiliares
	unsigned char numero=255; //Variable de tipo char (byte)
	unsigned char arreglo[125];
	
	//bit 0 del arreglo 999
	a=300;
	PONE_1(arreglo[a/8],a%8);

	//Determinar la longitud de los bits a operar
	printf("N�mero de bits\n");
	n_bits=sizeof(numero) * 8;
	printf("%2d bits",n_bits);	
	printf("\n");
	
	//Revisar el valor de cada bit
	printf("Valor de los bits\n");
	for (i=n_bits-1; i>=0; i--)
	printf("%d",CONSULTARBIT(numero,i));
	printf("\t%u\n",numero);

	//Modificar el valor de algunos bits
	printf("Modificar el valor de los bits\n");
	PONE_1(numero,7); 		//1 en Bit 0  
	//PONE_1(numero,3); 		//1 en Bit 3
	PONE_1(numero,5); 		//1 en Bit 5
	//PONE_0(numero,5); 		//0 en Bit 5
	
	CAMBIA(numero,0);		//Negar Bit 0
	CAMBIA(numero,3);		//Negar Bit 3
	//CAMBIA(numero,7);		//Negar Bit 7
	//CAMBIA(numero,0);		//Negar Bit 0

	//PONE_1(numero,31); 		//1 en Bit 5
	//Revisar el valor de cada bit
	printf("Valor de los bits\n");
	for (i=n_bits-1; i>=0; i--)
	printf("%d",CONSULTARBIT(numero,i));
	printf("\t%u\n",numero);
}
*/