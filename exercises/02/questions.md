# Exercise 02 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
- To create the custom yocto layer and understand the difference between loadable kernel module and out of tree kernel module.
- In this exercise, I accomplished creating a hello-world layer.

## 2. What is a Yocto layer? What are the essential requirements to correctly define a new one?
-  It is a development model for embedded and IoT Linux creation that distinguishes the Yocto Project from other simple build systems. Layers are repositories that contain related sets of instructions that tell the OpenEmbedded Build System what to do. Users can collaborate, share, and reuse layers.
- It has to contain a `conf/layer.conf` file inside of which metadata like the priority, path, and the included BitBake files must be specified.

## 3. What priority did you assign to your layer? How and why?
- The priority of the layer is 6. It assigned the default priority by running the command `bitbake add layer`. This was done by setting the `BBFILE_PRIORITY_meta-group13` variable inside the layer configuration.

## 4. What does LKM stand for (in the context of this exercise)? What does it mean and what are the characteristics of a LKM? What's the alternative?
- LKM stands for Loadable Kernel Module.
- If you want to add code to a Linux kernel, the most basic way to do that is to add some source files to the kernel source tree and recompile the kernel. In fact, the kernel configuration process consists mainly of choosing which files to include in the kernel to be compiled.But you can also add code to the Linux kernel while it is running. A chunk of code that you add in this way is called a loadable kernel module.
- The characteristics of a LKM are
    - **Dynamic linking** : A kernel module can be loaded and linked into the kernel while the kernel is already in memory and executing.A module can also be unlinked and removed from memory at any time.
    - **Stackable modules** : The modules are arranged in a hierarchy. Individual modules serve as libraries when they are referenced by client modules higher up in the hierarchy, and as clients when they reference modules further down.
- The alternative is to provide the functionality directly into the kernel without any means to dynamically include or remove it once the kernel has been compiled.

## 5. What does Out-of-Tree Module mean? What's the alternative and what are the differences?
- It refers to where the resulting build output/artifacts are placed during a compile, "out-of-tree", in a separate root directory that separates the build output from the source files.
- The alternative is to *upstream* the module.
- Out-of-tree modules are easier to get started with and allow for a faster development cycle without going through the extensive review process for new kernel modules or updates for existing ones. However, it is also requires one to manually keep up with changes done in the upstream kernel.

## 6. How did you define the module metadata? How does it work?
- We defined the metadata inside the BitBake recipe.One simply has to assign the desired values to predefined variable names which Yocto then automatically recognizes.

## 7. How is the module built? How does it get installed inside `core-image-minimal`?
-  It is build using a Makefile whilst the target core-image-minimal is generated. This is due to it being listed inside the `IMAGE_INSTALL_append` list in our `build/conf/local.conf`file.

## 8. What is the path for the `sysfs` entry for the module? List and explain its contents.
- The sysfs entry is `/sys/module/hello`.
- The most important files to use is the parameter directory. It provides access to each of the module parameters by exposing them as files and depending on the module allows changing them during runtime.
- Other files and directories provide information about the modules metadata and composition (e.g. sections) or expose internal bookkeeping information (e.g. refcnt).

## 9. Feedback (what was difficult? what was easy? how would you improve it?)
- Initially, I felt difficult and after understanding the steps it was easy. Mention all instructions clearly in one place would be better.
