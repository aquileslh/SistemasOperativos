/* @Autor: Aquiles Lazaro Hernandez
 * @Fecha: 10/10/2012
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>

int main(){
//Declaracion de Variables 
long id;
long ide_mem_com;
int status;
int hijo;
int *shm;
/*Asignacion de un segmento de memoria compartida
 *@return un identificador al segmento de memoria asociado
 */
ide_mem_com=shmget(5678,2,IPC_CREAT|0666);

shm=shmat(ide_mem_com,NULL,0);

*shm=0;

id=fork();

if (id!=0)
  {
   printf("soy el proceso padre %d\n",getpid());
   printf("variable compartida antes %d\n",*shm);
   printf("soy el proceso padre idMem %d\n",ide_mem_com);
   hijo=wait(&status);
   printf("mi hijo que espere %d\n",hijo);
   printf("variable compartida DESPUES %d\n",*shm);

  }
else
  {
   printf("soy el proceso hijo %d\n",getpid());
   printf("soy el proceso hijo idMem %d\n",ide_mem_com);
   system("sleep 1");
   *shm=12345;
  }
}