#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 5000
int main()
{
    int sock = 0;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    char msg[64] = {0};
    char buf[64] = {0};

    //1.创建UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    while (1)
    {
        //2.发送客户端请求
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(SERVER_PORT);
        addr.sin_addr.s_addr = inet_addr("10.211.55.11");//服务器IP地址

        printf("输入向服户端发送的信息:\n");
        scanf("%s", msg);
        sendto(sock, msg, strlen(msg), 0, (struct sockaddr *)&addr, addrlen);

        //3.接收服务器应答
        recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addrlen);
        printf("服务器应答: %s\n", buf);
    }
}