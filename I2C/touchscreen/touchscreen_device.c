#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#define DEICE_NAME "touchscreen_dev"

static struct i2c_adapter * touchscreen_adp=NULL;
static struct i2c_board_info touchscreen_info;
static struct i2c_client * touchscreen_client=NULL;
static int __init touchscreen_dev_init(void){
	/*1����ȡ������*/
	touchscreen_adp=i2c_get_adapter(1);//��ԭ��ͼ����IIC����1��
	if(touchscreen_adp==NULL){
		printk("������ע��ʧ��\n");
		return -EBUSY;
	}
	/*2�����弶�ṹ��*/
	strncpy(touchscreen_info.type,DEICE_NAME,20);
	touchscreen_info.addr=0x38;
	touchscreen_info.irq=gpio_to_irq(EXYNOS4_GPX1(6));
	/*3�����I2C�豸*/
	touchscreen_client=i2c_new_device(touchscreen_adp,&touchscreen_info);
	if(touchscreen_client==NULL){
		printk("���I2C�豸ʧ��\n");
		return -EBUSY;
	}
	printk("������װ�ɹ�\n");
	return 0;
}
static void __exit touchscreen_dev_exit(void) {
	if(touchscreen_client){
		i2c_unregister_device(touchscreen_client);
	}
	printk("touchscreen����ж�سɹ�\n");
}
module_init(touchscreen_dev_init);
module_exit(touchscreen_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");




