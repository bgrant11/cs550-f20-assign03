#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <linux/ioctl.h>

#define IOCTL_GET_PFN _IORW('p', 1, unsigned long)
#define MAX_VA 144115188075855871lu
#define NO_FRAME 18446744073709551615lu

#endif

