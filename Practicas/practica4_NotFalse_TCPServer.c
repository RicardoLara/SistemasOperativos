#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

int i = 0;

void error(const char *msg){
    perror(msg);
    exit(1);
}

void * aceptar(void * fd){
    FILE *archivo;
    unsigned char my_id;
    int newsockfd = (int*)fd;
    unsigned char buffer[256];
    int num, n = 0;
    bzero(buffer,256);
    printf("I: %d\n",i);
    switch(i){
        case 1: archivo = fopen("img5.png", "rb"); my_id = '1'; break;
        case 0: archivo = fopen("img1.jpg", "rb"); my_id = '0'; break;
        case 2: archivo = fopen("p1.pdf", "rb"); my_id = '2'; break;
        case 3: archivo = fopen("Stromae-Papaoutai.mp3", "rb"); my_id = '3'; break;
        case 4: archivo = fopen("JusticeLeague#30.cbr", "rb"); my_id = '4'; break;
    } i++;
    if (archivo == NULL){
        printf ( "Error en la apertura. Es posible que el fichero no exista \n ");
        fclose (archivo);
        return 0;
    }
    printf("Estoy enviando el archivo %c\n",my_id);
    send(newsockfd,&my_id,1,0);
    while(!feof(archivo)){
        n = n+1;
        bzero(buffer,256);
        num = fread(buffer, 1, 256, archivo);
        send(newsockfd,buffer,num ,0);
        printf("%s|--- AQUI TERMINA EL %d\n", buffer, n);
    }
    strcpy(buffer,""); strcpy(buffer,"Ya quedo");
    printf("ESTOY MANDANDO +%s+ al wey.\n",buffer );
    send(newsockfd,buffer,strlen(buffer),0);
    if(fclose (archivo) != 0){
        printf("El archivo no se pudo cerrar correctamente\n");
        return 0;
    }
    printf("Saliendo\n");
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int n, sockfd, newsockfd[5], portno;
    pthread_t thread[5];

    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
       error("ERROR bind");
    listen(sockfd,5);

    while (1){
	    newsockfd[i] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	    if (newsockfd < 0) error("ERROR accept");
	    printf("Soy el cliente %d\n", i);
	    pthread_create (&thread[i], NULL, aceptar, (void *)newsockfd[i]);
    }
    return 0;
}
