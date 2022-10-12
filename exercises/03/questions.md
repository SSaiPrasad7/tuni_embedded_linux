# Exercise 03 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
- This exercise aims to teach kernel debugging.We resolved the runtime errors in the file `evil.c`.
## 2. Where is the `evil-tests` script installed inside the image? Where is the accompanying data installed? Describe how this is set up in Yocto.
- The script file is located at `/opt/evil-tests/sbin/`
- Accompanying data is installed at `/opt/evil-tests/share/data.txt`
- In `evil-tests.bb`file under do_install,the location of script file and accompanying data is specified.
## 3. How are the LKM and `evil-tests` added to `core-image-minimal`? Briefly describe what sets apart the `evil-tests` recipe compared with most recipes included in `meta-groupXX`, `meta-pynq`, `meta-xilinx` and `poky`.
- The `evil-mod` and `evil-tests` are added to `core-image-minimal` using `IMAGE_INSTALL`specified in `meta-compce460\recipes-core\images\core-image-minimal.bbappend` which instructs yocto to install.
-  The `evil-tests` recipe only have do_install step but for others, it has do_configure and do_compile.
## 4. How many buffers does the `evil` LKM use? List their names, their size and their purpose. How is their memory allocated?
- Two buffers input_buf and data_storage.
- `input_buf` is for data which is written to evil sysfs file.
- `data_storage` allocates with `PAGE_SIZE` has 4096 bytes using kmalloc and later allocated with 1000 bytes.

## 5. How are user-input strings stored inside the module? How does the module iterate over this list? What's the loop end condition?
- User strings are kept in data storage, separated by the character '0'. The module makes several attempts to read from the data storage, each starting at a different offset (after the last instance of "0").
- This is done in order to iterate the list. If no additional data is read from the buffer, or if the return value of sprintf is 0, the loop is terminated.

## 6. What is the path for the `evil` LKM's sysfs entry? How is it determined? How is it mapped to the module functionality?
- The path for `evil` is `/sys/kernel/evil_module/evil`.The result of mounting the `evil-mod` under the `/sys/kernel` directory and having set the name of the file inside the device struct to evil.
- Mapping is done by setting the .show and .store
attributes of the device struct to the desired handler functions.

## 7. What bugs did you find/fix? Categorize them and briefly describe each matching *category* (what's the *impact* of each *category*? How common do you *think* it is?)
| Bug  |  find |  fix | Difficulty |
|------|-------|------|----------- |
| Tasklet Memory allocation is missing  | Reading and working about tasklet declaration. | Used kmalloc function, to allocate memory. | High |
| `+=`  |  Guessed it |  Removed  `+`| Easy |
| `Permission write denied`  | Understood from the trace. |  Added the write permission |  Easy |   
|  out-of-bounds buffer access | Understoof from the trace  | Took time to fix.i.e `return -1`  | High | 

## 8. What are out-of-bounds accesses and stack overflows? Are they relevant for this exercise? What could be the consequences of such defects in a LKM?
- **Out-of-bounds**  are scenarios in which code reads or writes to memory regions outside of a buffer or struct. 
- **Stack overflow** is a runtime error that happens when a program runs out of memory in the call stack.
- Yes.The out-of-bounds accesses
- These have undefined behavior, and can result in crashes or incorrect program output.

## 9. Feedback (what was difficult? what was easy? how would you improve it?)
- It was average.No need to improve anything.
