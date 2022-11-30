# Exercise 07 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
- The goal of this exercise is that to understand character device drivers.

## 2. What is a Character Device? How is it different from a Block Device?
- Character devices transfer data to or from a user application by means of characters in a stream manner like a serial port does.
- A block driver provides access to devices that transfer randomly accessible data in fixed-size blocks like disk drives, primarily.

## 3. What design limits of the Ex6 version of `irqgen-mod` do we try to address adding a character device?
- In previous exercise, the userspace cannot access the values in `irqgen data` like latency information. In this exercise 7 , we added character device to transfer the data from kernelspace to userspace.
## 4. What system calls are we implementing for the filesystem representation of our character device?
-  We are implementing three system calls such as `open()`, `release()` and `read()` for the filesystem representation of our character device.

## 5. How does a device node differ from a regular file? What things are similar/identical?
- Character device files contain metadata: the major and minor device numbers. When processes perform I/O on character device files, the kernel uses that metadata to find the right character device driver in the kernel to handle the I/O requests made against the file. That is different from a regular file.

## 6. Which parts of our LKM code are potentially running in parallel? Which parts could interact in a conflicting way? Make a few concrete examples of conditions in which conflicts in concurrency may arise.
- There are two parts of the LKM where they potentially run in parallel, the interrupt handler and the char device read syscall, since they both access the same irqgen data and both can occur asynchronously. Interrupt occurs and starts changing the irqgen_data while the read syscall is executing due to a process who called it to read from the character device.

## 7. In the proposed structure, we opted for a single lock for the whole `irqgen_data` structure. Could you describe advantages and disadvantages of a single lock vs several locks? What about the effects on the IRQ handling latency?
- A single lock is simpler, but it can block in situations where it is not necessarily needed, for example accessing different non overlaping elements of an array. However, it is less likely to result in deadlock situations. Whereas several locks result in less blocking overall, but the chances of having deadlocks are way higher and it is more complex to manage multiple locks, and they may introduce more overhead.

## 8. To avoid concurrency issues among the different parts of `irqgen-mod` you had to choose a synchronization mechanisms. What kind did you choose? Why? Where? What alternatives did you consider? Why did you reject them?
- We chose to use spin locks because they cannot sleep and this is very important in the case of the irqgen-mod since the concurrency is occuring at the interrupts level not thread level, so we have an atomic context. We considered mutexes or semaphores, but since they sleep, we rejected them.

## 9. To optimize even more the IRQ handling latency we should abandon the monolithic handler function for a more efficient pattern: what's its name? Describe how the code currently handling the requests would be organized and describe a few reasons to choose the alternative over the monolithic style.
- We could use a top-bottom half approach, where the interrupt handling occurs in the top half, and updating data and dealing with concurrency can happen in the bottom half.
## 10. What is an SDK?
- An SDK consists of the following:
    - **Cross-Development Toolchain** : This toolchain contains a compiler, debugger, and various miscellaneous tools.
    - **Libraries, Headers, and Symbols** : The libraries, headers, and symbols are specific to the image (i.e. they match the image).
    - **Environment Setup Script** : This *.sh file, once run, sets up the cross-development environment by defining variables and preparing for SDK use.
## 11. In the context of the Yocto Project, what are the differences between the Standard and the Extensible SDK?
- An extensible SDK consists of everything that the standard SDK has plus tools that allow you to easily add new applications and libraries to an image, modify the source of an existing component, test changes on the target hardware, and easily integrate an application into the OpenEmbedded build system.

## 12. Describe your workflow in developing and testing the `irqgen_statistics` app
- In the irqgen_statistics application, I used `getline` to get the line and used `sscanf` to separate line number, latency, timestamp and stored in `stats_data` struct object. The latencies of respective lines are added and stored in `stats_data` struct objects. The event count is incremented, whenever the interrupt is generated. After the interrupt generation , `CTRL+C` is pressed then the overall latency results are displayed.

## 13. Feedback (what was difficult? what was easy? how would you improve it?)
- It is moderate and nothing to improve.