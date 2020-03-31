## 时	  间：2020-3-31
## 作	  者：jcning
## 联系方式：1959289104@qq.com
KERNEL_ADDR=/home/NJC/work/linux-3.5kernel/linux-3.5
all: 
	make -C $(KERNEL_ADDR) M=`pwd` modules
	#表示-C是到Linux内核路径最顶上的makefile文件，
	#M=让该makefile在构造modules目标之前返回到模块源代码路径
	cp *.ko /home/NJC/mnt
	make -C $(KERNEL_ADDR) M=`pwd` modules clean
	arm-linux-gcc app.c -o app
	mv app /home/NJC/mnt
obj-m +=beep.o