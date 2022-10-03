/**
 * @file    hello-world.c
 * @author  Sai Prasad Samudrala
 * @date    03 October 2022
 * @version 0.1
 * @brief  An introductory "Hello World!" out of tree module that can display a message on console
 * The module can accept an argument when it is loaded -- the name, which appears in the kernel
 * log files.
*/

#include <linux/init.h>             
#include <linux/module.h>           
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
           
 
MODULE_LICENSE("GPL");              ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Sai Prasad Samudrala");      ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux driver for the getting parameter from user and display it.");  ///< The description -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module

static char *name = "blah";
module_param(name, charp, 0000);
MODULE_PARM_DESC(name, "A character string"); 
static int __init hello_init(void) 
{ 
    pr_info("Hello, world \n=============\n");
    printk(KERN_INFO "%s ,Welcome to Real Time Systems.\n", name); 
    return 0; 
} 

void __exit hello_exit(void)
{
	printk("Goodbye Cruel World!\n");
}

module_init(hello_init); 
module_exit(hello_exit);
