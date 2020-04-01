#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/interrupt.h>
/*按键设备信息*/
struct key_info
{
	int gpio;
	int key_val;
	int flag;
	char name[10];
	int irq;
};

/*初始化按键信息*/
static struct key_info key_dev[]=
{
	{EXYNOS4_GPX3(2),0x1,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key1"},
	{EXYNOS4_GPX3(3),0x2,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key2"},
	{EXYNOS4_GPX3(4),0x3,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key3"},
	{EXYNOS4_GPX3(5),0x4,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key4"}
};
irqreturn_t key_irq_handler(int irq, void *dev_id)
{
	struct key_info *p=(struct key_info *)dev_id;
     if(gpio_get_value(p->gpio)){
     	printk("0x%x\n",p->key_val);
     }
	 else{
	 	printk("无按键\n");
	 }
	 return IRQ_HANDLED;	 
}
static int __init key_init(void) 
{
	int i=0,ret;
	for(i=0;i<4;i++)
	{
		key_dev[i].irq=gpio_to_irq(key_dev[i].gpio);
		if(request_irq(key_dev[i].irq, key_irq_handler, key_dev[i].flag, key_dev[i].name,&key_dev[i]))
		{
			printk("中断注册失败\n");
		}
	}
	printk("key驱动安装成功\n");
	return 0;
}
static void __exit key_exit(void) 
{
	int i; 
	for(i=0;i<4;i++)
	{
		free_irq(key_dev[i].irq,&key_dev[i]);
	}
	printk("key驱动卸载成功\n");
}
module_init(key_init);
module_exit(key_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");