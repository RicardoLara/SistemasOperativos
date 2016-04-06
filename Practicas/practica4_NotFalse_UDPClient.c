#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int LONGITUD_MAX = 255;

int recibir(int socket, char *buffer, struct sockaddr_in cli_addr){
    FILE *archivo;
    int tam = sizeof(cli_addr), n = 0;
    unsigned char buffer2[LONGITUD_MAX +1];
    bzero(buffer,LONGITUD_MAX +1);
    bzero(buffer2,LONGITUD_MAX +1);
    archivo = fopen("copia.pdf", "wb");
    if (archivo == NULL){
        printf ( "Error en la apertura. Es posible que el fichero no exista \n ");
        fclose (archivo);
        return 0;
    }
    while(strncmp(buffer2, "Ya quedo", 7) != 0){
        n=n+1;
        bzero(buffer,LONGITUD_MAX +1);
        int k = recvfrom(socket,buffer,LONGITUD_MAX + 1,0,(struct sockaddr *)&cli_addr,&tam);
        printf("%d --- AQUI TERMINA EL %d\n", buffer, n);
        if (strncmp(buffer, "Ya quedo", 7) != 0){
                if (fwrite(buffer, 1, k, archivo) == -1)
                return 0;
        }
        else
            strncpy(buffer2, buffer, 8);
    }
    if(fclose (archivo) != 0){
        printf("El archivo no se pudo cerrar correctamente\n");
        return 0;
    }
    return 0;
}

int main(int argc, char *argv[]){
	int sockfd;
	struct sockaddr_in serv_addr, cli_addr;
    unsigned char buffer[256];
    FILE *archivo;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

	bzero((char *) &cli_addr, sizeof(cli_addr));

    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = inet_addr(argv[1]);
    cli_addr.sin_port = htons(atoi(argv[2]));


	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    bzero(buffer,256);
	int tam = sizeof(cli_addr);
    sendto(sockfd,"I got your message",18,0,(struct sockaddr *)&cli_addr, sizeof(cli_addr));
    recibir(sockfd, buffer, cli_addr);
    //recvfrom(sockfd,buffer,256,0,(struct sockaddr *)&cli_addr,&tam);
    printf("Ya \n");
    close(sockfd);
    return 0;
}
