#include "myserver.h"
#include "myerrno.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h> /*memset*/

int initServer(unsigned short port)
{
	//创建serverSocket
	int serverSocket;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	//配置地址
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//配置端口可重用
	int opt = 1;
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	//绑定端口
	if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		printSystemError("bind");
		return -1;
	}

	//监听，配置最大连接数
	if(listen(serverSocket, SOMAXCONN))
	{
		printSystemError("listen");
		return -1;
	}

	int clientSocket;
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	//接收客户端的连接请求
	if((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen)) < 0)
	{
		printSystemError("accept");
		return -1;
	}

	//打印客户端信息
	printf("client: %s:%u connected!\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	
	//关闭serverSocket
	close(serverSocket);

	return clientSocket;
}
