# Exercise 06 - Q&A

## 1. What is the goal of this exercise? What did you accomplish?
To understand platform drivers and device resources management.

## 2. What is a platform device? What makes such a device different from, e.g., a USB device or a PCI device?
- Platform devices are devices that typically appear as autonomous entities in the system. This includes legacy port-based devices  and host bridges to peripheral buses, and most controllers integrated into system-on-chip platforms.
- Our device is non-hot-pluggable and non-discoverable when compared with USB and PCI device.

## 3. What is the relation between the device-tree and platform device drivers?
- The platform devices cannot be automatically detected, we must inform Linux kernel what platform devices are present in the system, and their properties (address, interrupt number, etc). This is done using the device tree.
- Platform drivers use the information from device tree(IRQ numbers and addresses) and communicates with desired platform device. 

## 4. Why did we bother to rewrite the LKM code to implement a platform device driver?
- We bother to rewrite because that implementation support only one IRQ line and using hardcoding address and irq ids. 

## 5. Imagine you are developing a product on the PYNQ-Z1 board involving several IP blocks of your own design to squeeze all the resources and cabalities of the SoC FPGA; most IP blocks are accessible from the PS through the AMBA/AXI bus. Do you need to alter the device-tree we are using? What's the minimum set of information that you would require for each addressable IP block?
- Yes. The address and length of the block/register area. Interrupt numbers and to identify the device we require compatible property. 

## 6. What capabilities are exposed through the current sysfs interface of the `irqgen`? Describe the available entry points inside `/sys/kernel/irqgen` and their functions.

  ```
  amount
  enabled
  intr_ids
  latency
  total_handled
  count_register
  intr_acks
  intr_idx
  line
  delay
  intr_handled
  latencies
  line_count
  ```

## 7. Are there code sections that are missing concurrency barriers? Where? Can you think of a way of triggering unintended behaviour?
- I dont know the answer.

## 8. Feedback (what was difficult? what was easy? how would you improve it?)
- It was difficult.Need some more time to do the exercise.

