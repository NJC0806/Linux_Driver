�ں˶�ʱ�����ǵ�ʱ�䵽�ﳬʱʱ������ִ�г�ʱ��������
����붨ʱ�����Ͻ��볬ʱ������������Ҫ�ڳ�ʱ��������
�����޸ĳ�ʱʱ�䡣
ʹ���ں˶�ʱ���Ĳ���
1����д��ʱ������
static void beep_timer_function(unsigned long data)
2�����ں˶�ʱ����ֵ
beep_timer.expires=jiffies+ msecs_to_jiffies(1000); 
beep_timer.function=beep_timer_function;
beep_timer.data=0;//���ݸ���ʱ���������Ĳ���
3����ʼ����ʱ��
init_timer(&beep_timer);
4��������ʱ��
add_timer(&beep_timer);
5��ɾ����ʱ��
del_timer(&beep_timer);