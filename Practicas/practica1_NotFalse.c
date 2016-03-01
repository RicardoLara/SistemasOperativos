#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#define ColAFilB 4
#define FilAColB 2

int main(){
	int i, col, fil;
	int *p;
	int hijos = 2;
	int matrizA[FilAColB][ColAFilB], matrizB[ColAFilB][FilAColB], matrizC[FilAColB][FilAColB];
	p = matrizC;
	llenarMatrizA(&matrizA);
	llenarMatrizB(&matrizB);
	vaciarMatrizC(&matrizC);
	imprimirMatrizA(matrizA);
	imprimirMatrizB(matrizB);
	multConHijos(hijos, matrizA, matrizB, &matrizC, p);
	imprimirMatrizC(matrizC);
	return 0;
 }

int llenarMatrizA(int matrizA[][ColAFilB]){
	srand (time(NULL)*3);
	int col, fil;
	for(col = 0; col < FilAColB; ++col){
		for (fil = 0; fil < ColAFilB; ++fil){
			matrizA[col][fil] = rand()%(9+1);
		}
	}
	return 0;
}

int llenarMatrizB(int matrizB[][FilAColB]){
	srand (time(NULL)*5);
	int col, fil;
	for(col = 0; col < ColAFilB; ++col){
		for (fil = 0; fil < FilAColB; ++fil){
			matrizB[col][fil] = rand()%(9+1);
		}
	}
	return 0;
}

int vaciarMatrizC(int matrizC[][FilAColB]){
	int col, fil;
	for(col = 0; col < FilAColB; ++col){
		for (fil = 0; fil < ColAFilB; ++fil){
			matrizC[col][fil] = 0;
		}
	}
	return 0;
}

int imprimirMatrizA(int matrizA[][ColAFilB]){
	int i, j;
	printf("\nMatriz A\n");
	for (i = 0; i < FilAColB; i++){
		for (j = 0; j < ColAFilB; j++)
		{
			printf("%d ", matrizA[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int imprimirMatrizB(int matrizB[][FilAColB]){
	int i, j;
	printf("Matriz B\n");
	for (i = 0; i < ColAFilB; i++){
		for (j = 0; j < FilAColB; j++)
		{
			printf("%d ", matrizB[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int imprimirMatrizC(int matrizC[][FilAColB]){
	int i, j;
	printf("Matriz resultado\n");
	for (i = 0; i < FilAColB; i++){
		for (j = 0; j < FilAColB; j++)
		{
			printf("%d ", matrizC[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int multConHijos(int hijos, int matrizA[][ColAFilB], int matrizB[][FilAColB], int matrizC[FilAColB][FilAColB], int *p){
	int x, y, i, j, k, n;
	pid_t pid;
 	for(x = 0; x < hijos; x++){
		switch(pid = fork()){
			case 0:
				for(i = ((FilAColB/hijos) * x); i < ((FilAColB/hijos) * (x+1)); i++){
					for (j = 0; j < FilAColB; j++){
						for (k = 0; k < ColAFilB; k++){
							((p+i)+j) = (*(p+i)+j) + (matrizA[i][k] * matrizB[k][j]);
							printf("Soy mA %d y soy mB %d\n", matrizA[i][k], matrizB[k][j]);
							printf("Soy k %d y soy p : %d\n", k, (*(p+i)+j));
						}
						printf("Soy j: %d\n", j);
					}
					printf("Soy i: %d\n", i);
				}
				exit(0);
			break;
			case -1:
				printf("Error en la creacion del proceso \n");
				exit(0);
			break;
			default:
				for (y=0; y<hijos; y++)
					wait(&y);
			break;
		}
		printf("Soy x: %d\n", x);
 	}
 	return 0;
}