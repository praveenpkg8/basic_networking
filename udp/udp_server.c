#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080


struct details{
        int rollno;
        char name[1024];
        int dept;
    };

int main(int argc, char const *argv[])
{
    int servsock, clisock;
    struct sockaddr_in server, client;
    int clilen, servlen;
    char *buffer;
    struct details s;



    if((servsock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
        perror("socket connection failed");
        exit(EXIT_FAILURE);
    }
    bzero((struct *sockaddr)&servsock, sizeof(servsock));
    bzero((struct *sockaddr)&clisock, sizeof(clisock));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htons(INADDR_ANY);

    if((bind(server, (struct *sockaddr)&server, sizeof(server))) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    clilen = sizeof(client);

    do{
        recvfrom(servsock, &s, sizeof(s), 0, (struct *sockaddr)&client, &clilen);
        if(s.dept == 1){
            buffer = "\n we have a common interest as cs";
            printf("%d", sizeof(buffer));
            sendto(servsock, buffer, 1024, 0, (struct sockaddr*) &client, clilen);
        }
        else{
            buffer = "\nwe dont have a common interest";
            sendto(servsock, buffer, 1024, 0, (struct sockaddr*) &client, clilen);
        }
        printf("\npress 0 to exit");
        printf("\n");

        scanf("%d", &a);
    }while(a != 0);

    close(servsock);
    close(clisock);
    return 0;
}


