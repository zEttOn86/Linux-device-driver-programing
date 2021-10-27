#include <linux/module.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <asm/current.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");

static void hook_tty_console(char *msg)
{
//    struct signal_struct *sig;
   struct tty_struct *tty;
    // https://stackoverflow.com/questions/20719713/how-can-i-write-to-tty-from-a-kernel-module
    // tty = current->signal->tty;
    // tty = container_of(sig, struct signal_struct, tty);
    tty = get_current_tty();
    if(tty != NULL){
        ((tty->driver->ops)->write)(tty, msg, strlen(msg));
        ((tty->driver->ops)->write)(tty, "\r\n", 2);
    }
}

static int sample_init(void)
{
    printk("driver loaded \n");

    hook_tty_console("This message is written by sample driver");

    return 0;
}

static void sample_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);