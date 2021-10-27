#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME ("devone")

static int devone_devs = 1; /* device count */
static int devone_major = 0; /* dynamic aloocation */
static int devone_minor = 0; 
static struct cdev devone_cdev;
static struct class *devone_class = NULL;
static dev_t devone_dev;

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    int i;
    unsigned char val = 0xFF;
    int retval;

    for(i =0; i<count; i++){
        if(copy_to_user(&buf[i], &val, 1)){
            retval = -EFAULT;
            goto out;
        }
    }

    retval = count;
out:
    return retval;
}

struct file_operations devone_fops = {
    .read = devone_read,
};

static int devone_init(void)
{
    dev_t dev = MKDEV(devone_major, 0);
    int alloc_ret = 0;
    int major;
    int cdev_err = 0;
    struct device *class_dev = NULL;

    alloc_ret = alloc_chrdev_region(&dev, 0, devone_devs, DRIVER_NAME);
    if(alloc_ret)
        goto error;
    devone_major = major = MAJOR(dev);

    cdev_init(&devone_cdev, &devone_fops);
    devone_cdev.owner = THIS_MODULE;
    devone_cdev.ops = &devone_fops;
    cdev_err = cdev_add(&devone_cdev, MKDEV(devone_major, devone_minor), devone_devs);
    if(cdev_err)
        goto error;
    
    /* Register class */
    devone_class = class_create(THIS_MODULE, "devone");
    if(IS_ERR(devone_class))
        goto error;
    devone_dev = MKDEV(devone_major, devone_minor);
    class_dev = device_create(devone_class, NULL, devone_dev, NULL, "devone%d", devone_minor);

    printk(KERN_ALERT "%s driver(major %d) installed\n", DRIVER_NAME, major);

    return 0;

error:
    if(cdev_err == 0)
        cdev_del(&devone_cdev);
    
    if(alloc_ret == 0)
        unregister_chrdev_region(dev, devone_devs);

    return -1;
}

static void devone_exit(void)
{
    dev_t dev = MKDEV(devone_major, 0);

    /* unregister class */
    device_destroy(devone_class, devone_dev);
    class_destroy(devone_class);

    cdev_del(&devone_cdev);
    unregister_chrdev_region(dev, devone_devs);

    printk("%s driver remove\n", DRIVER_NAME);
}

module_init(devone_init);
module_exit(devone_exit);