#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#define DEVICE_NAME "eeprom_dev"

static struct i2c_adapter * epm_ad=NULL;
struct i2c_client *eeprom_client=NULL;
static struct i2c_board_info eeprom_dev_info; 
static int __init eeprom_dev_init(void){
	/*1、注册适配器*/
	epm_ad=i2c_get_adapter(0);//eeprom在原理图上在IIC总线0上(Xi2cSCL0)
	if(epm_ad==NULL){
		printk("适配器注册失败\n");
		return  -EBUSY;
	}
	/*2、填写板级信息*/
	strncpy(eeprom_dev_info.type,DEVICE_NAME,20);
	eeprom_dev_info.addr=0x50;
	/*3、添加新设备*/
	eeprom_client = i2c_new_device(epm_ad,&eeprom_dev_info);
	if(eeprom_client==NULL){
		printk("添加新设备失败\n");
		return  -EBUSY;
	}
	printk("eeprom驱动注册成功\n");
	return 0;
}
static void __exit eeprom_dev_exit(void) {
	int ret;
	/*1、注销适配器*/
	ret=i2c_del_adapter(epm_ad);
	if(ret<0){
		printk("适配器注销失败\n");
	}
	/*2、注销设备*/
	i2c_unregister_device(eeprom_client);
	printk("eeprom驱动卸载成功\n");
}
module_init(eeprom_dev_init);
module_exit(eeprom_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");




