#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#define DEVICE_NAME "eeprom_dev"
static int eeprom_probe(struct i2c_client *eeprom_client, const struct i2c_device_id *eeprom_device_id)
{
	u8 buff[6];
	printk("匹配成功,IIC总线为%d\n",eeprom_client->adapter->nr);
	printk("设备名称为%s\n",eeprom_client->name);
	i2c_smbus_write_i2c_block_data(eeprom_client,0,6,"jcning");
	mdelay(10);
	i2c_smbus_read_i2c_block_data(eeprom_client,0, 6,buff);
	buff[6]='\0';
	printk("获取到的字符串为%s\n",buff);
	return 0;
}
static int eeprom_remove(struct i2c_client *eeprom_client)
{
	printk("资源释放完成\n");
	return 0;
}
struct i2c_device_id eeprom_id_table[]={//写成数值是因为id_table可以表示多个匹配
			{DEVICE_NAME},
			{}
};
static struct i2c_driver eeprom_driver={
	.probe=eeprom_probe,
	.remove=eeprom_remove,
	.driver={
			.name=DEVICE_NAME//IIC实际是通过id_table匹配
	},
	.id_table=eeprom_id_table//IIC实际是通过id_table匹配
};
static int __init eeprom_drv_init(void){
	int ret; 
	/*1、注册I2C驱动*/
	ret=i2c_add_driver(&eeprom_driver);
	if(ret<0){
		printk("I2C驱动注册失败\n");
	}
	printk("I2C驱动注册成功\n");
	return 0;
}
static void __exit eeprom_drv_exit(void) {
	/*1、注销I2C驱动*/
	i2c_del_driver(&eeprom_driver);
	printk("I2C驱动注销成功\n");
}

module_init(eeprom_drv_init);
module_exit(eeprom_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


























