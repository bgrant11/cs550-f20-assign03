
MOD := module
TST := tests


all: buildtests mod

mod:
	make -C $(MOD) all

cleanmod:
	make -C $(MOD) clean

#inmod:
#	make -C $(MOD) inm

#   sudo insmod page_table.ko process_ID= 

outmod:
	make -C $(MOD) outm



buildtests:
	make -C $(TST)

cleantests:
	make -C $(TST) clean

memtest:
	#make -C $(TST) memrun
	tests/memory_intensive &


comptest:
	#make -C $(TST) comprun
	tests/computation_intensive &


bothtest: memtest comptest
	#make -C $(TST) bothrun
	ps

cleanall: cleanmod cleantests
