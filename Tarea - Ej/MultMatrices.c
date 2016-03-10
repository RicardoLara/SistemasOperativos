#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int llenarMatrizA(int FilA, int ColA){
	srand (time(NULL)*3);
	int col, fil;
	for(col = 0; col < FilA; ++col){
		for (fil = 0; fil < ColA; ++fil){
			matrizA[col][fil] = rand()%(9+1);
		}
	}
	return 0;
}

int llenarMatrizB(int FilB, int ColB){
	srand (time(NULL)*5);
	int col, fil;
	for(col = 0; col < FilB; ++col){
		for (fil = 0; fil < ColB; ++fil){
			matrizB[col][fil] = rand()%(9+1);
		}
	}
	return 0;
}

int imprimirMatrizA(int FilA, int ColA){
	int i, j;
	printf("\nMatriz A\n");
	for (i = 0; i < FilA; i++){
		for (j = 0; j < ColA; j++)
		{
			printf("%d ", matrizA[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int imprimirMatrizB(int FilB, int ColB){
	int i, j;
	printf("Matriz B\n");
	for (i = 0; i < FilB; i++){
		for (j = 0; j < ColB; j++)
		{
			printf("%d ", matrizB[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int imprimirMatrizC(int FilA, int ColB){
	int i, j;
	printf("Matriz resultado\n");
	for (i = 0; i < FilA; i++){
		for (j = 0; j <ColB; j++)
		{
			printf("%d ", matrizC[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void *multiplicar(void *param){
	printf("Entre a multiplicar\n");
	parametro *var= (parametro *)param;
	int i, j, k;
	for(i = ((var->FilA/var->numHijos) * var->idHijo); i < ((var->FilA/var->numHijos) * ((var->idHijo)+1)); i++){
		for (j = 0; j < var->ColB; j++){
			matrizC[i][j] = 0;
				for (k = 0; k < var->ColA; k++){
					matrizC[i][j] += (matrizA[i][k] * matrizB[k][j]);
					//printf("Soy mA %d y soy mB %d\n", matrizA[i][k], matrizB[k][j]);
					//printf("Soy n %d \n", matrizC[i][j]);
				}
			//printf("%d ", matrizC[i][j]);
			//printf("Soy j: %d\n", j);
		}
		//printf("\n");
		//printf("Soy i: %d\n", i);
	}
	pthread_exit(0);
}

int multConHijos(int hijos, int FilA, int ColA, int FilB, int ColB){
	printf("entre a multConHijos\n");
	int x, y, i, j, k, n;
	parametro variable[hijos];
	pthread_t hilos[hijos];
 	for(x = 0; x < hijos; x++){
		variable[x].numHijos = hijos;
		variable[x].FilA = FilA;
   		variable[x].ColA = ColA;
   		variable[x].ColB = ColB;
   		printf("entre a el primer for\n");
 	}
 	for(x = 0; x < hijos; x++){
		variable[x].idHijo = x;
		if(pthread_create(&hilos[x],NULL,multiplicar,(void*)&variable[x])){
			fprintf(stderr, "Error creating thread\n");
			return 2;
		}
 	}
 	for(i=0;i<hijos;i++){
		if(pthread_join(hilos[i], NULL)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
	}
 	return 0;
}

int **matrizA, **matrizB, **matrizC;

typedef struct parametro {
   int idHijo;
   int numHijos;
   int FilA;
   int ColA;
   int ColB;
} parametro;

int main(){
	int i, x, y, j, k, n, hijos, FilA, ColA, FilB, ColB;
	hijos = 4;
	printf("\n¿# de filas de la matrizA?: ");
	scanf("%d",&FilA);
	printf("\n¿# de columnas de la matrizA?: ");
	scanf("%d",&ColA);
	printf("\n¿# de filas de la matrizB?: ");
	scanf("%d",&FilB);
	printf("\n¿# de columnas de la matrizB?: ");
	scanf("%d",&ColB);
	
	if (ColA == FilB){
		matrizA = (int **)malloc (FilA*sizeof(int *));
		for (i=0;i<FilA;i++)
			matrizA[i] = (int *) malloc (ColA*sizeof(int));
		printf("Creado con exito matrizA\n");
		matrizB = (int **)malloc (FilB*sizeof(int *));
		for (i=0;i<FilB;i++)
			matrizB[i] = (int *) malloc (ColB*sizeof(int));
		printf("Creado con exito matrizB\n");
		matrizC = (int **)malloc (FilA*sizeof(int *));
		for (i=0;i<FilA;i++)
			matrizC[i] = (int *) malloc (ColB*sizeof(int));
		printf("Creado con exito matrizC\n");
		llenarMatrizA(FilA, ColA);
		llenarMatrizB(FilB, ColB);
		imprimirMatrizA(FilA, ColA);
		imprimirMatrizB(FilB, ColB);
		multConHijos(hijos,FilA, ColA, FilB, ColB);
		imprimirMatrizC(FilA, ColB);
		return 0;
	}else{
		printf("La columna de la matrizA debe ser igual a la fila de la matrizB\n");
		return 0;
	}
}