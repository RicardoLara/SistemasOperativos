#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types>
#include<sys/wait>

int main(){
    pid_t proceso;
    for(i=0; i<4; i++){
            proceso = fork();
            switch(proceso){
                case -1: printf("ERROR\n"); break;
                case 0: 
                    if(!getpid()%2) 
                proceso = fork(); printf("Mi pit: %d, Hijo de %d\n",getpid(),getppid()); break;
                case 1: proceso = fork(); printf("Mi pit: %d, Hijo de %d\n",getpid(),getppid()); break;
                default: printf("Mi pit: %d\n",getpid()); for(j=0; j<2; j++) proceso = fork(); wait(&status); break;
            }
    }
    return 0;
}