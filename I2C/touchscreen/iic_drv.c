#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/workqueue.h>

static struct work_struct work;
static  struct i2c_client *client_drv;
static const struct i2c_device_id i2c_id[] =
{
	{"FT5X06",0},//�豸�˵�����Ϊ"myiic",0��ʾ����Ҫ˽������
	{}
};


//�������д�����
static void work_func(struct work_struct *work)
{
	s32 x=0,y=0,num=0;
	
	/*1. �������µĵ�����*/
	num=i2c_smbus_read_byte_data(client_drv,0x02)&0x0f;
	
	/*2. ��ȡX����*/
	x=(i2c_smbus_read_byte_data(client_drv,0x03)&0x0f)<<8; //��λ
	x|=i2c_smbus_read_byte_data(client_drv,0x04); //��λ

	/*3. ��ȡY����*/
	y=(i2c_smbus_read_byte_data(client_drv,0x05)&0x0f)<<8; //��λ
	y|=i2c_smbus_read_byte_data(client_drv,0x06); //��λ

	printk("num=%d,x=%d,y=%d\n",num,x,y);	
}



//�жϷ�����
static irqreturn_t irq_handler(int irq, void *dev)
{
	schedule_work(&work); 
	return IRQ_NONE;
}


static int i2c_probe(struct i2c_client *client, const struct i2c_device_id *device_id)//ƥ��ɹ�ʱ����
{	
    client_drv=client;
	printk("i2c_probe!!!\n");
	printk("������IICƥ��ĵ�ַ=0x%x\n",client->addr);
	
    /*ע�ᴥ�������ж�*/
    if(request_irq(client->irq,irq_handler,IRQ_TYPE_EDGE_BOTH,client->name,NULL)!=0)
	{
        printk("�ж�ע��ʧ��!\n");
	}

	/*��ʼ������*/
	INIT_WORK(&work,work_func);
    return 0;
}


static int i2c_remove(struct i2c_client *client)
{
	printk("i2c_remove!!!\n");
	//ע���ж�
	free_irq(client->irq,NULL);
	return 0;
}

struct i2c_driver i2c_drv =
{
	.driver = //�������ӻᱨ��ʵ����û����
	{
		.name = "XL",
		.owner = THIS_MODULE,
	},	
	.probe = i2c_probe,  //̽�⺯��
	.remove = i2c_remove, //��Դж��
	.id_table = i2c_id,  //������һ�����ֵĲ�������ƥ���豸������
};


/*iic������*/
static int __init i2c_drv_init(void)
{
	i2c_add_driver(&i2c_drv);//��iic����ע��һ������
	return 0;
}

static void __exit i2c_drv_exit(void)//ƽ̨�豸�˵ĳ��ں���
{
	i2c_del_driver(&i2c_drv);
}

module_init(i2c_drv_init);
module_exit(i2c_drv_exit);
MODULE_LICENSE("GPL");


