KERNEL_ADDR=/home/NJC/work/linux-3.5kernel/linux-3.5
all:
	make -C $(KERNEL_ADDR) M=`pwd` modules
	mv *.ko /home/NJC/mnt
	make -C $(KERNEL_ADDR) M=`pwd` modules clean
obj-m+=key.o