#include<unistd.h>
#include<stdio.h>
P
/*
    Fork: Crea procesos
    WIFEXITED: Comprueba que el valor recibido sea ! 0
    WEXITSTATUS: Evalua los 8 bits menos significativos del 
    codigo de retorno del hijo para identificar su edo de 
    finalizacion
    P (wait y sale de tabla de procesos), H acaba con exit.
*/

int main(){
    int i;
    pid__t proceso;
    proceso = fork();
    switch(proceso){
        case -1: printf("ERROR\n"); break;
        case 0: printf("Hola Mapa Mundi (Soy Lucke Vader), mi id es -> %d\n",proceso); break;
        default : 
            for(i=0; i<50; i++)
            printf("Soy Darth Vader, mi id es -> %d\n",proceso); 
        break;
    }
    return 0;
}