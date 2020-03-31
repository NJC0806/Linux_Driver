/*
时	  间：2020-3-31
作	  者：jcning 
联系方式：1959289104@qq.com
文件描述：
		 该文件主要是为了测试杂项设备驱动所写的应用层代码。
		 
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "beep.h"
int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("./app /dev/beep\n");
		return 0;
	}
	int fd=open(argv[1],O_RDWR);
	if(fd<0)
	{
		printf("%s 文件打开失败.\n",argv[1]);
		return 0;
	}
	
	while(1)
	{
		ioctl(fd,BEEP_OFF);
		sleep(1);
		ioctl(fd,BEEP_ON);
		sleep(1);
	}
	close(fd);
	return 0;
}

