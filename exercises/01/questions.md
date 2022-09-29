# Exercise 01 - Q&A

## 1. What did you accomplish in this exercise?
- In this exercise, we created a image of custom  Linux OS using yocto project for pynq-z1 board. 

## 2. How does Yocto recognize that the target machine "pynq" is supported?
- Yocto recognizes target machine from `local.conf` configuration file  under `build/conf` directory where we configured as `MACHINE ?= "pynq"`
## 3. Where do you find the device-tree source code for the PYNQ board?
- The device tree source code is located in `meta-pynq` repository under `recipes-bsp` directory.

## 4. What is the priority of the PYNQ support layer?
- The priority of the PYNQ support layer is `5`.

## 5. What additional applications are installed to the `core-image-minimal` target in the PYNQ support layer?
- The additional applications are rt-tests and dropbear.