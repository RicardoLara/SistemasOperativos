#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int LONGITUD_MAX = 255;

int enviar(int sockfd, struct sockaddr_in cli_addr, char id){
	FILE *archivo;
	unsigned char buffer[LONGITUD_MAX + 1];
	int num, n = 0;
	archivo = fopen("p1.pdf", "rb");
	if (archivo == NULL){
		printf ( "Error en la apertura. Es posible que el fichero no exista \n ");
		fclose (archivo);
		return 0;
	}

	while(!feof(archivo)){
		n = n+1;
		bzero(buffer,LONGITUD_MAX +1);
		num = fread(buffer, 1, LONGITUD_MAX, archivo);
		//buffer[num * sizeof(char)] = '\0';
		sendto(sockfd,buffer,num ,0,(struct sockaddr *)&cli_addr, sizeof(cli_addr));
		printf("%s --- AQUI TERMINA EL %d\n", buffer, n);
	}
	sendto(sockfd,"Ya quedo",8,0,(struct sockaddr *)&cli_addr, sizeof(cli_addr));
	if(fclose (archivo) != 0){
        printf("El archivo no se pudo cerrar correctamente\n");
        return 0;
    }
	return 0;
}

int main(int argc, char *argv[]){
	int sockfd;
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[256];
	FILE *archivo;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

	bzero((char *) &cli_addr, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = INADDR_ANY;
    cli_addr.sin_port = htons(atoi(argv[1]));
	while (1){
		bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
		bzero(buffer,256);
		int tam = sizeof(cli_addr);
		recvfrom(sockfd,buffer,256,0,(struct sockaddr *)&cli_addr,&tam);
		if (!strncmp(buffer, "I got your message", 18))
			printf("%s y %d \n", buffer, strlen(buffer));
		else printf("I did not got your message\n");
		enviar(sockfd, cli_addr, '1');
	}
	//sendto(sockfd,"Same",4,0,(struct sockaddr *)&cli_addr, sizeof(cli_addr));
    close(sockfd);
    return 0;
}
