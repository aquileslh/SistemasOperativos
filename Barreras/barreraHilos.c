/*@Autor: Aquiles Lazaro
 *@Descripcion: Creacion de barreras con semaforos, los procesos se detienen hasta 
 *	que todos llegan y despues todos abansan.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXHILOS 5 //Numero de hilos
//Uso como semaforo
sem_t sem1; 
pthread_mutex_t m1;
int contador = 0;

void func(int i){
	int tid;
	tid = i;
	printf("Soy el Hilo %d\n", tid);
	sleep(tid*2); //Suspende la ejecución
	pthread_mutex_lock(&m1);
	contador = contador + 1;	
	if(contador != MAXHILOS){ //Pasan la barrera los hilos
		pthread_mutex_unlock(&m1);
		sem_wait(&sem1);
		printf("Soy el hilo %d paso la barrera\n", tid);
	}else{
		printf("Hilos en la barrera\n");
		sleep(tid);
		for (i = 0; i < MAXHILOS; ++i)
			sem_post(&sem1);
		pthread_mutex_unlock(&m1);
	}
}

int main(){
	int i;
	pthread_t hilo[MAXHILOS];//Declaración del numero de hilos
	pthread_mutex_init(&m1, NULL); //inicializa un semaforo mutex con el valor de 1	

	for (i = 0; i < MAXHILOS; ++i)
		pthread_create(&hilo[i],NULL,(void *)&func,(void *)i); //El hilo ejecuta la función producer().
	
	for (i = 0; i < MAXHILOS; ++i)
		pthread_join(hilo[i],NULL); //Para esperar a los hilos creados	
	
	return 0;
}
