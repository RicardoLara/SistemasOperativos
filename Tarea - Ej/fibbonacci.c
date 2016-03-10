#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define NUM 10

void *fibbo(void *param){
	int *num = (int *)param;
	int c,a = 0, b = 1, sig;
	printf("Dentro hijo:\n");

	for (c=0; c<*num;c++) {
		if (c<=1) sig = c;
		else {
			sig = a + b;
			a = b;
			b = sig;
		}
		printf("[%d] %d\n", *num,sig);
	}
	pthread_exit((void*)sig);
}

int main(int argc, char *argv[]){
	int i;
	int *resul = malloc(100);
	pthread_t hilos[NUM];
	int arrays[NUM];

	for (i=0;i<NUM;i++){
		printf("Numero #%d: ", i);
		scanf("%d",&arrays[i]);
	}

	for(i=0;i<NUM;i++)
		if(pthread_create(&hilos[i],NULL,fibbo,(void*)&arrays[i])){
			fprintf(stderr, "Error creating thread\n");
			return 2;
		}

	for(i=0;i<NUM;i++){
		if(pthread_join(hilos[i], (void*)&resul)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
		printf("\tResultado Hilo #%d[%d]: %d\n", i,arrays[i],(int)resul);
	}
}