obj-m += led_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# To load the module easily after building
install:
	sudo insmod led_driver.ko

# To remove the module easily
uninstall:
	sudo rmmod led_driver
