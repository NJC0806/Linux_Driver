������ϵͳ��ʹ�ò���

1����̬����input_dev�ṹ��
	key_inut_dev=input_allocate_device();
2�������ϱ�����
	input_set_capability(key_inut_dev,EV_KEY,KEY_L);
	input_set_capability(key_inut_dev,EV_KEY,KEY_S);
	input_set_capability(key_inut_dev,EV_KEY,KEY_ENTER);
	input_set_capability(key_inut_dev,EV_KEY,KEY_BACKSPACE);
	__set_bit(EV_REP, key_inut_dev->evbit);//�ϱ��ظ��¼�
3��ע��������ϵͳ
	input_register_device(key_inut_dev)
4���ϱ��������豸�ṹ����
	input_report_key();
5���ϱ���Ӧ�ò�
	input_sync();
	
	
	
	