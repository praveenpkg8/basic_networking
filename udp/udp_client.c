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
    int a = 1024;
    

    if((clisock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("socket connection failed");
    }

    bzero((struct sockaddr*)&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = htons(INADDR_ANY);

    clientsize = sizeof(client);
            struct details s;


    do{

            printf("\nEnter the name: ");
            scanf("\n %[^\n]%*c", s.name);

            printf("Enter the roll no: ");
            scanf("%d", &s.rollno);

            printf("Departments: \n ");
            printf("1. computer science \n ");
            printf("2. Information Technology \n ");
            printf("3. Mechanical \n ");
            printf("4. Electical \n ");
            printf("5. communication \n");






            printf("Enter the department No: ");
            scanf("%d", &s.dept);
            
            sendto(clisock, &s, sizeof(s), 0, (struct sockaddr*) &client, sizeof(client));
            
            recvfrom(clisock, buffer, 1024, 0, (struct sockaddr*) &client, &clientsize);
            printf("Server: %s\n", buffer);
            fflush(stdin);

        }while(1);

    
    close(clisock);
    
    return 0;
}

