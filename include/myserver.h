#ifndef __MYSERVER_H__
#define __MYSERVER_H__

/**
 * 初始化服务器
 * @param port 绑定端口
 * @return 如果成功返回socket描述符，失败返回-1
 */
int initServer(unsigned short port);


#endif //__MYSERVER_H__