#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/input.h>
#define DEICE_NAME "touchscreen_dev"
struct work_struct touchscreen_work;
struct i2c_client *client;
struct input_dev *touch_input;

static irqreturn_t touchscreen_irq_handler_t(int irq, void *arg)
{
	schedule_work(&touchscreen_work);
	return IRQ_HANDLED;
}
static void touchscreen_work_fn(struct work_struct *touchscreen_work)
{
	u8 buff[7];
	u32 x,y;
	i2c_smbus_read_i2c_block_data(client,0,7, buff);
	x=(buff[3]&0xF)<<8|buff[4];
	y=(buff[5]&0xF)<<8|buff[6];
	if(buff[2]&0xF)	{
		input_report_abs(touch_input, ABS_X, x);
		input_report_abs(touch_input, ABS_Y, y);
		input_report_abs(touch_input, ABS_PRESSURE, 1);
	}
	else{
		input_report_abs(touch_input, ABS_X, x);
		input_report_abs(touch_input, ABS_Y, y);
		input_report_abs(touch_input, ABS_PRESSURE, 0);
	}
	input_sync(touch_input);
}
static int touchscreen_probe(struct i2c_client *touchscreen_client,
									   const struct i2c_device_id *touchscreen_device_id)
{
	int ret;
	printk("匹配成功，总线编号为%d\n",touchscreen_client->adapter->nr);
	printk("中断编号为%d\n",touchscreen_client->irq);
	printk("设备的名字为%s\n",touchscreen_client->name);
	client=touchscreen_client;
	INIT_WORK(&touchscreen_work,touchscreen_work_fn);
	if(request_irq(touchscreen_client->irq,touchscreen_irq_handler_t,
					IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING, DEICE_NAME, NULL)){
		printk("中断注册失败\n");
		return -EBUSY;
	}
	/*2、动态分配input_dev结构体*/
	touch_input=input_allocate_device();
	/*3、设置上报类型*/
	input_set_capability(touch_input, EV_ABS,ABS_X);
	input_set_capability(touch_input, EV_ABS,ABS_Y);
	input_set_capability(touch_input, EV_ABS,ABS_PRESSURE);
	/*4、限制上报的范围*/
	input_set_abs_params(touch_input, ABS_X,0,799,0,0);
	input_set_abs_params(touch_input, ABS_Y,0,479,0,0);
	input_set_abs_params(touch_input, ABS_PRESSURE,0,1,0,0);
	/*5、注册输入子系统*/
	ret=input_register_device(touch_input);
	if(ret<0){
		printk("输入子系统注册失败\n");
	}
	return 0;
}
static int touchscreen_remove(struct i2c_client *touchscreen_client)
{
	free_irq(touchscreen_client->irq,NULL);
	/*2、注销输入子系统*/
	input_unregister_device(touch_input);
	printk("资源释放成功\n");
	return 0;
}
struct i2c_device_id touchscreen_id_table[]={
		{DEICE_NAME,0},
		{}
};
static struct i2c_driver touchscreen_driver={
	.probe=touchscreen_probe,
	.remove=touchscreen_remove,
	.driver={
		.name=DEICE_NAME,
	},
	.id_table=touchscreen_id_table,
};
static int __init touchscreen_drv_init(void){
	int ret; 
	/*1、注册I2C驱动*/
	ret=i2c_add_driver(&touchscreen_driver);
	if(ret<0){
		printk("I2C驱动注册失败\n");
	}
	printk("I2C驱动注册成功\n");
	return 0;
}
static void __exit touchscreen_drv_exit(void) {
	/*1、注销I2C驱动*/
	i2c_del_driver(&touchscreen_driver);
	
	printk("I2C驱动注销成功\n");
}

module_init(touchscreen_drv_init);
module_exit(touchscreen_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


























