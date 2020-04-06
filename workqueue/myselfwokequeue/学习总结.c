通过创建自己的工作队列调度工作函数
1、创建自己的工作队列
struct workqueue_struct *my_work_queue;
my_work_queue=create_workqueue("key_dev");
2、创建工作
struct work_struct key_work;
3、初始化工作队列
INIT_WORK(&key_dev.key_work,key_work_function);
4、调度工作
queue_work(key_dev.my_work_queue,&key_dev.key_work);
5、注销工作队列
destroy_workqueue (key_dev.my_work_queue);


总结：
Linux内核共享工作队列和自己创建的工作队列的区别在于共享工作队列是每个人都可以使用的，
工作队列已经创建好了，只需要初始化即可。而自己的工作队列，需要自己创建工作队列再初始
化。
