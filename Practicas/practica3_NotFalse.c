#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char archivos[5][50];

void * buscaCosas(void * p){
	printf("Si entre sl hilo\n");
	int * cual = (int *)p;
	//Buscar cosas en archivos[*cual]
	printf("Soy el hilo con %d <- este archivo",*cual);
}

int main(int argc, char ** argv){
	int i;
	pthread_t hilos[5];
	printf("Estoy cachando %d parametros\n",argc);

	if(argc != 6)
		printf("Uy, te mamaste, mala entrada\n");
	else{
		for(i=0; i<5; i++){
			strcat(archivos[i],argv[i+1]);
			printf("Archivo %d: %s.\n",i,archivos[i]);
			if(pthread_create(&hilos[i],NULL,buscaCosas,(void *)i))
				printf("Error creando hilo\n");
			else printf("Cree el hilo de archivo %d. \n",i);
		}
		/*
			Para cada archivo, crear un hilo P
			P crea 5 hilos que cuentan:
				- espacios en blanco aparecen
  				- palabras "hola"
				- caracteres "a"
  				- palabras "programación" 
  				- palabras "la"
  			Cada hilo regresa "El resultado" a su padre, al final
  			el padre de todos suma los resultados y gg.
		*/

	}
	return 0;
}
