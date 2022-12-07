# Exercise 08 - Q&A

## 1. What is `uname -a` output on the PYNQ board before starting Ex 8?
```
Linux pynq 4.9.0-xilinx-v2017.3 #1 SMP PREEMPT Thu Aug 9 16:33:05 UTC 2018 armv7l GNU/Linux
```
## 2. What is the average latency and worst case latency you measure after Ex 7 using the application you developed?
```
IRQ line: 0  Events occured: 10054 Average Latency: 264.304058 worst latency: 3222 
IRQ line: 1  Events occured: 10370 Average Latency: 256.259402 worst latency: 2801
IRQ line: 2  Events occured: 10950 Average Latency: 283.371598 worst latency: 344969
IRQ line: 3  Events occured: 11167 Average Latency: 231.122952 worst latency: 3732
IRQ line: 4  Events occured: 11311 Average Latency: 284.736716 worst latency: 342209
IRQ line: 5  Events occured: 11617 Average Latency: 264.225015 worst latency: 206986
IRQ line: 6  Events occured: 10834 Average Latency: 236.052428 worst latency: 3792
IRQ 1ine: 7  Events occured: 10652 Average Latency: 238.101671 worst latency: 4224
IRQ line: 8  Events occured: 10078 Average Latency: 284.457829 worst latency: 340713
IRQ line: 9  Events occured: 8998  Average Latency: 253.072127 worst latency: 3161
IRQ line: 10 Events occured: 10371 Average Latency: 292.909845 worst latency: 344017
IRQ line: 11 Events occured: 11845 Average Latency: 281.267708 worst latency: 346238
IRQ line: 12 Events occured: 11466 Average Latency: 287.569074 worst latency: 343827
IRQ line: 13 Events occured: 11159 Average Latency: 238.046689 worst latency: 3538
IRQ line: 14 Events occured: 10702 Average Latency: 239.725005 worst latency: 4100
IRQ line: 15 Events occured: 10299 Average Latency: 260.292747 worst latency: 3584
Overall Results:
      Events occured: 171873 Average Latency: 244.441064 worst latency: 346238
```
## 3. What is `uname -a` output on the PYNQ board after rebooting with the new kernel image?
```
Linux pynq 4.9.0-rt1-xilinx-v2017.3 #2 SMP PREEMPT RT Mon Dec 5 15:50:21 UTC 2022 armv7l GNU/Linux
```
## 4. What is the average latency and worst case latency you measure in the new kernel image (same procedure as question 2)?
```
IRQ line: 0  Events occured: 6790 Average Latency: 842.981149 worst latency: 6738
IRQ line: 1  Events occured: 6608 Average Latency: 829.036774 worst latency: 6209
IRQ line: 2  Events occured: 5757 Average Latency: 979.113427 worst latency: 5960
IRQ line: 3  Events occured: 5175 Average Latency: 969.986280 worst latency: 6086
IRQ line: 4  Events occured: 6307 Average Latency: 970.517203 worst latency: 5308
IRQ line: 5  Events occured: 5270 Average Latency: 808.573814 worst latency: 6689
IRQ line: 6  Events occured: 6789 Average Latency: 911.940639 worst latency: 5662
IRQ line: 7  Events occured: 6763 Average Latency: 891.598699 worst latency: 5433
IRQ 1ine: 8  Events occured: 6932 Average Latency: 962.204126 worst latency: 5858
IRQ line: 9  Events occured: 4865 Average Latency: 1058.62446 worst latency: 4585
IRQ line: 10 Events occured: 4400 Average Latency: 816.374318 worst latency: 5523
IRQ line: 11 Events occured: 6682 Average Latency: 770.002095 worst latency: 6075
IRQ line: 12 Events occured: 7180 Average Latency: 804.411978 worst latency: 5469
IRQ line: 13 Events occured: 7323 Average Latency: 912.753653 worst latency: 5858
IRQ line: 14 Events occured: 7388 Average Latency: 893.796156 worst latency: 4931
IRQ line: 15 Events occured: 7089 Average Latency: 861.051206 worst latency: 6303
Overall Results:
      Events occured: 101318 Average Latency: 892.685373 worst latency: 6738
```

## 5. Compare the results of questions 2 and 4; do they differ significantly? why?
- Yes. When using the RT linux, the average latency increased but worst latency and events occured are decreased. This occurs because it solved interrupt priority inversion problem and adding RT patch to linux causes the scheduling overhead.

## 6. Compare the plots for the 6 different profiles. Describe each of them and compare them?
- These plots represent the IRQ latency on line 5(hw_irq:51) interrupt.
### Graph 1 (No RT No Torture)
- The spikes are more in this graph, these represents random behaviour.

### Graph 2 (No RT Torture)

### Graph 3 (RT No Torture)

### Graph 4 (RT Torture)

### Graph 5 (Tuned RT No Torture)

### Graph 6 (Tuned RT Torture)

## 7. Document the RT performance differences and their reasons
|                     | no RT, no torture |no RT, torture | RT, no torture | RT, torture |tuned RT, no torture | tuned RT, torture |
|---------------------|-------------------|---------------|----------------|-------------|---------------------|-------------------|
| Lowest latency      | 201               | 199           | 426            | 275         | 279                 | 274               |
| Highest latency     | 5999              | 5243          | 205910         | 7477        | 5956                | 7252              |

## 8. What is the goal of this exercise? What did you accomplish?
- The goal of the exercise is to run interrupt handler in kernel thread by using RT linux patch and performing stress test.In the exercise, we measure the interrupt latency performances using RT linux and non RT linux.

## 9. Feedback (what was difficult? what was easy? how would you improve it?)
- Instructions are easy to understand. To find the right RT patch was difficult. Nothing to improve.