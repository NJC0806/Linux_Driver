#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#define DEVICE_NAME "eeprom_dev"

static struct i2c_adapter * epm_ad=NULL;
struct i2c_client *eeprom_client=NULL;
static struct i2c_board_info eeprom_dev_info; 
static int __init eeprom_dev_init(void){
	/*1��ע��������*/
	epm_ad=i2c_get_adapter(0);//eeprom��ԭ��ͼ����IIC����0��(Xi2cSCL0)
	if(epm_ad==NULL){
		printk("������ע��ʧ��\n");
		return  -EBUSY;
	}
	/*2����д�弶��Ϣ*/
	strncpy(eeprom_dev_info.type,DEVICE_NAME,20);
	eeprom_dev_info.addr=0x50;
	/*3��������豸*/
	eeprom_client = i2c_new_device(epm_ad,&eeprom_dev_info);
	if(eeprom_client==NULL){
		printk("������豸ʧ��\n");
		return  -EBUSY;
	}
	printk("eeprom����ע��ɹ�\n");
	return 0;
}
static void __exit eeprom_dev_exit(void) {
	int ret;
	/*1��ע��������*/
	ret=i2c_del_adapter(epm_ad);
	if(ret<0){
		printk("������ע��ʧ��\n");
	}
	/*2��ע���豸*/
	i2c_unregister_device(eeprom_client);
	printk("eeprom����ж�سɹ�\n");
}
module_init(eeprom_dev_init);
module_exit(eeprom_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");




