/*
ʱ	  �䣺2020-3-31
��	  �ߣ�jcning 
��ϵ��ʽ��1959289104@qq.com
�ļ�������
		 ���ļ���Ҫ��Ϊ�˲��������豸������д��Ӧ�ò���롣
		 
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
		printf("%s �ļ���ʧ��.\n",argv[1]);
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

