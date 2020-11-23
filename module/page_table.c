#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/slab.h>

static unsigned long total_pages = (1ULL<<45);

static int pid = -1;
module_param(pid, int, S_IRUGO);



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
};

struct miscdevice page_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "page_table",
    .fops = &page_fops,
};

static int __init page_init(void)
{
    int error;
	if(pid == -1){
		pr_err("must pass paramater as pid=<pid>");
		return -1;
	}
	pr_info("total_pages: %lu\n", total_pages);
	
    error = misc_register(&page_device);
    if (error) {
        pr_err("can't misc_register :(\n");
        return error;
    }

    pr_info("page table Device registered\n");
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

