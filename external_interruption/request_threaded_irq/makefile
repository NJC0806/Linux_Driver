KERNAL_ADDR=/home/NJC/work/linux-3.5kernel/linux-3.5
all:
	make -C $(KERNAL_ADDR) M=`pwd` modules
	cp *ko /home/NJC/mnt
	make -C $(KERNAL_ADDR) M=`pwd` modules clean
obj-m+=key.o