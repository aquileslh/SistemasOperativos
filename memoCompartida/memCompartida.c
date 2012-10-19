/* @Autor: Aquiles Lazaro Hernandez
 * @Fecha: 10/10/2012
 * @Descripcion: Se crea un espacio de memoria compartida, y dos procesos los cuales suman
 *    en el mismo espacio de memoria compartida, en algun momento se sobreescribe este espacio de memoria 
 *    por los dos procesos y obtenemos un resultado erroneo.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>

#define N 1000000

int main(){
//Declaracion de Variables 
long id;
long ide_mem_com;
int status;
int hijo;
int *shm;
int i;
/*Asignacion de un segmento de memoria compartida
 *@return un identificador al segmento de memoria asociado
 */
ide_mem_com=shmget(5678,2,IPC_CREAT|0666);
/*Operaciones de memoria compartida
 *@return la direccion del secmento de memoria
*/
shm=shmat(ide_mem_com,NULL,0);
//Asignacion de valor a la memoria compartida
*shm=0;
//Creacion de proceso
id=fork();
if (id!=0){
   //@Muestra el pid del proceso
   printf("soy el proceso padre %d\n",getpid());
   //@Incremento de la variable compartida
   for (i = 0; i < N; i++){
      *shm = *shm + 1;
   }
   //@Para esperar al hijo creado
   hijo=wait(&status);
   printf("variable compartida DESPUES %d\n",*shm);
  }else{
    //@Muestra el pid del proceso
   printf("soy el proceso hijo %d\n",getpid());
   //@Incremento de la variable compartida
   for (i = 0; i < N; i++){
      *shm = *shm + 1;
   }
  }
}