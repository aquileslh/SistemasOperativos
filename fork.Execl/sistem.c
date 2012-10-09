/*
 * @autor: Lazaro Hernandez Aquiles.
 * @fecha: 07/oct/2012
 * @descripción: Crea proceso de forma lineal con la llamada al sistema fork(). Y en el 
 * 				 proceso penultimo y ultimo se crean procesos distintos con system() fuera del siclo for().
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 5 //@descripción: Se define para obtener el número maximo de procesos.

void main(){
	int i; //@descripción: Usada como contador en el numero de procesos.
	int val; //@descripción: Para guardar el valor de la llamada al sistema fork().

	for(i=0; i<MAX; i++){ //@descripción: Creación de procesos de forma lineal.
		val = fork();
		if(val == 0)
			break;
	}
	if(i == MAX-2){ //@descripción: Si es el ultimo proceso.
			system("./hola2"); //@descripción: Ejecuta al proceso hola2.
	}
	if(i == MAX-1){ //@descripción: Si es el penultimo proceso.
			system("./hola1"); //@descripción: Ejecuta al proceso hola1.
	}
	sleep(20); //@descripción: Suspende la ejecución del programa.
}