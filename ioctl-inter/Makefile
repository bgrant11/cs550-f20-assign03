# Simple Makefile to build a simple misc driver
# Nick Glynn <Nick.Glynn@feabhas.com>
#

obj-m += query_ioctl.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

CC := $(CROSS_COMPILE)gcc

all:
	$(MAKE) -C $(KDIR) M=${shell pwd} modules
        
clean:
	-$(MAKE) -C $(KDIR) M=${shell pwd} clean || true
	-rm *.o *.ko *.mod.{c,o} modules.order Module.symvers || true
	rm -f query_app

app: query_app.c
	gcc -o query_app query_app.c


