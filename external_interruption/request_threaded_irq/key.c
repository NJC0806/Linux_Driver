#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/interrupt.h>
/*�����豸��Ϣ*/
struct key_info
{
	int gpio;
	int key_val;
	int flag;
	char name[10];
	int irq;
};

/*��ʼ��������Ϣ*/
static struct key_info key_dev[]=
{
	{EXYNOS4_GPX3(2),0x5,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key1"},
	{EXYNOS4_GPX3(3),0x6,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key2"},
	{EXYNOS4_GPX3(4),0x7,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key3"},
	{EXYNOS4_GPX3(5),0x8,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key4"}
};
irqreturn_t key_thread_fn(int irq, void * dev_id)
{
	struct key_info *p=(struct key_info *)dev_id;
	if(gpio_get_value(p->gpio)){
		printk("0x%x����\n",p->key_val);
	}else{
		printk("0x%x�ɿ�\n",p->key_val);
	}
	return IRQ_HANDLED;
}
irqreturn_t key_irq_handler(int irq, void * dev_id)
{
	printk("�����ж�\n");
	return IRQ_WAKE_THREAD;//�����ж��߳�
}
static int __init key_init(void)
{
	int i=0;
	for(i=0;i<4;i++){
		key_dev[i].irq=gpio_to_irq(key_dev[i].gpio);
		if(request_threaded_irq(key_dev[i].irq,key_irq_handler,key_thread_fn,key_dev[i].flag,key_dev[i].name,&key_dev[i]))
		{
			printk("�ж�ע��ʧ��\n");
		}
		
	}
	printk("������װ�ɹ�\n");
	return 0;
}
static void __exit key_exit(void)
{
	int i=0;
	for(i=0;i<4;i++){
		free_irq(key_dev[i].irq,&key_dev);
	}
	printk("����ж�سɹ�\n");
}
module_init(key_init);
module_exit(key_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");