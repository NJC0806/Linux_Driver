输入子系统的使用步骤

1、动态分配input_dev结构体
	key_inut_dev=input_allocate_device();
2、设置上报类型
	input_set_capability(key_inut_dev,EV_KEY,KEY_L);
	input_set_capability(key_inut_dev,EV_KEY,KEY_S);
	input_set_capability(key_inut_dev,EV_KEY,KEY_ENTER);
	input_set_capability(key_inut_dev,EV_KEY,KEY_BACKSPACE);
	__set_bit(EV_REP, key_inut_dev->evbit);//上报重复事件
3、注册输入子系统
	input_register_device(key_inut_dev)
4、上报到输入设备结构体中
	input_report_key();
5、上报给应用层
	input_sync();
	
	
	
	