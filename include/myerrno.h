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

//get error reason
const char *getMyError();

void printInfo(const char *info);
void printErr(const char *err); 

#endif //__MYERRNO_H__

