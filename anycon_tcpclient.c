#include <stdio.h>

//TCP异步并发服务器测试客户端
int main ()
{
	char msg[128] = {0};
	
	//1. 创建TCP socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//2. 向服务器发起连接
	//给saddr设定服务器端的ip和端口号
	connect(sockfd,(struct sockaddr*)&saddr, sizeof(saddr));

	//3. 循环发送
	while(1)
	{
		//先情空缓存
		memset(msg, 0 , sizeof(msg));
		
		//从控制台获取消息输入
		printf("please input:");
		scanf("%s", msg);
		
		if ('q' == msg[0])
		{
			break; //消息输入结束
		}
		else
		{
			//向服务器发信息
			send(sockfd, msg, strlen(msg), 0);
		}
	}
	
	close(sockfd);	
	
	return 0;
}