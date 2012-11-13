/*@Autor: Aquiles Lazaro
 *@Descripcion: Simiulacion del problema del productor consumidor, usando semaforos para evitar
 * 	la sobre escritura de las mismas casillas en el arreglo al tiempo de insertar y eliminar.
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXHILOS 2
#define MAX 100 
//Variables globales
int pos=0;
int item=1;
int arreglo[MAX];
//Variables semaforo
sem_t mutex;
sem_t empty;
sem_t full;
//Funcion que inserta en el arreglo
void insertaEnArreglo(item){
	arreglo[pos]=item;
	printf("Produci un %d en la casilla %d\n", item, pos);
}
//Funcion que elimina del arreglo
int eliminaEnArreglo(){
	int obtenido;
	obtenido=arreglo[pos];
	return obtenido;
}
//Funcion del productor
void productor(){
  int i;

  for(i=0;i<MAX;i++){
	sem_wait(&empty);
	sem_wait(&mutex);
	//Region critica del productor
	insertaEnArreglo(item);
	item++;
	pos++;	
	sem_post(&mutex);
	sem_post(&full);
  }
	printf("Arreglo lleno me voy a dormir(PRODUCTOR)\n");
	pthread_exit(0);
}
//Funcion del consumidor
void consumidor(){
  int i, obtenido;

  for(i=0;i<MAX;i++){
 	sem_wait(&full);
 	sem_wait(&mutex);
	//Region critica del consumidor 
	pos--;
	obtenido = eliminaEnArreglo();
	printf("Consumi un %d de la casilla %d\n", obtenido, pos);
	item--;
  	sem_post(&mutex);
  	sem_post(&empty);
  }
	printf("Arreglo vacio me voy a dormir(CONSUMIDOR)\n");
  	pthread_exit(0);
}

int main()  {
  pthread_t hilo[MAXHILOS];

  sem_init(&mutex,0,1);  //inicializa un semaforo mutex con el valor de 1
  sem_init(&full,0,0);  //inicializa un semaforo full con el valor de 0
  sem_init(&empty,0,MAX);  //inicializa un semaforo empty con el valor de MAX
  //Funciones que ejecutan los hilos
  pthread_create(&hilo[0],NULL,(void *)&productor,NULL);
  pthread_create(&hilo[1],NULL,(void *)&consumidor,NULL);
  //Para que el hilo principal espere a los hilos creados
  pthread_join(hilo[0],NULL);
  pthread_join(hilo[1],NULL);

  return 0;
}
