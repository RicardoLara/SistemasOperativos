#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> 
#include <arpa/inet.h>  
#include <unistd.h> 

int main(int argc, char *argv[]){ 
	char buf[256], c = '\n'
    char *p_buf;
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
    	printf("Cliente: ");
    	gets(buf);
        len = strlen(buf);
        p_buf = buf;
        while (len > 0){
            k = send(sock_desc, p_buf, len, 0);      
            if (k == -1){
                printf("cannot write to server!\n");
                break;
            }
            p_buf += k;
            len -= k;
        }
        k = send(sock_desc, &c, 1, 0);      
        if (k == -1){
            printf("cannot write to server!\n");
            break;
        }
        if (strcmp(buf, "exit") == 0) break;
        strcpy(buf,"");
        int n_bits = recv(sock_desc,buf,100,0);
        printf("Server: ");
        for(k=0; k<n_bits; k++) printf("%c",buf[k]);
        printf("\n");
    }  
    close(sock_desc);  
    printf("client disconnected\n");
    return 0;  
} 
