/**
 * @file   irqgen_cdev.c
 * @author Nicola Tuveri
 * @date   15 November 2018
 * @version 0.7
 * @target_device Xilinx PYNQ-Z1
 * @brief   A stub module to support the IRQ Generator IP block for the
 *          Real-Time System course (character device support).
 */

# include <linux/kernel.h>           // Contains types, macros, functions for the kernel

# include <linux/device.h>
# include <linux/string.h>

# include <linux/cdev.h>             // Header for character devices support
# include <linux/fs.h>               // Header for Linux file system support
# include <linux/uaccess.h>          // Header for userspace access support
#include <linux/spinlock.h>
# include "irqgen.h"                 // Shared module specific declarations

#define IRQGEN_CDEV_CLASS "irqgen-class"

struct irqgen_chardev {
    struct cdev cdev;
    dev_t devt;
    struct device *dev;
    struct class *class;
    // do we need a sync mechanism for any cdev operation?
    spinlock_t lock_char_device;
};

static struct irqgen_chardev irqgen_chardev;

// The prototype functions for the character driver -- must come before the struct definition
static int     irqgen_cdev_open(struct inode *, struct file *);
static int     irqgen_cdev_release(struct inode *, struct file *);
static ssize_t irqgen_cdev_read(struct file *, char *, size_t, loff_t *);

static struct file_operations fops = {
    .open = irqgen_cdev_open,
    .release = irqgen_cdev_release,
    .read = irqgen_cdev_read,
};

// Initialize the char device driver
int irqgen_cdev_setup(struct platform_device *pdev)
{
    int ret;
	printk(KERN_INFO "CHARDEV: irqgen_cdev_setup start\n"); 

    cdev_init(&irqgen_chardev.cdev, &fops);
    irqgen_chardev.cdev.owner = THIS_MODULE;
    irqgen_chardev.cdev.kobj.parent = &pdev->dev.kobj;

    // dynamically allocate a major and a minor for this chrdev
    // don't forget error handling
	 ret = alloc_chrdev_region(&irqgen_chardev.devt, 0, 1, DRIVER_NAME);
	 if(ret < 0)
	 {
		printk(KERN_ERR KMSG_PFX "CHARDEV: Cannot allocate major number for device\n");
		goto err_alloc_chrdev_region;
	 }

    // add to the system the cdev for the allocated (major,minor)
    // don't forget error handling
	ret = cdev_add( &irqgen_chardev.cdev,irqgen_chardev.devt,1);
	if(ret < 0 ) 
	{
		printk(KERN_ERR KMSG_PFX "CHARDEV: Unable to add cdev");
		goto err_cdev_add;
	}

    // Add an "irqgen" node in the /dev/ filesystem (hint: device_create())
    // don't forget error handling
        irqgen_chardev.class = class_create(THIS_MODULE,IRQGEN_CDEV_CLASS); 
	ret  = device_create(irqgen_chardev.class, NULL, irqgen_chardev.devt, NULL,DRIVER_NAME);
	if(ret == NULL)
	{
		printk(KERN_ERR KMSG_PFX "CHARDEV: Cannot create the device\n");
		goto err_device_create;
	}

    // do we need a sync mechanism for any cdev operation?
	spin_lock_init(&irqgen_chardev.lock_char_device);
    return 0;
	
		
    // use labels to handle errors and undo any resource allocation
	err_device_create:
		device_destroy(irqgen_chardev.class,irqgen_chardev.devt);
	err_cdev_add:
		cdev_del(&irqgen_chardev.cdev); 
	err_alloc_chrdev_region:
		unregister_chrdev_region(irqgen_chardev.devt, 1);
		
    return ret;
}

void irqgen_cdev_cleanup(struct platform_device *pdev)
{
    // destroy, unregister and free, in the right order, all resources
    // allocated in irqgen_cdev_setup()
    device_destroy (irqgen_chardev.class,irqgen_chardev.devt);
    cdev_del(&irqgen_chardev.cdev);
    unregister_chrdev_region(irqgen_chardev.devt, 1);
    printk(KERN_INFO "CHARDEV:irqgen_cdev_cleanup done\n"); 
}

static u8 already_opened = 0;

static int irqgen_cdev_open(struct inode *inode, struct file *f)
{
# ifdef DEBUG
    printk(KERN_DEBUG KMSG_PFX "irqgen_cdev_open() called.\n");
# endif
	spin_lock(&irqgen_chardev.lock_char_device);
    if (already_opened) {
	spin_unlock(&irqgen_chardev.lock_char_device);
        return -EBUSY;
    }
    already_opened = 1;
    spin_unlock(&irqgen_chardev.lock_char_device);

    return 0;
}

static int irqgen_cdev_release(struct inode *inode, struct file *f)
{
# ifdef DEBUG
    printk(KERN_DEBUG KMSG_PFX "irqgen_cdev_release() called.\n");
# endif
    spin_lock(&irqgen_chardev.lock_char_device);
    if (!already_opened) {
	    spin_unlock(&irqgen_chardev.lock_char_device);
        return -ECANCELED;
    }
    already_opened = 0;
    spin_unlock(&irqgen_chardev.lock_char_device);

    return 0;
}

// This will write in the userspace buffer one line at a time, the
// client (or the std library) will retry automatically.
//
// NOTE: We require the userland buffer to be at least 60 bytes (count>=60)
static ssize_t irqgen_cdev_read(struct file *fp, char *ubuf, size_t count, loff_t *f_pos)
{
    // We cannot write to user space directly: we need to use a buffer
    // in kernel space and then use specialized functions to copy the
    // data to provided the userland buffer.
#define KBUF_SIZE 100
    static char kbuf[KBUF_SIZE];
    ssize_t ret = 0;

    struct latency_data v;

    if (count < 60) {
        printk(KERN_ERR KMSG_PFX "read() buffer too small (<=60).\n");
        return -ENOBUFS;
    }

    // TODO: how to protect access to shared r/w members of irqgen_data?
	spin_lock(&irqgen_data->data_lock);
	
    if (irqgen_data->rp == irqgen_data->wp) {
        // Nothing to read
	spin_unlock(&irqgen_data->data_lock);
        return 0;
    }

    v = irqgen_data->latencies[irqgen_data->rp];
    irqgen_data->rp = (irqgen_data->rp + 1)%MAX_LATENCIES;
	spin_unlock(&irqgen_data->data_lock);
    ret = scnprintf(kbuf, KBUF_SIZE, "%u,%lu,%llu\n", v.line, v.latency, v.timestamp);
    if (ret < 0) {
        goto end;
    } else if (ret == 0) {
        ret = -ENOMEM;
        goto end;
    }

    // TODO: how to transfer from kernel space to user space?
    if(copy_to_user(ubuf,kbuf,KBUF_SIZE)!=0) goto end;
    *f_pos += ret;

 end:
    return ret;
#undef KBUF_SIZE
}

