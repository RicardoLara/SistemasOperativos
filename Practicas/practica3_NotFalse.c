#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char archivos[5][50];

void * buscaCosas(void * p){
	int * cual = (int *)p;
	//Buscar cosas en archivos[*cual]
}

int main(int argc, char ** argv){
	int i;
	pthread_t hilo;
	if(argc != 5)
		printf("Uy, te mamaste, mala entrada\n");
	else{
		for(i=0; i<5; i++){
			strcat(archivos[i],atoi(argv[i+1]));
			printf("Archivo %d: %s\n",i,archivos[i]);
			if(!pthread_create(hilo,NULL,buscaCosas,i)) printf(":D\n");
			else printf("Error creando hilo\n");
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