KERNEL_ADDR=/home/NJC/work/linux-3.5kernel/linux-3.5
all:
	make -C $(KERNEL_ADDR) M=`pwd` modules
	mv *.ko /home/NJC/mnt
	make -C $(KERNEL_ADDR) M=`pwd` modules clean
	arm-linux-gcc app.c -o app
	mv app /home/NJC/mnt
obj-m+=key_input.o