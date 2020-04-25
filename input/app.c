#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <signal.h>
#include <unistd.h>
#include <linux/input.h>
int fd,lenth;
struct input_event key_input;
/*
struct input_event {
	struct timeval time;
	__u16 type;
	__u16 code;
	__s32 value;
};
*/
int main(int argc ,char ** argv)
{
	if(argc!=2)
	{
		printf("./app /dev/inputx");
		return -1;
	}
	fd=open(argv[1],O_RDWR);
	if(fd<0)
	{
		printf("节点打开失败\n");
		return -1;
	}
	while(1)
	{
		lenth=read(fd,&key_input,sizeof(struct input_event));
		if(lenth==sizeof(struct input_event)){
			switch(key_input.code)
			{
				case KEY_L:
					printf("type=%d value=%d\n",key_input.type,key_input.value);break;
				case KEY_S:
					printf("type=%d value=%d\n",key_input.type,key_input.value);break;
				case KEY_ENTER:
					printf("type=%d value=%d\n",key_input.type,key_input.value);break;
				case KEY_BACKSPACE:
					printf("type=%d value=%d\n",key_input.type,key_input.value);break;
			}
		}
	}
	close(fd);
	return 0;
}
