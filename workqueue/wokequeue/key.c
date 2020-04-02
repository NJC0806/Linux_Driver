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
/*�����豸��Ϣ*/
struct key_info
{
	int gpio;
	int key_val;
	int flag;
	char name[10];
	int irq;
	struct work_struct key_work;//�����һ������
};

/*��ʼ��������Ϣ*/
static struct key_info key_dev=
{
	.gpio=EXYNOS4_GPX3(2),
	.key_val=0x5,
	.flag=IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,
	.name="key1",
};
static void key_work_function(struct work_struct *work)//������INITʱ�����
{
	struct key_info *p=container_of(work,struct key_info,key_work);
	//ͨ�������������������ܵĽṹ���У�ͨ�������ṹ����Ի���ܵĽṹ����׵�ַ
	if(gpio_get_value(p->gpio))
	{
		printk("����\n");
	}
	else
	{
		printk("�ɿ�\n");
	}
}
irqreturn_t key_irq_handler(int irq, void *dev)
{
	struct key_info *p=(struct key_info *)dev;
	printk("�����жϣ���ʼ����key_work\n");
	schedule_work(&p->key_work);
	return IRQ_HANDLED;
}
static int __init key_init(void)
{
	INIT_WORK(&key_dev.key_work, key_work_function);
	key_dev.irq=gpio_to_irq(key_dev.gpio);
	if(request_irq(key_dev.irq,key_irq_handler,key_dev.flag,key_dev.name,&key_dev))
	{
		printk("�ж�ע��ʧ��\n");
	}
	printk("����ע��ɹ�\n");
	return 0;
}
static void __exit key_exit(void)
{
	free_irq(key_dev.irq,&key_dev);
	printk("����ж�سɹ�\n");
}
module_init(key_init);
module_exit(key_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


