#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> 
#include <arpa/inet.h>  
#include <unistd.h> 

char carpeta[10];
char comando[255];
int extension;

void mover(){
    printf("SI ENTRO A MOVER\n");
    char aux[255];
    strcpy(aux,""); strcpy(comando,"");
    switch(extension){
        case 0: sprintf(aux, "copia.%s", "jog"); break;
        case 1: sprintf(aux, "copia.%s", "png"); break;
        case 2: sprintf(aux, "copia.%s", "pdf"); break;
        case 3: sprintf(aux, "copia.%s", "mp3"); break;
        case 4: sprintf(aux, "copia.%s", "cbr"); break;
    }
    sprintf(comando, "cp %s", aux);
    sprintf(comando, "%s %s",comando, carpeta); system(comando);
    strcpy(comando,"");
    sprintf(comando,"rm %s",aux); system(comando);
}

int main(int argc, char *argv[]){ 
	unsigned char buffer[256],buffer2[256];
    char c = '\n', *p_buf;
    int k, len;
    int sock_desc = socket(AF_INET, SOCK_STREAM, 0); 
    
    if (sock_desc == -1){
        printf("cannot create socket!\n");
        return 0;
    }

    struct sockaddr_in client;  
    memset(&client, 0, sizeof(client));  
    client.sin_family = AF_INET;  
    client.sin_addr.s_addr = inet_addr(argv[1]);  
    client.sin_port = htons(atoi(argv[2]));  
    if (connect(sock_desc, (struct sockaddr*)&client, sizeof(client)) != 0){
        printf("cannot connect to server!\n");
        close(sock_desc);
    }  

    while(1){
        bzero(buffer,256);
        bzero(buffer2,256);
        int n = 0;
    	FILE *archivo;
        printf("Cliente -> Conectado :D\n");
    	int uno = recv(sock_desc,buffer,1,0);
        if(uno == 1){
            printf("Estoy recibiendo el archivo: %s\n",buffer);
            extension = atoi(buffer);
            printf("ID de extension: %d\n",extension);
            switch(extension){
                case 0: archivo = fopen("copia.jpg", "wb"); break;
                case 1: archivo = fopen("copia.png", "wb"); break;
                case 2: archivo = fopen("copia.pdf", "wb"); break;
                case 3: archivo = fopen("copia.mp3", "wb"); break;
                case 4: archivo = fopen("copia.cbr", "wb"); break;
            }
            sprintf(carpeta,"cliente%s",buffer);
            sprintf(comando,"mkdir -p %s",carpeta); 
            system(comando);
            printf("Fue creada la carpeta %s\n",carpeta);
        }
        else{ printf("Error al recibir extension\n"); return 0; }
        if (archivo == NULL){
            printf ( "Error en la apertura. Es posible que el fichero no exista \n ");
            fclose (archivo);
            return 0;
        }
        while(strncmp(buffer2, "Ya quedo", 7) != 0){
            n=n+1; bzero(buffer,256);
            int k = recv(sock_desc,buffer,256,0);
            printf("%s --- AQUI TERMINA EL %d\n", buffer, n);
            if (strncmp(buffer, "Ya quedo", 7) != 0)
                if (fwrite(buffer, 1, k, archivo) == -1)
                    return 0;
            else strncpy(buffer2, buffer, 8);
        }
        printf("Quiero mover\n"); mover();
        if(fclose (archivo) != 0){
            printf("El archivo no se pudo cerrar correctamente\n");
            return 0;
        }
    }  
    close(sock_desc);  
    printf("client disconnected\n");
    return 0;  
}
