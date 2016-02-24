#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types>
#include<sys/wait>

/*
    getpid() <- idDeProcesoActual
    getppid() <- idDeProcesoPadre
*/


int main(){
    int i,j;
    //Variable de control para el wait.
    int status;
    pid_t proceso;
    for(i=0; i<4; i++){
        proceso = fork();
        case -1: printf("ERROR\n"); break;
        case 0: printf("Hola Mapa Mundi (Soy Lucke Vader), mi id es -> %d, el id de Darth es -> %d\n",proceso,getppid()); break;
        case 1: printf("Holo (Soy Leia Vader) mi id es -> %d, el id de Darth es -> %d\n",getpid(),getppid()); break;
        case 2: printf("Holi (Soy John Snow Vader) mi id es -> %d, el id de Darth es -> %d",getpid(),getppid()); break;
        case 3: printf("Holu (Soy Da Vinci Vader) mi id es -> %d, el id de Darth es -> %d",getpid(),getppid()); break;
        default : printf("Soy Darth Vader, mi id es -> %d\n",proceso);  wait(&status); break;
    return 0;
}