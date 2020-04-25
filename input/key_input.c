#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/input.h>
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
struct work_struct key_work;
struct key_info *p=NULL;
struct input_dev * key_inut_dev;
/*��ʼ��������Ϣ*/
static struct key_info key_dev[]=
{
	{EXYNOS4_GPX3(2),KEY_L,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key1"},
	{EXYNOS4_GPX3(3),KEY_S,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key2"},
	{EXYNOS4_GPX3(4),KEY_ENTER,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key3"},
	{EXYNOS4_GPX3(5),KEY_BACKSPACE,IRQF_TRIGGER_FALLING|IRQF_TRIGGER_RISING,"key4"}
};
static irqreturn_t key_irq_handler_t(int irq, void *argv)
{
	p=(struct key_info *)argv;
	schedule_work(&key_work);
	return IRQ_HANDLED;
}
static void key_work_fn(struct work_struct *key_work)
{
	//�͵�ƽ���£��ߵ�ƽ�ɿ�
	if(!gpio_get_value(p->gpio)){
	     input_report_key(key_inut_dev,p->key_val, 1);
	 }
	else 
	{
		input_report_key(key_inut_dev,p->key_val, 0);
	}
	input_sync(key_inut_dev);//ֻ��ͬ���˲������ϱ��ɹ�
}

static int __init key_drv_init(void){
	int count;
	for(count=0;count<4;count++){
		key_dev[count].irq=gpio_to_irq(key_dev[count].gpio);
		if(request_irq(key_dev[count].irq,key_irq_handler_t, key_dev[count].flag,key_dev[count].name, &key_dev[count])){
			printk("�ж�����ʧ��\n");
		}
	}
	INIT_WORK(&key_work,key_work_fn);
	/*��̬����input_dev�ṹ��*/
	key_inut_dev=input_allocate_device();
	/*�����ϱ�����*/
	input_set_capability(key_inut_dev,EV_KEY,KEY_L);
	input_set_capability(key_inut_dev,EV_KEY,KEY_S);
	input_set_capability(key_inut_dev,EV_KEY,KEY_ENTER);
	input_set_capability(key_inut_dev,EV_KEY,KEY_BACKSPACE);
	__set_bit(EV_REP, key_inut_dev->evbit);//�ϱ��ظ��¼�
	/*ע��������ϵͳ*/
	if(input_register_device(key_inut_dev)<0){
		printk("������ϵͳע��ʧ��\n");
	}
	printk("������װ�ɹ�\n");
	return 0;
}
static void __exit key_drv_exit(void) {
	int count;
	for(count=0;count<4;count++){
		free_irq(key_dev[count].irq,&key_dev[count]);
	}
	input_free_device(key_inut_dev);
	input_unregister_device(key_inut_dev);
	printk("����ж�سɹ�\n");
}
module_init(key_drv_init);
module_exit(key_drv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");














