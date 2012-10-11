/* @Autor: Aquiles Lazaro Hernandez
 * @Fecha: 10/10/2012
 * @Descripcion: Se crean dos espacio de memoria compartida, y dos procesos hijos los cuales suman
 *    cada uno la mitad del arreglo y muestran su suma parcial, terminan y el resultado de los dos
 *    lo suma el padre y muestra el resultado.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>

#define N 100

int main(){
//Declaracion de Variables 
long id;
long ide_mem_com, ide_mem_com2;
int status;
int hijo;
int *shm, *shm2;
int i;
int arreglo[N];
//Llenado del arreglo
for (i = 0; i < N; i++){
  arreglo[i] = i + 1;
}
/*Asignacion de un segmento de memoria compartida
 *@return un identificador al segmento de memoria asociado
 */
ide_mem_com=shmget(5678,2,IPC_CREAT|0666);
ide_mem_com2=shmget(5690,2,IPC_CREAT|0666);
/*Operaciones de memoria compartida
 *@return la direccion del secmento de memoria
*/
shm=shmat(ide_mem_com,NULL,0);
shm2=shmat(ide_mem_com2,NULL,0);
//Asignacion de valor a la memoria compartida
*shm=0;
*shm2=0;
//Creacion de proceso
id=fork();

if (id!=0){
   //@Muestra el pid del proceso
   printf("soy el proceso padre %d\n",getpid());
   //@Incremento de la variable compartida
   id=fork();
   if(id == 0){
      //@Muestra el pid del proceso
      printf("soy el proceso hijo 2: %d\n",getpid());
      for (i = N/2; i < N; i++){
          *shm2 = *shm2 + arreglo[i];
      }
      printf("Hijo 2 mi suma es: %d\n", *shm2);
    }
   //@Para esperar al hijo creado
   hijo=wait(&status);
   hijo=wait(&status);
   printf("Soy el padre la suma total es: %d\n",*shm + *shm2);
  }else{
    //@Muestra el pid del proceso
   printf("soy el proceso hijo 1: %d\n",getpid());
   //@Incremento de la variable compartida
   for (i = 0; i < N/2; i++){
      *shm = *shm + arreglo[i];
   }
   printf("Hijo 1 mi suma es: %d\n", *shm);
  }
}