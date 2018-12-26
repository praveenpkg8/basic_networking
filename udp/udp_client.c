#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define PORT 8080

struct details{
        int rollno;
        char name[1024];
        int dept;
    };

int main(int argc, char const *argv[])
{
    int clisock;
    struct sockaddr_in client;
    char buffer[1024];
    socklen_t clientsize;
    int a;
    
    struct details s;

    if((clisock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("socket connection failed");
    }

    bzero((struct sockaddr*)&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = htons(INADDR_ANY);

    clientsize = sizeof(client);

    do{
            printf("Enter the name: ");
            scanf("%s", s.name);

            printf("Enter the roll no: ");
            scanf("%d", &s.rollno);

            printf("Enter the department: ");
            scanf("%d", &s.dept);
            
            sendto(clisock, &s, sizeof(s), 0, (struct sockaddr*) &client, sizeof(client));
            write(clisock, &s, sizeof(s));
            listen(clisock,1);
            
            recvfrom(clisock, buffer, 1024, 0, (struct sockaddr*) &client, &clientsize);
            read(clisock, buffer, sizeof(buffer));
            printf("Server: %s\n", buffer);

            printf("\npress 0 to exit");
            printf("\n");
            scanf("%d", &a);

        }while( a != 0);

    
    close(clisock);
    
    return 0;
}

