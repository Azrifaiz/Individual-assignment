#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/if.h>
#include <time.h>
#include <stdlib.h>


#define MAX 1000

void func(int sockfd)
{
    char buff[MAX];
    int n;
    // To get the current time
    time_t current_time;
    char* c_time_string;

    for (;;)
    {
        bzero(buff, MAX);
        time_t now = time(&now);
        int n;
        struct ifreq ifr;
        char array[] = "enp0s8";

        // To print the current time
        if (now == -1)
        {
             puts("The time() function failed");
        }

        struct tm *ptm = gmtime(&now);

        if (ptm == NULL)
        {
             puts("The gmtime() function failed");
        }

        bzero(buff, sizeof(buff));
        printf("Enter message to server : ");
        n = 0;
        bzero(buff, MAX);
        while ((buff[i++] = getchar()) != '\n');
        if (strncmp("exit", buff, 4) == 0)
        {
             printf("\nClient Exit...\n\n");
             break;
        }
        write(sockfd, buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("\nCurrent time            : %s", asctime(ptm));
        printf("Server Name             : %s", getlogin());
        printf("\nMessage from server     : %s", buff);
    }
    n = 0;
}

int main()
{
    time_t now = time(&now);
    int sockfd, connfd;
    struct ifreq ifr;
    struct sockaddr_in server, client;
    char array[] = "enp0s8";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        puts("Socket creation failed....\n");
        exit(0);
    }
    else{
        printf("\nSocket successfully created...\n");
        bzero(&server, sizeof(server));
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.66.5");
    server.sin_port = htons(123);

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) != 0) {
        puts("Connection with the server failed...\n");
        exit(0);
    }
    else{
        printf("Client is connected to the NTP server...\n");
        printf("\nThis is PC-01 Client...\n");
    }

    func(sockfd);
    close(sockfd);
}
