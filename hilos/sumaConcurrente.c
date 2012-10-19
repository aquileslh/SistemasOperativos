/**
 * @Autor: Aquiles Lazaro
 * @Descripcion: Se crean dos hilos, los cuales realizan una suma del arreglo respetando
 *  			la region critica para no sumar la misma casilla dos veces 
**/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	2
#define MAX 100000
//Variables globales 
int arreglo[MAX];
int total=0;
int indice=0;
//Crea la variable mutex (o candado) que puede tener el valor lock (bloqueado) y unlock (libre)
pthread_mutex_t m1;
pthread_mutex_t m2;
//Funcion que ejecutan los hilos creados
void *PrintHello(void *threadid){
   	int *id_ptr, taskid;
   	int miIndice;
   	int parcial=0;
   	//Para saver el numero del hilo
	id_ptr = (int *) threadid;
	taskid = *id_ptr;
	//Ciclo para sumar todos los elementos del arreglo
	while(indice < MAX){
		/*Para la exclusion mutua el hilo se detiene si otro esta dentro de la region critica*/
		pthread_mutex_lock(&m1);
		miIndice = indice;
		indice++;
		//Libera la region critica para que otro hilo entre
		pthread_mutex_unlock(&m1);
		parcial = parcial + arreglo[miIndice];
	}
	printf("Hilo %d termine el ciclo, mi parcial es: %d\n",taskid, parcial);
	//Region critica para no sobrescribir el total
	pthread_mutex_lock(&m2);
	total = total + parcial;
	pthread_mutex_unlock(&m2);
	//Termina el proceso del hilo
   	pthread_exit(NULL);
}

int main(){

	pthread_t threads[NUM_THREADS];
	int *taskids[NUM_THREADS];
	int rc, t;
	//Se inician las variables candado
	pthread_mutex_init (&m1, NULL);
	pthread_mutex_init (&m2, NULL);
	//Llenado del arrreglo
	for(t=0; t<MAX; t++){
		arreglo[t]=1;
	}
	arreglo[MAX]=3;
	//Creacion de los hilos
	for(t=0;t<NUM_THREADS;t++) {
  		taskids[t] = (int *) malloc(sizeof(int));
  		*taskids[t] = t;
  		rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
	}
	//Para esperar los hilos creados
	for(t=0;t<NUM_THREADS;t++){
 		pthread_join(threads[t],NULL);
	}
	printf("el total es: %d\n", total);
}
