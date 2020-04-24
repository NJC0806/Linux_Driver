#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#define DEVICE_NAME "eeprom_dev"
static int eeprom_probe(struct i2c_client *eeprom_client, const struct i2c_device_id *eeprom_device_id)
{
	u8 buff[6];
	printk("ƥ��ɹ�,IIC����Ϊ%d\n",eeprom_client->adapter->nr);
	printk("�豸����Ϊ%s\n",eeprom_client->name);
	i2c_smbus_write_i2c_block_data(eeprom_client,0,6,"jcning");
	mdelay(10);
	i2c_smbus_read_i2c_block_data(eeprom_client,0, 6,buff);
	buff[6]='\0';
	printk("��ȡ�����ַ���Ϊ%s\n",buff);
	return 0;
}
static int eeprom_remove(struct i2c_client *eeprom_client)
{
	printk("��Դ�ͷ����\n");
	return 0;
}
struct i2c_device_id eeprom_id_table[]={//д����ֵ����Ϊid_table���Ա�ʾ���ƥ��
			{DEVICE_NAME},
			{}
};
static struct i2c_driver eeprom_driver={
	.probe=eeprom_probe,
	.remove=eeprom_remove,
	.driver={
			.name=DEVICE_NAME//IICʵ����ͨ��id_tableƥ��
	},
	.id_table=eeprom_id_table//IICʵ����ͨ��id_tableƥ��
};
static int __init eeprom_drv_init(void){
	int ret; 
	/*1��ע��I2C����*/
	ret=i2c_add_driver(&eeprom_driver);
	if(ret<0){
		printk("I2C����ע��ʧ��\n");
	}
	printk("I2C����ע��ɹ�\n");
	return 0;
}
static void __exit eeprom_drv_exit(void) {
	/*1��ע��I2C����*/
	i2c_del_driver(&eeprom_driver);
	printk("I2C����ע���ɹ�\n");
}

module_init(eeprom_drv_init);
module_exit(eeprom_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


























