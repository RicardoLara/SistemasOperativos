#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void creaHijo(int nivel, int hijo, int cont){
	int n = cont, i3, i4,k;
	pid_t pid3;

	for (i3=0; i3<hijo; ++i3){
		pid3 = fork();
		switch(pid3){
			case -1: printf(("Error de bifurcacion \n")); break;
			case 0:
				n++;
				if(n != nivel) {for(k=0;k<n;k++) printf("\t"); printf("+---------------------------------------+\n");}
				else if(i3==0) {for(k=0;k<n;k++) printf("\t"); printf("+---------------------------------------+\n");}
				for(k=0;k<n;k++) printf("\t"); printf("| Nivel: %d | Mi PID: %d | Padre: %d |\n",n+1,getpid(),getppid());
				for(k=0;k<n;k++) printf("\t"); printf("+---------------------------------------+\n");
				if(n < nivel) creaHijo(nivel, hijo, n);
				exit(0);
			break;
			default:
				if(i3==0){
					if(n==1){
					for(k=0;k<n;k++) printf("\t"); printf("+---------------------------------------+\n");
					for(k=0;k<n;k++) printf("\t"); printf("| Nivel: %d | Mi PID: %d | Padre: %d |\n",n+1,getpid(),getppid());
					}
					if(n==1) {for(k=0;k<n;k++) printf("\t"); printf("+---------------------------------------+\n");}
					for(k=0;k<n;k++) printf("\t"); printf("| Creando %d hijos...                    |\n",hijo);
					for(k=0;k<n;k++) printf("\t"); printf("+---------------------------------------+\n");
				}
				for (i4=0; i4<hijo; i4++) wait(&i4);
			break;
		}
	}
}

int main (){
	pid_t pid;
	int x, n = 0, i, nivel;

	printf("Inserte Nivel: ");
	scanf("%d",&nivel);
	for(x=0; x<2; x++){
		pid = fork();
		switch(pid){
			case -1: printf("Error de bifurcacion \n"); break;
			case 0:
				n++;
				printf("+---------------------------------------+\n| Nivel: %d | Mi PID: %d | Padre: %d |\n| Rama: ",n,getpid(),getppid());
				if(x) printf("Derecha  ");
				else  printf("Izquierda");
				printf("                       |\n| Creando %d hijos...                    |\n+---------------------------------------+\n",x+2);
				if(x%2) creaHijo(nivel, 3, n);
				else creaHijo(nivel, 2, n);
				exit(0);
			break;
			default:
				if (x==0) printf("\n#=======================================#\n\tDatos Inicio:\nPID Padre: %d (terminal)\nPID Actual: %d\n#=======================================#\n\n", getppid(),getpid());
				for (i=0; i<2; i++)	wait(&i);
			break;
		}
	}
	return 0;
}