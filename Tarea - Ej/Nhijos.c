#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int i,status;
	pid_t proceso;
	
	for(i=0; i<4; i++){
		proceso = fork();
		switch(proceso){
			case -1: printf("ERROR\n"); break;
			case 0: printf("Hola soy %d, y soy hijo de %d\n",getpid(),getppid()); break;
			default: if(i == 0) printf("Soy el papa %d\n",getpid()); break;
		}
		if(proceso == 0) break;
	}
	wait(&status);
	return 0;
}