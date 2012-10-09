/*
 * @autor: Lazaro Hernandez Aquiles.
 * @fecha: 07/oct/2012
 * @descripción: Crea proceso de forma lineal con la llamada al sistema fork(). Y en el 
 * 				 proceso penultimo y ultimo se crean procesos distintos con execl() dentro del siclo for().
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 5 //@descripción: Se define para obtener el número maximo de procesos.

void main(){
	int i; //@descripción: Usada como contador en el numero de procesos.
	int val, val2; //@descripción: Para guardar el valor de la llamada al sistema fork().

	for(i=0; i<MAX; i++){ //@descripción: Creación de procesos de forma lineal.
		val = fork();
		if(val == 0)
			break;
		if(i == MAX-2){ //@descripción: Si es el ultimo proceso.
			val2 = fork(); //@descripción: Se crea un proceso.
			if(val2 == 0) 
					execl("./hola2",NULL,NULL); //@descripción: Si el proceso es el hijo, ejecuta al proceso hola2 y muere
		}
		if(i == MAX-1){ //@descripción: Si es el penultimo proceso.
			val2 = fork(); //@descripción: Se crea un proceso.
			if(val2 == 0)
				execl("./hola1",NULL,NULL); //@descripción: Si el proceso es el hijo, ejecuta al proceso hola1 y muere.
		}
	}
	sleep(20); //@descripción: Suspende la ejecución del programa.
}