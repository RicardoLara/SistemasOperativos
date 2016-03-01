#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void creaHijo(int nivel, int hijo, int cont){
	int n = cont, i3, i4;
	pid_t pid3;

	for (i3=0; i3<hijo; ++i3){
		pid3 = fork();
		switch(pid3){
			case -1: printf(("Error de bifurcacion \n")); break;
			case 0:
				n++;
				printf("Nivel %d, soy %d y mi padre es %d \n", n, getpid(), getppid());
				if(n < nivel) creaHijo(nivel, hijo, n);
				exit(0);
			break;
			default:
				printf("Soy el proceso padre %d \n", getpid());
				for (i4=0; i4<hijo; i4++) wait(&i4);
			break;
		}
	}
}

int main (){
	pid_t pid;
	int x, n = 0, i, nivel;

	printf("Hola guapo, meteme el nivel\n");
	scanf("%d",&nivel);
	for(x=0; x<2; x++){
		pid = fork();
		switch(pid){
			case -1: printf("Error de bifurcacion \n"); break;
			case 0:
				n++;
				printf("Nivel %d, soy %d y mi padre es %d \n", n, getpid(), getppid());
				if(x%2) creaHijo(nivel, 3, n);
				else creaHijo(nivel, 2, n);
				exit(0);
			break;
			default:
				printf("Soy el proceso padre %d \n", getpid());
				for (i=0; i<2; i++)	wait(&i);
			break;
		}
	}
	return 0;
}