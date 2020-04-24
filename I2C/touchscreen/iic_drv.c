#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/workqueue.h>

static struct work_struct work;
static  struct i2c_client *client_drv;
static const struct i2c_device_id i2c_id[] =
{
	{"FT5X06",0},//设备端的名字为"myiic",0表示不需要私有数据
	{}
};


//工作队列处理函数
static void work_func(struct work_struct *work)
{
	s32 x=0,y=0,num=0;
	
	/*1. 读出按下的点数量*/
	num=i2c_smbus_read_byte_data(client_drv,0x02)&0x0f;
	
	/*2. 读取X坐标*/
	x=(i2c_smbus_read_byte_data(client_drv,0x03)&0x0f)<<8; //高位
	x|=i2c_smbus_read_byte_data(client_drv,0x04); //低位

	/*3. 读取Y坐标*/
	y=(i2c_smbus_read_byte_data(client_drv,0x05)&0x0f)<<8; //高位
	y|=i2c_smbus_read_byte_data(client_drv,0x06); //低位

	printk("num=%d,x=%d,y=%d\n",num,x,y);	
}



//中断服务函数
static irqreturn_t irq_handler(int irq, void *dev)
{
	schedule_work(&work); 
	return IRQ_NONE;
}


static int i2c_probe(struct i2c_client *client, const struct i2c_device_id *device_id)//匹配成功时调用
{	
    client_drv=client;
	printk("i2c_probe!!!\n");
	printk("驱动端IIC匹配的地址=0x%x\n",client->addr);
	
    /*注册触摸屏的中断*/
    if(request_irq(client->irq,irq_handler,IRQ_TYPE_EDGE_BOTH,client->name,NULL)!=0)
	{
        printk("中断注册失败!\n");
	}

	/*初始化工作*/
	INIT_WORK(&work,work_func);
    return 0;
}


static int i2c_remove(struct i2c_client *client)
{
	printk("i2c_remove!!!\n");
	//注销中断
	free_irq(client->irq,NULL);
	return 0;
}

struct i2c_driver i2c_drv =
{
	.driver = //这个不添加会报错，实际上没作用
	{
		.name = "XL",
		.owner = THIS_MODULE,
	},	
	.probe = i2c_probe,  //探测函数
	.remove = i2c_remove, //资源卸载
	.id_table = i2c_id,  //里面有一个名字的参数用来匹配设备端名字
};


/*iic驱动端*/
static int __init i2c_drv_init(void)
{
	i2c_add_driver(&i2c_drv);//向iic总线注册一个驱动
	return 0;
}

static void __exit i2c_drv_exit(void)//平台设备端的出口函数
{
	i2c_del_driver(&i2c_drv);
}

module_init(i2c_drv_init);
module_exit(i2c_drv_exit);
MODULE_LICENSE("GPL");


