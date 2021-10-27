#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");


static int devone_devs = 1; /* device count */
static int devone_major = 0; /* dynamic aloocation */
static struct cdev devone_cdev;

wait_queue_head_t yutaka_sample_wait;
EXPORT_SYMBOL(yutaka_sample_wait);

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    int i;
    unsigned char val = 0xFF;
    int retval;

    init_waitqueue_head(&yutaka_sample_wait);
    wait_event_timeout(yutaka_sample_wait, NULL, HZ*5);

    printk("Wakeup! (%s)\n", __func__);

    for(i = 0; i < count; i++) {
        if(copy_to_user(&buf[i], &val, 1)){
            retval = -EFAULT;
            goto out;
        }
    }
    retval = count;
out:
    return count;
}

struct file_operations devone_fops = {
    .read  = devone_read,
};

static int devone_init(void) 
{
    dev_t dev = MKDEV(devone_major, 0);
    int ret = 0;
    int major;
    int err = 0;

    ret = alloc_chrdev_region(&dev, 0, devone_devs, "devone");
    if(ret)
        return ret;
    
    devone_major = major = MAJOR(dev);

    cdev_init(&devone_cdev, &devone_fops);
    devone_cdev.owner = THIS_MODULE;
    devone_cdev.ops = &devone_fops;
    err = cdev_add(&devone_cdev, MKDEV(devone_major, 0), devone_devs);
    if(err)
        return err;

    printk(KERN_ALERT "devone driver(major %d) installed\n", major);

    return 0;

}

static void devone_exit(void)
{
    dev_t dev = MKDEV(devone_major, 0);

    cdev_del(&devone_cdev);
    unregister_chrdev_region(dev, devone_devs);

    printk(KERN_ALERT "devone driver remove.\n");
}

module_init(devone_init);
module_exit(devone_exit);