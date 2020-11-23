
MOD := module


mod:
	make -C $(MOD) all

cleanmod:
	make -C $(MOD) clean

inmod:
	make -C $(MOD) inm

outmod:
	make -C $(MOD) outm

