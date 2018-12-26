#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080

struct details{
        int rollno;
        char name[1024];
        int dept;
    };


int main(int argc, char const *argv[])
{
    int sock, clisock;
    int len,a;
    char *buffer;
    struct sockaddr_in server, client;
    struct details s;
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
        read(clisock, &s, sizeof(s));
        if(s.dept == 1){
            buffer = "\n we have a common interest as cs";
            printf("%d", sizeof(buffer));
            write(clisock, buffer, 1024);
        }
        else{
            buffer = "\nwe dont have a common interest";
            write(clisock, buffer, 1024);

        }

        printf("\npress 0 to exit");
        printf("\n");

        // printf("\nserver: ");
        scanf("%d", &a);


    }while(a != 0);

    close(sock);
    close(clisock);

    
    return 0;
}
