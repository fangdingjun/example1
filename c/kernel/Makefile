ifneq ($(KERNELRELEASE),)
	obj-m += hello.o
	obj-m += mem.o
	obj-m += kern_hack.o
else
	build=/lib/modules/$(shell uname -r)/build
default:
	$(MAKE) -C $(build) M=$(shell pwd) modules
clean:
	$(MAKE) -C $(build) M=$(shell pwd) clean
install:
	$(MAKE) -C $(build) M=$(shell pwd) modules_install
endif
