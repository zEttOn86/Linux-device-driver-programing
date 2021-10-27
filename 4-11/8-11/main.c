#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
MODULE_LICENSE("Dual BSD/GPL");


#define TIMEOUT_VALUE (5*HZ)

static struct timer_list tickfn;

static void sample_timeout(struct timer_list *t)
{
    struct timer_list *ptr = t;
    void *memptr;

    printk("ptr %p (%s)\n", ptr, __func__);

    memptr = kmalloc(1024 * 1024, GFP_KERNEL);
    if(ptr){
        printk("memptr %p\n", memptr);
        kfree(memptr);
    }
}

static int sample_init(void)
{
    printk("sample driver installed: %p\n", &tickfn);

    timer_setup(&tickfn, sample_timeout, 0);
    tickfn.expires = jiffies + TIMEOUT_VALUE;
    add_timer(&tickfn);

    return 0;
}

static void sample_exit(void)
{
    int ret;

    ret = del_timer_sync(&tickfn);

    printk("sample driver removed\n");
}

module_init(sample_init);
module_exit(sample_exit);