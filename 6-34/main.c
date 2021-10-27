#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
 #include <linux/uaccess.h>
MODULE_LICENSE("Dual BSD/GPL");

#define PROCNAME "driver/sample"

#define DUMMY_BUFSIZ 4096
static char dummy[DUMMY_BUFSIZ];

static ssize_t sample_read_proc(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    int len;
    // printk("page=%p *start=%p off=%d count=%d *eof=%d data=%p\n", page, *start, (int)off, count, *eof, data);

    len = count;
    if(len > PAGE_SIZE)
        return -ENOBUFS;
    
    copy_to_user(dummy, buf, count);
    // memcpy(page, dummy, len);
    // *eof = 1;

    printk("len=%d (%s)\n", len, __func__);
    return len;
}

static struct file_operations proc_fops = {
    .read = sample_read_proc,
};

static int sample_init(void)
{
    struct proc_dir_entry *entry;
    int i;

    /* add /proc */
    entry = proc_create(PROCNAME, S_IRUGO | S_IWUGO, NULL, &proc_fops);
    if(entry == NULL) {
        printk(KERN_WARNING "sample: unable to create /proc entry\n");
    }

    for(i = 0; i < DUMMY_BUFSIZ; i++) {
        dummy[i] = 'A' + (i % 26);
    }

    printk("driver loaded\n");
    return 0;
}

static void sample_exit(void)
{
    remove_proc_entry(PROCNAME, NULL);
    printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);
