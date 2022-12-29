#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 64

int main ()
{
    int sockfd;
    struct sockaddr_in saddr;
    char chat[BUF_SIZE] = {0};
    char buf[BUF_SIZE] = {0};

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("192.168.31.198");
    saddr.sin_port = htons(8080);

    connect(sockfd,(struct sockaddr*)&saddr, sizeof(saddr));

    while(1)
    {
        memset(chat, 0 , sizeof(chat));
        memset(buf, 0 , sizeof(buf));

        printf("please chat:");
        scanf("%s", chat);

        send(sockfd, chat, strlen(chat), 0);

        recv(sockfd, buf, sizeof(buf), 0);
        printf("from server: %s\n", buf);
    }

    close(sockfd);

    return 0;
}