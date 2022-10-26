# Exercise 04 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
- The goal of this exercise to learn is how to generate interrupts using FPGA pynq board.I filled the stubs with right functionality.

## 2. Summarize the functionality provided by the IRQ Generator IP block, then describe what is the purpose of the various registers exposed by the FPGA device. Finally, ignore the fact that you were instructed to look for the base address of the IRQ Generator register space in the provided `devicetree.dts` and instead imagine you were also the developer of the FPGA core design, where would you have found the base address of the register space?
- The functionality of IRQ to generate interrupts(level sensitive)  between the Programmable logic and processing system.
- Registers description:
    - IRQ_GEN_CTRL_REG – Offset 0x0000 : for core control and irq handling.
    - IRQ_GEN_GENIRQ_REG – Offset 0x0004 : the core to generate specific amount of IRQs to an IRQ line.
    - IRQ_GEN_IRQ_COUNT_REG – Offset 0x0008 : in this count field is incremented when some IRQ line is triggered.
    - IRQ_GEN_LATENCY_REG – Offset 0x000C : it stores the latency of the last successfully served IRQ. 
- We can get the base address from FPGA vendor manuals or datasheets.

## 3. Describe the relationship between interrupt lines in the IRQ Generator, HW IRQ and Linux IRQ numbers, and how did you proceed to discover the IRQ number to use in the driver.
- IRQ generator has 16 interrupt output lines these are connected to CPU, those are called HW IRQs. The kernel doesnot directly use HW IRQs instead they have mapping for HW IRQs.These are referred to as Linux IRQ numbers. 
-  I found the first HW IRQ number(61) from spec and the ran the command `grep -s 61 */hwirq` on the terminal at `/sys/kernel/irq` location.

## 4. How many interrupt lines are available in the documented FPGA core (refer to the spec, even if we only used one in the *beta* bitstream we were given)?
- 16 interrupt lines(61-68 and 84-91)

## 5. What value is reported in the devicetree for the first IRQ line? How is it determined? (check the spec document, it has all the required information to map the line number to the HW IRQ on the processing system)
- 45 value is reported from the devicetree for the first IRQ line. It is determined by running the command `grep -s 61 */hwirq` at `/sys/kernel/irq` location.

## 6. Using the information detailed in the previous answer, what should be written in the `devicetree.dts` line describing the IRQ Generator interrupts if it were to describe all the 16 HW IRQs? (write the exact line as it would appear in the `devicetree.dts`, notice that the HW IRQs are not contiguous!). Each interrupt line is specified by three cells in the device tree file; what information does each of these three cells represent?
 ```
 irq_gen@43C00000 { 
 compatible = "wapice,irq-gen"; 
 interrupt-parent = <0x4>; 
             #interrupt-cells = <0x3>; 
 interrupts = <0x0 0x1d 0x4 0x0 0x1e 0x4 0x0 0x1f 0x4 0x0 0x20 0x4               
                           0x0 0x21 0x4 0x0 0x22 0x4 0x0 0x23 0x4 0x0 0x24 0x4  
                           0x0 0x34 0x4 0x0 0x35 0x4 0x0 0x36 0x4 0x0 0x37 0x4  
                           0x0 0x38 0x4 0x0 0x39 0x4 0x0 0x3a 0x4 0x0 0x3b 0x4>; 
 wapice,intrack = <ACK1d ACK1e ACK1f ACK20 ACK21 ACK22 ACK23 ACK24  
                               ACK34 ACK35 ACK36 ACK37 ACK38 ACK39 ACK3a ACK3b>; 
 reg = <0x43c00000 0x10000>; 
};
 ```
 - First cell (interrupt type) : 
    - 0 : SPIs (shared peripheral interrupt)
    - 1 : PPIs (private peripheral interrupt) 
 - Second cell is interrupt number 
 - Third cell (interrupt type)
    - 1 : low-to-high edge
    - 2 : high-to-low edge
    - 4 : active high level-sensitive
    - 8 : active low level-sensitive

## 7. Why do we need to use `ioremap`, `ioread32` and `iowrite32`? Why do we want to use the Linux kernel bitfields macroes rather than using bitwise arithmetic directly?
- Prior to accessing a memory region, the memory region must be mapped into kernel address space for that we need to use `ioremap`.
- The `ioremap` returns `__iomem void` pointer which `ioread32()` and `iowrite32()` accepts  __iomem addresses only.So, this io access more secure.
- Bitfields Macros are easy to use for bit manipulation and safety purposes.

## 8. (BONUS, optional) Did you find any bug in the bitstream implementation while testing the sysfs interface?

## 9. Feedback (what was difficult? what was easy? how would you improve it?)
- It was bit difficult to understand the documentation. No need to improve.

