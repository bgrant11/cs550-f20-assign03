
MOD := module
TST := tests


all: buildtests mod user_app

mod:
	make -C $(MOD) all

cleanmod:
	make -C $(MOD) clean

inmod: module/page_table.ko
	sudo insmod module/page_table.ko process_ID=$(pid)

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
	$(TST)/memory_intensive &
	ps


comptest:
	$(TST)/computation_intensive &
	ps


bothtest: memtest comptest cleanuser

cleanall: cleanmod cleantests cleanuser

endall: cleanall outmod
	kill $(pid)
