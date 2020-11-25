#include "module/page_table.h"

unsigned long translate_va(int fd, unsigned long va){
	unsigned long addr = va;	
	if (ioctl(fd, IOCTL_GET_PFN, &addr) == -1){
		perror("Failed to invoke ioctl to translate va\n");
	}
	return addr;

}

void print_translation(unsigned long va, unsigned long pa){
	if(addr == NO_FRAME){
		printf("%lu ---> NO_FRAME\n", va);
	} else {
		printf("%lu ---> %lu\n", va, addr);
	}
}

int main(int argc, char *argv[]){
	unsigned long in_addr;
	unsigned long phys_addr;
	int fd; 
	if( ( fd = open("/dev/page_table", O_RDWR)) < 0) {
		printf("Error opening /dev/process_list: %d\n", fd);
		return -1;
	}
	printf("Enter virtual address: ");
	scanf("%lu", &in_addr);
	getchar(); //why is this needed?
	phys_addr = translate_va(fd, in_addr); 
	print_translation(in_addr, phys_addr);

	return 0;
}