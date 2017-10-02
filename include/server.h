#ifndef __SERVER_H__
#define __SERVER_H__

/**
 * 初始化服务器
 * @param port 绑定端口
 * @return 如果成功返回socket描述符，失败返回-1
 */
int initServer(unsigned short port);


#endif //__SERVER_H__