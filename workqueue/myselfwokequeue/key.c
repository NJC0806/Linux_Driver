#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
/*按键设备信息*/
struct key_info
{
	int gpio;
	int key_val;
	int flag;
	char name[10];
	int irq;
	struct workqueue_struct *my_work_queue;
	struct work_struct key_work;
};
static struct key_info key_dev;
static void key_work_function(	struct work_struct *work)
{
	if(gpio_get_value(key_dev.gpio))
	{
		printk("按下\n");	
	}
	else
	{
		printk("松开\n");
	}
}
irqreturn_t key_irq_handler(int irq, void *dev)
{
	printk("进入中断\n");
	queue_work(key_dev.my_work_queue,&key_dev.key_work);
	return IRQ_HANDLED;
}
static int __init key_init(void)
{
	key_dev.gpio=EXYNOS4_GPX3(2);
	key_dev.key_val=0x5;
	key_dev.flag=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING;
	key_dev.name[10]="key1";
	key_dev.my_work_queue=create_workqueue("key_dev");
	key_dev.irq=gpio_to_irq(key_dev.gpio);
	if(request_irq(key_dev.irq,key_irq_handler,key_dev.flag,key_dev.name,&key_dev))
	{
		printk("中断注册失败\n");
	}
	INIT_WORK(&key_dev.key_work,key_work_function);
	printk("my驱动注册成功\n");
	return 0;
}
static void __exit key_exit(void)
{
	free_irq(key_dev.irq,&key_dev);
	destroy_workqueue (key_dev.my_work_queue);
	printk("my驱动注册失败\n");
}
module_init(key_init);
module_exit(key_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


