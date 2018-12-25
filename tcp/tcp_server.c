#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080


int main(int argc, char const *argv[])
{
    int sock, clisock;
    int len;
    char buffer[1024];
    struct sockaddr_in server, client;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    bzero((struct sockaddr*)&server, sizeof(server));
    bzero((struct sockaddr*)&client, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htons(INADDR_ANY);

    if((bind(sock, (struct sockaddr*)&server, sizeof(server))) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(sock, 5) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    len = sizeof(client);

    clisock = accept(sock, (struct sockaddr*)&client, &len);

    if(clisock < 0){
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    do{
        read(clisock, buffer, sizeof(buffer));
        printf("\nclient: %s", buffer);

        printf("\nserver: ");
        scanf("%s", buffer);

        write(clisock, buffer, sizeof(buffer));

    }while(strcmp(buffer,"bye") != 0);

    close(sock);
    close(clisock);

    
    return 0;
}
