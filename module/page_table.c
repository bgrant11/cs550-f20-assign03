#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>
#include <linux/mm_types.h>
#include <linux/pgtable.h>

#include "page_table.h"



//static unsigned long total_pages = (1ULL<<45);

static int process_ID = -1;
module_param(process_ID, int, S_IRUGO);

struct pid *pid;
struct task_struct *pid_struct;
struct mm_struct *pid_mm_struct;

static void translate(void){
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	
	struct vm_area_struct *vma;
	unsigned long vaddr;
	unsigned long phys_address;	
	
	for(vma = pid_mm_struct->mmap; vma; vma = vma->vm_next){
		for(vaddr = vma->vm_start; vaddr < vma->vm_end; vaddr++){
			pgd = pgd_offset(pid_struct->mm, vaddr);
			p4d = p4d_offset(pgd, vaddr);
			pud = pud_offset(p4d, vaddr);
			pmd = pmd_offset(pud, vaddr);
			pte = pte_offset_map(pmd, vaddr);
			if(pte_present(*pte)){
				phys_address = pte_pfn(*pte);
				pr_info("%lu --> %lu\n", vaddr, phys_address);
			} else{ // this is here for a potential debug
				phys_address = NO_FRAME;
			}
		}
	}
}

static long ioctl_translate(long vaddr){
	//int err;	
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	
	//unsigned long vaddr;
	unsigned long phys_address;	

	pgd = pgd_offset(pid_struct->mm, vaddr);
	p4d = p4d_offset(pgd, vaddr);
	pud = pud_offset(p4d, vaddr);
	pmd = pmd_offset(pud, vaddr);
	pte = pte_offset_map(pmd, vaddr);
	if(pte_present(*pte)){
		phys_address = pte_pfn(*pte);
		//+pr_info("%lu --> %lu\n", vaddr, phys_address);
	} else{ // this is here for a potential debug
		phys_address = NO_FRAME;
	}
	return phys_address;
	
}

static void get_pid_structs(void){
	pid = find_get_pid (process_ID);
	pid_struct = pid_task(pid, PIDTYPE_PID);
	pid_mm_struct = pid_struct->mm;
}

static long page_ioctl(struct file *f, unsigned int cmd, unsigned long arg){
	int err;
	unsigned long paddr;
	if(arg > MAX_VA){
		pr_info("Virtual address is out of range");		
		return -EINVAL;
	}	
	switch (cmd){
		case IOCTL_GET_PFN:
			paddr = ioctl_translate(arg);
			err = copy_to_user((unsigned long*) 
								arg, 
								&paddr, 
								sizeof(unsigned long));
			if(err != 0){
				pr_info("Problem sending address to user, %d\n", err);
				return -EACCES;
			}
			break;
		default:
			pr_info("Invalid command");			
			return -EINVAL;

	}
	return 0;

}

static int page_open(struct inode *inode, struct file *file)
{    
	pr_info("Opening page table Device\n");
	pr_info("Opening page table Device end\n");	
	return 0;
}

static int page_close(struct inode *inodep, struct file *filp)
{
    pr_info("Closing page table Device\n");
    return 0;
}

static const struct file_operations page_fops = {
    .owner			= THIS_MODULE,
    .open			= page_open,
    .release		= page_close,
    .llseek 		= no_llseek,
	.unlocked_ioctl = page_ioctl,
};

struct miscdevice page_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "page_table",
    .fops = &page_fops,
};

static int __init page_init(void)
{
    int error;
	pr_info("initializing page table module\n");	
	if(process_ID == -1){
		pr_err("must pass paramater as process_ID=<pid>");
		return -1;
	}
	//pr_info("total_pages: %lu\n", total_pages);
	translate();
	
    error = misc_register(&page_device);
    if (error) {
        pr_err("can't misc_register :(\n");
        return error;
    }

    pr_info("page table module initialized\n");
    return 0;
}

static void __exit page_exit(void)
{
    misc_deregister(&page_device);
    pr_info("page table Device deregistered\n");
}

module_init(page_init)
module_exit(page_exit)

MODULE_DESCRIPTION("pageess table Device");
MODULE_AUTHOR("Brian Grant");
MODULE_LICENSE("GPL");

