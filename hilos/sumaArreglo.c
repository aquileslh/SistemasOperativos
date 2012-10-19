/**
 * @Autor: Aquiles Lazaro
 * @Descripcion: Creacion de dos hilos, suman la mitad del arreglo y el proceso padre muestra el total
 * @Nota: Compilacion en terminal: gcc -o hilo hilo.c -lpthread
**/
#include <stdio.h>
#include <stdlib.h>
#define TAM 100
#define NUM_THREADS	2
//Variables globales
int x[100];
int res1;
int res2;
int total=0;
//Funcion que ejecutaran los hilos
void *PrintHello(void *threadid){
   int *id_ptr, taskid;
   int parcial=0;
   int i;
   //Para saver el numero de hilo
   id_ptr = (int *) threadid;
   taskid = *id_ptr;
   //El hilo 1 suma la mitad del arreglo
   if(taskid==0){ 
      for(i=0;i<TAM/2;i++)  
        parcial=parcial+x[i]; 
      total=total+parcial;  
   }
   //El hilo 2 suma la otra mitad del arreglo
   if(taskid==1){ 
      for(i=TAM/2;i<TAM;i++)  
        parcial=parcial+x[i];
      total=total+parcial;
   }
   printf("soy el hilo %d mi parcial es %d:\n", taskid,parcial);  
   //Termina el proceso del hilo
   pthread_exit(NULL);
}

int main(){
  pthread_t threads[NUM_THREADS];
  int *taskids[NUM_THREADS];
  int rc, t;
  int i;
  //Llenado del arreglo
  for(i=0;i<TAM;i++)
     x[i]=i+1;
   //Creacion de los hilos
  for(t=0;t<NUM_THREADS;t++) {
    taskids[t] = (int *) malloc(sizeof(int));
    *taskids[t] = t;
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
  }
  //Para que el proceso padre espere a los hilos creados
  for(t=0;t<NUM_THREADS;t++) {
    pthread_join(threads[t],NULL);
  }

  printf("el resultado final es %d  \n",total);
  return 0;
}
