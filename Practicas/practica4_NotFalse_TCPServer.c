/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void escribir(int ds){

        char buf[100];
    char c = '\n';
    char *p_buf;
    int k, len;  
        gets(buf);

        len = strlen(buf);
        p_buf = buf;

        while (len > 0)
        {
            k = send(ds, p_buf, len, 0);      
            if (k == -1)
            {
                printf("cannot write to server!\n");
                break;
            }

            p_buf += k;
            len -= k;
        }

        k = send(ds, &c, 1, 0);
        if (k == -1)  printf("cannot write to server!\n");
}

void * aceptar(void * fd){
    int n, newsockfd = (int*)fd;
    char buffer[256];
    bzero(buffer,256);
    while(strncmp(buffer,"exit",4) != 0) { 
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR read");
        printf("Mensaje recibido: %s\n",buffer);
        escribir(newsockfd);
    }
    printf("Saliendo\n");
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int n, sockfd, newsockfd[5], portno,i=0;
    pthread_t thread[5];

    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       error("ERROR socket");
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
	    printf("Soy el cliente %d\n", i+1);
	    pthread_create (&thread[i], NULL, aceptar, (void *)newsockfd[i++]);
    }
    return 0;
}
