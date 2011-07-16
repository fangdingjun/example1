#include <linux/module.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("GPL");
unsigned char *pagemem;
unsigned char *kmallocmem;
unsigned char *vmallocmem;

int __init mem_module_init(void)
{
    pagemem = (unsigned char*)__get_free_page(0);
    printk(KERN_INFO "<1>pagemem addr=%#x\n", pagemem);

    kmallocmem = (unsigned char*)kmalloc(100, 0);
    printk(KERN_INFO "<1>kmallocmem addr=%#x\n", kmallocmem);

    vmallocmem = (unsigned char*)vmalloc(1000000);
    printk(KERN_INFO "<1>vmallocmem addr=%#x\n", vmallocmem);

    return 0;
}

void __exit mem_module_exit(void)
{
    free_page(pagemem);
    kfree(kmallocmem);
    vfree(vmallocmem);
    printk(KERN_INFO "mem module unloaded ,free memory\n");
}

module_init(mem_module_init);
module_exit(mem_module_exit);
