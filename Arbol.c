#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

void caso_cero(int pidPadre, int pidActual, int nHijos, int niveles){
	pid_t proceso;
	int i,status;

	printf("Soy el hijo de %d, mi pid es %d\n",pidPadre,pidActual);
	if(niveles == 0){ printf("*****************************************\n"); return; }
	for(i=0; i<nHijos; i++){
		proceso = fork();
		printf("Cree el proceso %d, lo hice en %d\n",getpid(),getppid());
		caso_cero(getppid(),proceso,nHijos,--niveles);
		wait(&status);
		exit(0);
	}
	
}

int main(){
	pid_t proceso;
	int i;
	int status1;

	printf("Datos de inicio:\nPID PADRE: %d\nPID ACTUAL: %d\n",getppid(),getpid());
	for(i=0; i<2; i++){
		proceso = fork();
		printf("Cree el proceso %d, lo hice en %d\n",getpid(),getppid());
		if(i%2) caso_cero(getppid(),getpid(),1,0);
		else caso_cero(getppid(),getpid(),2,2);
		wait(&status1);
	}
	return 0;
}

/*
int main(){
	pid_t proceso,proceso1,proceso2;
	int i,j,k;
	int status1,status2,status3;

	for(i=0; i<1; i++){
		proceso = fork();
		switch(proceso){
			case -1: printf("ERROR\n"); break;
			case 0: 
				printf("Soy el hijo de %d, mi pid es: %d\n",getppid(),getpid());
				for (j=0; j<2; j++){
					proceso1 = fork();
					switch(proceso1){
						case -1: printf("ERROR\n"); break;
						case 0: 
							printf("Soy el hijo de %d, mi pid es: %d\n",getppid(),getpid());
							for(k=0; k<2; k++){
								proceso2 = fork();
								switch(proceso2){
									case -1: printf("ERROR\n"); break;
									case 0:  
										printf("Soy el hijo de %d, mi pid es: %d\n",getppid(),getpid());
									break;
									//default: printf("SOY EL ULTIMO QUE HACE 2 (SEGUN): %d\n",getpid()); break;
								}
								wait(&status3);
							}
							exit(0);							
						break;
						//default: printf("GENERO 2 (SEGUN): %d\n",getpid()); break;
					}
					wait(&status2);
				}
				exit(0);	
			break;
			default: printf("Soy NODO INICIAL: %d\n",getpid()); break;
		}
		wait(&status1);
		exit(0);
	}
	return 0;
}
*/