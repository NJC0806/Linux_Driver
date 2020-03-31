/*
ʱ	  �䣺2020-3-31
��	  �ߣ�jcning
��ϵ��ʽ��1959289104@qq.com
�ļ�������
		 ���ļ���Ҫ��Ϊ�˲��������豸�����д���������롣
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
	printk("�򿪳ɹ�\n");//��Ӧ�ò����open����ʱ��ִ��
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
	printk("�رճɹ�\n");//��Ӧ�ò����close����ʱ��ִ��
	return 0;
}

struct file_operations beep_fops={
	.open=&beep_open,
	.release=&beep_release,
	.unlocked_ioctl=beep_unlocked_ioctl
};

struct miscdevice beep_misc={
	.minor=MISC_DYNAMIC_MINOR,//���豸�ţ�0-254 255 ��ʾ�Զ�������豸��
	.name=DEVICE_NAME,//�豸�ļ�������
	.fops=&beep_fops//�����ļ��������ϣ�ΪӦ�ò���������ṩ�ӿ�
};

/*��װ����ʱ��ִ��*/
static int __init beep_init(void) {
	int ret;
	gpio_request(EXYNOS4_GPD0(0),"BEEP");//����GPIO
	s3c_gpio_cfgpin(EXYNOS4_GPD0(0), S3C_GPIO_OUTPUT);//����GPIO��ģʽ
	gpio_set_value(EXYNOS4_GPD0(0),0);//����
	ret=misc_register(&beep_misc);//ע�������豸
	if(ret<0)
		printk("beep������װʧ��\n");
	else
		printk("beep������װ�ɹ�\n");
	return 0;
}

/*ж������ʱ��ִ��*/
static void __exit beep_exit(void){
	int ret;
	gpio_free(EXYNOS4_GPD0(0));
	ret=misc_deregister(&beep_misc);
	if(ret<0)
		printk("beep����ж��ʧ��\n");
	else
		printk("beep����ж�سɹ�\n");
};

module_init(beep_init);
module_exit(beep_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


