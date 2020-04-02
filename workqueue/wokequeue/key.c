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
	struct work_struct key_work;//这个是一个技巧
};

/*初始化按键信息*/
static struct key_info key_dev=
{
	.gpio=EXYNOS4_GPX3(2),
	.key_val=0x5,
	.flag=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
	.name="key1",
};
static void key_work_function(struct work_struct *work)//参数是INIT时候传入的
{
	struct key_info *p=container_of(work,struct key_info,key_work);
	//通过将工作函数定义在总的结构体中，通过工作结构体可以获得总的结构体的首地址
	if(gpio_get_value(p->gpio))
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
	struct key_info *p=(struct key_info *)dev;
	printk("进入中断，开始调度key_work\n");
	schedule_work(&p->key_work);
	return IRQ_HANDLED;
}
static int __init key_init(void)
{
	INIT_WORK(&key_dev.key_work, key_work_function);
	key_dev.irq=gpio_to_irq(key_dev.gpio);
	if(request_irq(key_dev.irq,key_irq_handler,key_dev.flag,key_dev.name,&key_dev))
	{
		printk("中断注册失败\n");
	}
	printk("驱动注册成功\n");
	return 0;
}
static void __exit key_exit(void)
{
	free_irq(key_dev.irq,&key_dev);
	printk("驱动卸载成功\n");
}
module_init(key_init);
module_exit(key_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


