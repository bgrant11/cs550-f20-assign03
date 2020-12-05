#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>



#include "module/page_table.h"

unsigned long translate_va(int fd, unsigned long va){
	unsigned long addr = va;	
	if (ioctl(fd, IOCTL_GET_PFN, &addr) == -1){
		perror("Failed to invoke ioctl to translate va\n");
	}
	return addr;

}

void print_translation(unsigned long va, unsigned long pa){
	if(pa == NO_FRAME){
		//printf("%lu ---> NO_FRAME\n", va);
		printf("%lX ---> NO_FRAME\n", va);
	} else {
		//printf("%lu ---> %lu\n", va, pa);
		printf("%lX ---> %lX\n", va, pa);
	}
	printf("\n");
}

void get_input(int fd){
	unsigned long in_addr;
	unsigned long phys_addr;
	char input[100];	
	char *endpoint;	
		
	printf("Enter virtual page number: ");
	//scanf("%lX", &in_addr);
	scanf("%s", input);
	getchar(); //why is this needed?
	while(!strcmp(input, "exit")){
		//printf("in_addr: %lu\n", in_addr);	
		in_addr = strtoul(input, &endpoint, 16);		
		printf("in_addr: %lX\n", in_addr);
		phys_addr = translate_va(fd, in_addr); 
		print_translation(in_addr, phys_addr);
	
		printf("Enter virtual page number: ");
		//scanf("%lX", &in_addr);
		scanf("%s", input);
		getchar(); //why is this needed?
	}

}

int main(int argc, char *argv[]){
	int fd; 
	if( ( fd = open("/dev/page_table", O_RDWR)) < 0) {
		printf("Error opening /dev/process_list: %d\n", fd);
		return -1;
	}
	
	get_input(fd);	
	/*	
	printf("Enter virtual page number: ");
	//scanf("%lX", &in_addr);
	scanf("%s", &input);
	getchar(); //why is this needed?
	while(!strcmp(input, "exit"){
		//printf("in_addr: %lu\n", in_addr);	
		in_addr = strtoul(input, &endpoint, 16);		
		printf("in_addr: %lX\n", in_addr);
		phys_addr = translate_va(fd, in_addr); 
		print_translation(in_addr, phys_addr);
	
		printf("Enter virtual page number: ");
		//scanf("%lX", &in_addr);
		scanf("%s", &input);
		getchar(); //why is this needed?
	}
	*/
	close(fd);
	return 0;
}
