#ifndef __MYERRNO_H__
#define __MYERRNO_H__

typedef enum
{
	MYERR_SUCCESS,
	MYERR_ALREADY_HAS_NAME,
	MYERR_NO_SUCH_NAME,
	MYERR_UNKNOW_ERR,
	MYERR_NO_VALUE,
	MYERR_ARGS_FEW,
	MYERR_ARGS_MORE,
	MYERR_ARGS_INVALID,
}MyErrNo;

extern MyErrNo g_my_errno;

/**
 * 获取自定义错误
 */
const char *getMyError();

/**
 * 打印系统错误信息
 * @param msg 错误提示
 */
void printSystemError(const char *msg);

/**
 * 打印自定义错误信息
 * @param msg 错误提示
 */
void printMyError(const char *msg);

#endif //__MYERRNO_H__

