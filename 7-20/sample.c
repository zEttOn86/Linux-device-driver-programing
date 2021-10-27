#include <linux/module.h>
#include <linux/init.h>
#include <asm/io.h>

void do_asm(void)
{
    u16 cx = 0, dx = 0;
    u16 ax = 0x200;

    asm("int $0x1a"
            : "+a" (ax), "=c" (cx), "=d" (dx)
            : : "ebx", "esi", "edi");
        
    printk("ax %x cx %x dx %x\n", ax, cx, dx);
}