#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int contarCad (char *arch, char *pala){
	int contador = 0;
	FILE *f;
	char palabra[16];
	char caracter;
	
	f = fopen(arch, "r");
    if (f == NULL) {
        printf("No se pudo abrir el archivo %s\n", arch);
        exit(EXIT_FAILURE);
    }
	if(pala == " "){
		while (feof(f) == 0){
			caracter = fgetc(f);
			if(caracter == ' ') contador++;
		}
	}else{
		while (!feof(f)) {
	        fscanf(f, "%s", palabra);
	        if (strcmp(palabra, pala) == 0)
	            contador++;
	    }
	}
	fclose(f);
	return contador;
}

typedef struct conteo_data { //Estructura para pasar parametros a padres e hijos
 int id_hijo; //en los padres es Nulo
 char *busqueda; //en los padres es Nulo
 int id_padre;
 char *archivo;
} conteo; 

void *hijo(void *param){ // Funcion hijo que cuenta una palabra de un archivo
	int hijo, padre;
 	char *arch_actual,*query;
 	conteo *datos = (conteo *) param; //Define estructura "datos" recibida del padre

	int *result = (int *)malloc(sizeof(int)); // Declara variable result y la prepara para ser enviada por pthread_exit()

	hijo = datos->id_hijo;	padre = datos->id_padre; // Obtiene datos del padre a traves de la estructura "Datos"
	arch_actual = datos->archivo; query = datos->busqueda;
	*result = contarCad(arch_actual,query); // llena result aleatoriamente

	printf("Padre [%d]: Hilo #%d: \t Result: %d \t[%s:%s]\n", padre,hijo,*result,arch_actual,query); //Imprime datos
	pthread_exit(result); //Envia cuantas veces aparece "query" en el "arch_actual"
}

void *padre(void *param){ // Funcion padre que genera 5 hijos y les pasa las palabras que deben buscar
	int i; //i cont de ciclos, 
	conteo *datos= (conteo *)param; //Define estructura "datos" recibida del padre
	printf("Soy padre, ID: %d | Mi archivo es: %s\n",datos->id_padre,datos->archivo);

	void *retorno; //Delcara variable para almacenar retorno de los hilos hijo
	int *ret_array = malloc(6*sizeof(ret_array[0])); //Declara arreglo de enteros y la prepara para ser enviada por pthread_exit()
	
	pthread_t hijos[5]; //Declara hilos
	conteo est_conteo[5]; //Una estructura por hilo

	char *busquedas[5]={" ","hola","a","programacion","la"}; //Declara querys

	for(i=0;i<5;i++) { //Llena estructuras con informacion
		est_conteo[i].id_hijo = i;
		est_conteo[i].id_padre = datos->id_padre;
		est_conteo[i].archivo = datos->archivo;
		est_conteo[i].busqueda = busquedas[i];
		if (pthread_create(&hijos[i], NULL, hijo, (void *)&est_conteo[i])) { // Crea hilos
			fprintf(stderr, "Error creating thread\n");
			exit(-1);
		}
	} 

	for(i=0;i<5;i++){
		if(pthread_join(hijos[i], &retorno)) {
			fprintf(stderr, "Error joining thread\n");
			exit(-1);
		}
		ret_array[i] = *((int *)retorno); //Cada que termina un hilo almacena resultado en arreglo ret_array
	}
	ret_array[5]=-1; //Almacena sentinela
	printf("Array completo: %d,%d,%d,%d,%d|%d\n", ret_array[0],ret_array[1],ret_array[2],ret_array[3],ret_array[4],ret_array[5]);
	pthread_exit(ret_array);
}

int main(int argc, char *argv[]){

	if(argc < 6){
		printf("ERROR: Debe ejecutar el programa con argumentos eg ./a.out 1.txt 2.txt 3.txt 4.txt 5.txt\t(Argumentos Minimos: 5)");
		return 1;
	}

	int i,k;
	void *ret_array; //Declara arreglo de retorno
	int *sum_array; //Arreglo intermedio de suma
	int result_array[5] = {0,0,0,0,0}; //Arreglo final de suma

	pthread_t padres[5]; //Delcara hilos
	conteo input[5]; //Una estructura por hilo

	for(i=0;i<5;i++){ //Imprime variables
		input[i].id_padre = i;
		printf("ARGV[%d]: %s\n",i,argv[i+1]);
 		input[i].archivo = argv[i+1];
	} printf("\n"); //Formato
	
	for(i=0;i<5;i++){ //Crea hilos llamando a funcion padre
		if(pthread_create(&padres[i],NULL,padre,(void*)&input[i])){
			fprintf(stderr, "Error creating thread\n");
			return 2;
		}
	}

	for(i=0;i<5;i++){ // Espera a que los hilos terminen
		if(pthread_join(padres[i],&ret_array)) {
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}
		sum_array = ret_array; //Copia arreglo intermedio
		printf("Main %d: ", i); // Formato
		for (k = 0; sum_array[k] != -1; k++) {
			result_array[k] = result_array[k] + sum_array[k]; //Suma de arreglos retornados por hilos padre
	    	printf("%d ", sum_array[k]); // Imprime arreglos retornados por hilos padre
	    }
	    printf("\n"); //Formato
	}
	printf("\nResult Array: %d,%d,%d,%d,%d\n", result_array[0],result_array[1],result_array[2],result_array[3],result_array[4]);
	printf("\nInfomacion:\n [%d] Espacios\n [%d] Hola\n [%d] a\n [%d] programacion\n [%d] la\n",result_array[0],result_array[1],result_array[2],result_array[3],result_array[4]);
	return 0;
}
