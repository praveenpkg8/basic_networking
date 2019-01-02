#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
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
    int clisock;
    int con,a;
    struct sockaddr_in client;
    char buffer[1024];
    
    struct details s;

    bzero((struct sockaddr*)&client, sizeof(client));

    if( ( clisock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("socket creation failed\n");
    
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr =htons(INADDR_ANY);

    con = connect(clisock, (struct sockaddr*)&client, sizeof(client));
    if ( con < 0)
        printf("socket creation failed\n");

    do
    {
         printf("Enter the name: ");
            gets(s.name);

            printf("Enter the roll no: ");
            scanf("%d", &s.rollno);

            printf("Departments: \n ");
            printf("1. computer science \n ");
            printf("2. Information Technology \n ");
            printf("3. Mechanical \n ");
            printf("4. Electical \n ");
            printf("5. communication \n");


        write(clisock, &s, sizeof(s));
        listen(clisock,1);

        read(clisock, buffer, sizeof(buffer));
        printf("Server: %s\n", buffer);

        printf("\npress 0 to exit and to continue press any key");
        printf("\n");
        scanf("%d", &a);



    }while( a != 0);


    close(clisock);
    return 0;
}

