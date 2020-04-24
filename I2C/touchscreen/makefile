KERNEL_ARR=/home/NJC/work/linux-3.5kernel/linux-3.5
all:
	make -C $(KERNEL_ARR) M=`pwd` modules
	cp *.ko /home/NJC/mnt
	make -C $(KERNEL_ARR) M=`pwd` modules clean 
obj-m +=touchscreen_device.o
obj-m +=touchscreen_drvier.o