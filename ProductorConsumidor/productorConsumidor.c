#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10
#define MAXHILOS 2 
#define MAX 5

int arreglo[MAX];
int posicion = 0;
int item = 1;
int cambio = 0;

sem_t mutex;
sem_t empty;
sem_t full;

void insertarEnElArreglo(int item){
	arreglo[posicion] = item;
	printf("Productor: Elemento %d insertado en la casilla %d\n", item, posicion);
}
int eliminaDelArreglo(){
	int x;
	x = arreglo[posicion];
	return x;
}
void productor(){
	while(item != N){
		if(cambio == 1)
			sleep(2);
		sem_wait(&empty);
		sem_wait(&mutex);
		insertarEnElArreglo(item);
		item++;
		posicion++;
		sem_post(&mutex);
		sem_post(&full);
		if(item == 10)
			cambio = 1;
	}
	pthread_exit(0);
}
void consumidor(){
	int obtenido;
	while(item != N){
		if(cambio == 0)
			sleep(2);
		sem_wait(&full);
		sem_wait(&mutex);
		posicion--;
		obtenido = eliminaDelArreglo();
		printf("Consumidor: Elemento %d sacado de la casilla %d\n", obtenido, posicion);
		sem_post(&mutex);
		sem_post(&empty);
	}
	pthread_exit(0);
}

int main(){ 
	pthread_t hilo[MAXHILOS];

	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, MAX);

	pthread_create(&hilo[0], NULL, (void *)&productor, NULL);
	pthread_create(&hilo[1], NULL, (void *)&consumidor, NULL);

	pthread_join(hilo[0], NULL);
	pthread_join(hilo[1], NULL);
	
	return 0;
}
