/*
时	  间：2020-3-31
作	  者：jcning
联系方式：1959289104@qq.com
文件描述：
		 该文件主要是为了测试杂项设备框架所写的驱动代码。
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include "beep.h"
static int beep_open(struct inode *inode , struct file *file)
{
	printk("打开成功\n");//在应用层调用open函数时候执行
	return 0;
}
static long beep_unlocked_ioctl(struct file *file , unsigned int cmd, unsigned long argv)
{
	switch(cmd){
		case BEEP_OFF:
						gpio_set_value(EXYNOS4_GPD0(0),0);
						break;
		case BEEP_ON:
						gpio_set_value(EXYNOS4_GPD0(0),1);
						break;
	}
	return 0;
}
static int beep_release(struct inode *inode, struct file *file )
{
	printk("关闭成功\n");//在应用层调用close函数时候执行
	return 0;
}

struct file_operations beep_fops={
	.open=&beep_open,
	.release=&beep_release,
	.unlocked_ioctl=beep_unlocked_ioctl
};

struct miscdevice beep_misc={
	.minor=MISC_DYNAMIC_MINOR,//次设备号，0-254 255 表示自动分配次设备号
	.name=DEVICE_NAME,//设备文件的名称
	.fops=&beep_fops//虚拟文件操作集合，为应用层操作驱动提供接口
};

/*安装驱动时候执行*/
static int __init beep_init(void) {
	int ret;
	gpio_request(EXYNOS4_GPD0(0),"BEEP");//请求GPIO
	s3c_gpio_cfgpin(EXYNOS4_GPD0(0), S3C_GPIO_OUTPUT);//配置GPIO的模式
	gpio_set_value(EXYNOS4_GPD0(0),0);//下拉
	ret=misc_register(&beep_misc);//注册杂项设备
	if(ret<0)
		printk("beep驱动安装失败\n");
	else
		printk("beep驱动安装成功\n");
	return 0;
}

/*卸载驱动时候执行*/
static void __exit beep_exit(void){
	int ret;
	gpio_free(EXYNOS4_GPD0(0));
	ret=misc_deregister(&beep_misc);
	if(ret<0)
		printk("beep驱动卸载失败\n");
	else
		printk("beep驱动卸载成功\n");
};

module_init(beep_init);
module_exit(beep_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


