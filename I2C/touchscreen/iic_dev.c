#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

static struct i2c_client *i2cClient = NULL;

static unsigned short const i2c_addr_list[] = 
{ 
	0x38, I2C_CLIENT_END
};//地址队列

struct i2c_adapter *i2c_adap;//获取到的总线存放在这个结构体
static int __init i2c_dev_init(void)
{
	
	struct i2c_board_info i2c_info;//设备描述结构体，里面存放着欲设备的名字还有地址

	/*获取IIC控制器*/
	i2c_adap = i2c_get_adapter(1);

	/*清空结构体*/
	memset(&i2c_info,0,sizeof(struct i2c_board_info));

	/*名称的赋值*/
	strlcpy(i2c_info.type,"FT5X06",I2C_NAME_SIZE);

   	/*获取中断号*/
	 i2c_info.irq=gpio_to_irq(EXYNOS4_GPX1(6));
	
	/*创建IIC设备--客户端*/
	i2cClient = i2c_new_probed_device(i2c_adap,&i2c_info,i2c_addr_list,NULL);

	/*设置模块信息  */
	i2c_put_adapter(i2c_adap);

	printk("i2c_dev_init!!\n");
	return 0;
}


static void __exit i2c_dev_exit(void)//平台设备端的出口函数
{
	printk(" i2c_dev_exit ok!!\n");

	/*注销设备*/
	i2c_unregister_device(i2cClient);

	/*释放*/
	i2c_release_client(i2cClient);
	
	//增加模块计数
	try_module_get(i2c_adap->owner);
}


module_init(i2c_dev_init);
module_exit(i2c_dev_exit);
MODULE_LICENSE("GPL");

