外部中断使用主要为以下几个步骤：
--------------------------------------------------------------------------------
1、获取中断号int gpio_to_irq(unsigned int gpio)
--------------------------------------------------------------------------------
2、注册中断int __must_check request_irq(unsigned int irq, 
										irq_handler_t handler, 
										unsigned long flags,
										const char *name, 
										void *dev)
										
				参数介绍：irq     中断号
						  handler 中断服务函数
						  flags   中断的标志
						  name    中断的名字
						  dev     一般为数据结构体
--------------------------------------------------------------------------------
3、中断服务函数 irqreturn_t (*irq_handler_t)(int, void *);
	函数返回值：
			/**
			 * enum irqreturn
			 * @IRQ_NONE		interrupt was not from this device
			 * @IRQ_HANDLED		interrupt was handled by this device
			 * @IRQ_WAKE_THREAD	handler requests to wake the handler thread
			 */
			enum irqreturn {
				IRQ_NONE		= (0 << 0),//用于共享中断，不是该设备时返回
				IRQ_HANDLED		= (1 << 0),//正常调用退出时返回
				IRQ_WAKE_THREAD		= (1 << 1),
			};
--------------------------------------------------------------------------------
4、释放中断线
void free_irq(unsigned int irq, void *dev_id)
	 void *dev_id就是注册中断线的最后一个参数
--------------------------------------------------------------------------------

















