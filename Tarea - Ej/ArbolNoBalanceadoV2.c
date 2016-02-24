#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t proceso;
	int i,j,status;
	pid_t ramaDer[7];
	int statusDer[7];
	pid_t ramaIzq[13];
	int statusIzq[13];

	printf("Soy la cabeza de la familia PID: %d\n",getpid());
	//Derecha
	if( (ramaDer[0] = fork()) != 0 ){
		if( (ramaDer[1] = fork()) != 0 ){
			if( (ramaDer[3] = fork()) != 0 ){
				wait(&statusDer[3]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			if( (ramaDer[4] = fork()) != 0 ){
				wait(&statusDer[4]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			wait(&statusDer[1]);
			printf("Soy %d, mi papa %d\n",getpid(),getppid());
		}
		if( (ramaDer[2] = fork()) != 0 ){
			if( (ramaDer[5] = fork()) != 0 ){
				wait(&statusDer[5]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			if( (ramaDer[6] = fork()) != 0 ){
				wait(&statusDer[6]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			wait(&statusDer[2]);
			printf("Soy %d, mi papa %d\n",getpid(),getppid());
		}
		wait(&statusDer[0]);
		printf("Soy %d, mi papa %d\n",getpid(),getppid());
	}

	//Izquierda
	if( (ramaIzq[0] = fork()) != 0 ){
		if( (ramaIzq[1] = fork()) != 0 ){
			if( (ramaIzq[4] = fork()) != 0 ){
				wait(&statusIzq[4]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			if( (ramaIzq[5] = fork()) != 0 ){
				wait(&statusIzq[5]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			if( (ramaIzq[6] = fork()) != 0 ){
				wait(&statusIzq[6]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			wait(&statusIzq[1]);
			printf("Soy %d, mi papa %d\n",getpid(),getppid());
		}
		if( (ramaIzq[2] = fork()) != 0 ){
			if( (ramaIzq[7] = fork()) != 0 ){
				wait(&statusIzq[7]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			if( (ramaIzq[8] = fork()) != 0 ){
				wait(&statusIzq[8]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			if( (ramaIzq[9] = fork()) != 0 ){
				wait(&statusIzq[9]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			wait(&statusIzq[2]);
			printf("Soy %d, mi papa %d\n",getpid(),getppid());
		}
		if( (ramaIzq[3] = fork()) != 0 ){
			if( (ramaIzq[10] = fork()) != 0 ){
				wait(&statusIzq[10]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			if( (ramaIzq[11] = fork()) != 0 ){
				wait(&statusIzq[11]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			if( (ramaIzq[12] = fork()) != 0 ){
				wait(&statusIzq[12]);
				printf("Soy %d, mi papa %d\n",getpid(),getppid());
			}
			wait(&statusIzq[3]);
			printf("Soy %d, mi papa %d\n",getpid(),getppid());
		}
		wait(&statusIzq[0]);
		printf("Soy %d, mi papa %d\n",getpid(),getppid());
	}
	return 0;
}