CONFIG_MODULE_SIG=n
obj-m += page_table.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

CC := $(CROSS_COMPILE)gcc

all:
	$(MAKE) -C $(KDIR) M=${shell pwd} modules
        
clean:
	-$(MAKE) -C $(KDIR) M=${shell pwd} clean || true
	-rm *.o *.ko *.mod.{c,o} modules.order Module.symvers || true

inm:
	sudo insmod page_table.ko pid=1 

outm:
	sudo rmmod page_table

#Username: bgrant11    
#IP: 128.226.28.59
#Password: NWKqjEi73

#/home/bgrant11/cs550-f20-assign03

#//home/work/cs/20fall/550/cs550-f20-assign03


