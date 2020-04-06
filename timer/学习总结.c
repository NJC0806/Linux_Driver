内核定时器就是当时间到达超时时间后，则会执行超时处理函数。
如果想定时器不断进入超时处理函数，则需要在超时处理函数中
从新修改超时时间。
使用内核定时器的步骤
1、编写超时处理函数
static void beep_timer_function(unsigned long data)
2、给内核定时器赋值
beep_timer.expires=jiffies+ msecs_to_jiffies(1000); 
beep_timer.function=beep_timer_function;
beep_timer.data=0;//传递给定时器处理函数的参数
3、初始化定时器
init_timer(&beep_timer);
4、开启定时器
add_timer(&beep_timer);
5、删除定时器
del_timer(&beep_timer);