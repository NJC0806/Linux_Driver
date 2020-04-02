
该中断注册带有一个线程，可以完成一个类似底部的效果。
-------------------------------------------------------------------------------
static inline int  request_threaded_irq(unsigned int irq, 
										irq_handler_t handler,
										irq_handler_t thread_fn,
										unsigned long flags, 
										const char *name, void *dev)
-------------------------------------------------------------------------------
1、获取中断号
	int gpio_to_irq(unsigned int gpio)
-------------------------------------------------------------------------------
2、注册中断			 
	static inline int  request_threaded_irq(unsigned int irq, 
										irq_handler_t handler,
										irq_handler_t thread_fn,
										unsigned long flags, 
										const char *name, void *dev)
-------------------------------------------------------------------------------
3、编写中断处理函数
	irqreturn_t (*irq_handler_t)(int, void *);
	放回值必须为
				IRQ_WAKE_THREAD
	用来唤醒中断线程
	
	注意：中断处理函数中只处理简单的事情和要求尽快处理的事情，
		  耗时的事情放到中断线程中去处理
-------------------------------------------------------------------------------
4、编写中断线程函数
	irqreturn_t (*irq_handler_t)(int, void *);
-------------------------------------------------------------------------------
5、释放中断线
void free_irq(unsigned int irq, void *dev_id)












										
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 