#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
    volatile int n = 0;

    printk(KERN_ALERT "driver loaded\n");
    n++;
    printk("n %d\n", n);
    
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
