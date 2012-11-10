/*@Autor: Aquiles Lazaro
 *@Descripcion: Creacion de barreras con Openmp, los procesos se detienen hasta 
 *	que todos llegan y despues todos abansan.
 */
#include <omp.h>
#include <stdio.h>

int main(){
 omp_set_num_threads(5); //numero de procesos
 #pragma omp parallel
 {   int i, tid;
     
     tid = omp_get_thread_num(); //Obtiene el numero de proceso
     sleep(tid*2);//Suspende la ejecucion del proceso
     printf("Antes de la barrera soy el hilo %d\n", tid); 
     #pragma omp barrier //Creamos la barrera
     printf("Despues de la barrera %d\n", tid);
 }
 return 0;
}
