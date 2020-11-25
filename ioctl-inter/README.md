Credits:https://www.opensourceforu.com/2011/08/io-control-in-linux/


# IOCTL-Interface
Input/Output Control (ioctl, in short) is a common operation, or system call, available in most driver categories. It is a one-bill-fits-all kind of system call. If there is no other system call that meets a particular requirement, then ioctl() is the one to use.

Practical examples include volume control for an audio device, display configuration for a video device, reading device registers, and so on — basically, anything to do with device input/output, or device-specific operations, yet versatile enough for any kind of operation (for example, for debugging a driver by querying driver data structures).

The question is: how can all this be achieved by a single function prototype? The trick lies in using its two key parameters: command and argument. The command is a number representing an operation. The argument command is the corresponding parameter for the operation. The ioctl() function implementation does a switch … case over the commmand to implement the corresponding functionality. The following has been its prototype in the Linux kernel for quite some time:

int ioctl(struct inode *i, struct file *f, unsigned int cmd, unsigned long arg);
However, from kernel 2.6.35, it changed to:

long ioctl(struct file *f, unsigned int cmd, unsigned long arg);
If there is a need for more arguments, all of them are put in a structure, and a pointer to the structure becomes the ‘one’ command argument. Whether integer or pointer, the argument is taken as a long integer in kernel-space, and accordingly type-cast and processed.

ioctl() is typically implemented as part of the corresponding driver, and then an appropriate function pointer is initialised with it, exactly as in other system calls like open(), read(), etc. For example, in character drivers, it is the ioctl or unlocked_ioctl (since kernel 2.6.35) function pointer field in the struct file_operations that is to be initialised.

Again, like other system calls, it can be equivalently invoked from user-space using the ioctl() system call, prototyped in <sys/ioctl.h> as:

int ioctl(int fd, int cmd, ...);
Here, cmd is the same as what is implemented in the driver’s ioctl(), and the variable argument construct (...) is a hack to be able to pass any type of argument (though only one) to the driver’s ioctl(). Other parameters will be ignored.

Note that both the command and command argument type definitions need to be shared across the driver (in kernel-space) and the application (in user-space). Thus, these definitions are commonly put into header files for each space.

Querying driver-internal variables
To better understand the boring theory explained above, here’s the code set for the “debugging a driver” example mentioned earlier. This driver has three static global variables: status, dignity, and ego, which need to be queried and possibly operated from an application. The header file query_ioctl.h defines the corresponding commands and command argument type. query_ioctl.c is where the ioctl interfaces are implemented in the device driver. query_app.c expolits the device driver functionalities using ioctl system call. 
