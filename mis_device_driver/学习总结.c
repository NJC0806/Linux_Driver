1、申请IO，第一个为IO口，第二个为参数，一般写名字
	int gpio_request(unsigned gpio, const char *tag)
2、配置IO口模式，第一个参数为IO口，第二个为模式(如下)
	int s3c_gpio_cfgpin(unsigned int pin, unsigned int config)
	/* Defines for generic pin configurations */
	#define S3C_GPIO_INPUT	(S3C_GPIO_SPECIAL(0))
	#define S3C_GPIO_OUTPUT	(S3C_GPIO_SPECIAL(1))
	#define S3C_GPIO_SFN(x)	(S3C_GPIO_SPECIAL(x))
3、设置IO口值 
	void gpio_set_value(unsigned gpio, int value)
4、获取IO口值
	int gpio_get_value(unsigned int gpio)
5、IO口转换为对应的中断编号
	int gpio_to_irq(unsigned int gpio)