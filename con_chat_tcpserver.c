#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 1024

int create_task(void*(*task)(void*), void* arg)
{
    int ret = 0;
    pthread_t id;

    ret = pthread_create (&id, NULL, (void*)task, arg);
    if (ret != 0)
    {
        printf("Create pthread error!/n");
        return -1;
    }

    // Wait for the thread to finish
    ret = pthread_join(id, NULL);
    if (ret != 0)
    {
        printf("Join pthread error!/n");
        return -1;
    }

    return id;
}

void *chatfunc(void* arg)
{
    int connfd = *(int*)arg;
    char buf[BUF_SIZE];
    char msg[BUF_SIZE];

    while(1)
    {
        recv(connfd, buf, sizeof(buf), 0);
        printf("from server: %s\n", buf);

        printf("please chat:");
        scanf("%s", msg);
        send(connfd, msg, strlen(msg), 0);
    }

    close(connfd);
}

int main ()
{
    int sockfd;
    int connfd;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    socklen_t addrlen = sizeof(clientaddr);

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    listen(sockfd, 10);

    while(1)
    {
        connfd = accept(sockfd, (struct sockaddr*)&clientaddr, &addrlen);

        create_task(chatfunc, (void*)&connfd);
    }

    close(sockfd);

    return 0;
}