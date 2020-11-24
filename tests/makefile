

all: memory_intensive computation_intensive

memory_intensive: memory_intensive.c
	gcc -o memory_intensive memory_intensive.c 

computation_intensive: computation_intensive.c
	gcc -o computation_intensive computation_intensive.c -pthread

memrun: memory_intensive
	./memory_intensive &

comprun: computation_intensive
	./computation_intensive &

bothrun: memrun comprun

clean:
	rm -f memory_intensive computation_intensive
