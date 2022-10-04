# Exercise 02 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
- To create the custom yocto layer and understand the difference between loadable kernel module and out of tree kernel module.
- In this exercise, I accomplished creating a hello-world layer.

## 2. What is a Yocto layer? What are the essential requirements to correctly define a new one?
- 

## 3. What priority did you assign to your layer? How and why?
- The priority of the layer is 6. It assigned the default priority by running the command `bitbake add layer`. 

## 4. What does LKM stand for (in the context of this exercise)? What does it mean and what are the characteristics of a LKM? What's the alternative?
- If you want to add code to a Linux kernel, the most basic way to do that is to add some source files to the kernel source tree and recompile the kernel. In fact, the kernel configuration process consists mainly of choosing which files to include in the kernel to be compiled.But you can also add code to the Linux kernel while it is running. A chunk of code that you add in this way is called a loadable kernel module.

## 5. What does Out-of-Tree Module mean? What's the alternative and what are the differences?

## 6. How did you define the module metadata? How does it work?

## 7. How is the module built? How does it get installed inside `core-image-minimal`?

## 8. What is the path for the `sysfs` entry for the module? List and explain its contents.

## 9. Feedback (what was difficult? what was easy? how would you improve it?)
- Initially, I felt difficult and after understanding the steps it was easy. Mention all instructions clearly in one place would be better.
