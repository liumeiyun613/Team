#include <stdio.h>

//消息处理任务声明
void *msgfunc(void* arg);

int main ()
{	
	//1. 创建TCP socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//2. 绑定IP地址与端口号
	bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))
	//3. 创建监听客户端连接队列
	listen(sockfd, 10);

	while(1)
	{		
		//4. 等待并建立客户端的连接
		connfd = accept(sockfd, (struct sockaddr*)&clientaddr,socklen_t addrlen);
	
		//5. 为已连接客户端创建消息处理任务
		create_task(msgfunc, (void*)&connfd);
	}
	
	close(sockfd);
	
	return 0;
}

//消息处理任务实现
void *msgfunc(void* arg)
{
	int connfd = *(int*)arg; //连接套接字
	Queue *que = NULL;
	T msg = 0;
	
	//1.创建消息队列
	que = CreateQueue();
	
	while(1)
	{
		//接收对方消息
		recv(connfd, msg, sizeof(msg), 0);
		Push(que, msg);//进队
		
		//对方确认消息接收完备
		if ('q' == msg[0])
		{
			break;
		}
	}
	
	//显示所有已接收消息
	Print(que);
	
	close(connfd);
}
