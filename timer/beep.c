#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
struct timer_list beep_timer;
static void beep_timer_function(unsigned long data)
{
	static int flag=1;
	printk("��ʱʱ�䵽\n");
	gpio_set_value(EXYNOS4_GPD0(0),flag);
	flag=!flag;
	mod_timer(&beep_timer, jiffies+ msecs_to_jiffies(1000)); //�޸Ķ�ʱ����ʱʱ��
}
static int __init beep_init(void) {
	gpio_request(EXYNOS4_GPD0(0),"BEEP");
	s3c_gpio_cfgpin(EXYNOS4_GPD0(0),S3C_GPIO_OUTPUT);
	gpio_set_value(EXYNOS4_GPD0(0),0);
	printk("beep������װ�ɹ�\n");
	beep_timer.expires=jiffies+ msecs_to_jiffies(1000); 
	beep_timer.function=beep_timer_function;
	beep_timer.data=0;//���ݸ���ʱ���������Ĳ���
	init_timer(&beep_timer);
	add_timer(&beep_timer);
	return 0;
}
static void __exit beep_exit(void){
	del_timer(&beep_timer);
	gpio_set_value(EXYNOS4_GPD0(0),0);
	gpio_free(EXYNOS4_GPD0(0));
	printk("beep����ж�سɹ�\n");
}

module_init(beep_init);
module_exit(beep_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jcning 1959289104@qq.com");


