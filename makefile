
MOD := module
TST := tests


all: buildtests mod user_app

mod:
	make -C $(MOD) all

cleanmod:
	make -C $(MOD) clean

#inmod:
#	make -C $(MOD) inm

#   sudo insmod module/page_table.ko process_ID=

# cat /proc/PID/smaps

outmod:
	make -C $(MOD) outm





user_app: user_app.c
	gcc -o user_app user_app.c

usertest: user_app
	sudo ./user_app

cleanuser:
	rm -f user_app

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


bothtest: memtest comptest cleanuser
	#make -C $(TST) bothrun
	ps

cleanall: cleanmod cleantests cleanuser
