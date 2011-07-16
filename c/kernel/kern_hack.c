/* 
 * license: GPL
 * author: fangdingjun@gmail.com
 * version: 0.1
 *
 * IMPORTANT:
 *      this is a test for replace system call for kernel version >= 2.6.24 on x86
 *      this code only for learning, DO NOT to use this code to do something else
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <asm/syscalls.h>
#include <linux/init.h>

/* idtr, 6 bytes */
struct {
    unsigned short limit;
    unsigned int base;
} __attribute__ ((packed)) idtr;

/* idt, 8 bytes */
struct {
    unsigned short off1;
    unsigned short sel;
    unsigned char none;
    unsigned char flags;
    unsigned short off2;
} __attribute__ ((packed)) idt;

/* save sys_call_table address */
static void **my_table;

asmlinkage long (*o_open) (const char *, int, int);
asmlinkage long (*get_uid) (void);
asmlinkage long (*m_getpid) (void);

static unsigned int get_cr0(void)
{
    unsigned int ch;
    asm("mov %%cr0,%0": "=r"(ch):);
    return ch;
}

static int set_cr0(unsigned int c)
{
    asm("mov %0,%%cr0": :"r"(c));
    return 0;
}

/* my sys_open */
asmlinkage long m_open(const char *filename, int flags, int mode)
{
    //printk("my open\n");
    char f_name[256];
    if (get_uid() == 1000) {
        if (copy_from_user(&f_name, filename, sizeof(filename)) == -1) {
            return -1;
        }
        printk("uid = 1000 pid = %ld open file %s\n", m_getpid(),
                filename);
    }

    /* invoke system's sys_open */
    return o_open(filename, flags, mode);
}

static int clear_protect(void)
{
    unsigned int flags;
    flags = get_cr0();
    if (flags & (1 << 16)) {
        flags &= ~(1 << 16);
        set_cr0(flags);
    }
    return 0;
}

static int enable_protect(void)
{
    unsigned int flags;
    flags = get_cr0();
    if (!(flags & (1 << 16))) {
        flags |= (1 << 16);
        set_cr0(flags);
    }
    return 0;
}

static int __init hack_init(void)
{
    unsigned int sys_call_off;
    unsigned int sys_call_table;

    char *p;
    int i;


    asm("sidt %0":"=m"(idtr));

    //printk("addr of idtr: %#x\n", (int) &idtr);

    memcpy(&idt, (void *) (idtr.base + 8 * 0x80), sizeof(idt));

    sys_call_off = ((idt.off2 << 16) | idt.off1);
    //printk("addr of idt 0x80: %#x\n", sys_call_off);

    p = (char *) sys_call_off;

    for (i = 0; i < 100; i++) {
        if (p[i] == '\xff' && p[i + 1] == '\x14' && p[i + 2] == '\x85') {
            /* sys_call_table found */
            sys_call_table = *(unsigned int *) (p + i + 3);
            printk("addr of sys_call_table: %#x\n", sys_call_table);
            goto out;
        }
    }
    /* sys_call_table not found */
    return -1;

out:
    printk("module init, replace sys_open\n");
    my_table = (void **) sys_call_table;

    /* old sys_open */
    o_open = my_table[__NR_open];

    clear_protect();
    /* replace */
    my_table[__NR_open] = m_open;

    enable_protect();
    get_uid = my_table[__NR_getuid];
    m_getpid = my_table[__NR_getpid];
    return 0;
}

static void __exit hack_exit(void)
{

    printk("modulde exit, restore sys_open\n");

    clear_protect();

    /* restore */
    my_table[__NR_open] = o_open;

    enable_protect();

    return;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fangdingjun@gmail.com");
MODULE_VERSION("0.1");
MODULE_DESCRIPTION("this is a test for replace system call for kernel version >=2.6.24");
MODULE_DESCRIPTION("this code only for learning, DO NOT to use this to do something else.");
module_init(hack_init);
module_exit(hack_exit);
