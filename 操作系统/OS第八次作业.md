## OS第八次作业

--------------
> 13.1 Consider the following I/O scenarios on a single-user PC.<br>
a. A mouse used with a graphical user interface<br>
b. A tape drive on a multitasking operating system (assume no device preallocation is available)<br>
c. A disk drive containing user files<br>
 <br>
For each of these I/O scenarios, would you design the operating system to use buffering, spooling, caching, or a combination? Would you use polled I/O, or interrupt-driven I/O? Give reasons for your choices.

<br>

a. Buffering may be needed to record mouse movement during times when higher-priority operations are taking place. Spooling and caching are inappropriate. Interrupt-driven I/O is most appropriate.

b. Buffering may be needed to manage throughput difference between the tape drive and the source or destination of the I/O . Caching can be used to hold copies of data that resides on the tape, for faster access. Spooling could be used to stage data to the device when multiple users desire to read from or write to it. Interrupt-driven I/O is likely to allow the best performance. 

c. Buffering can be used to hold data while in transit from user space to the disk, and visa versa. Caching can be used to hold disk-resident data for improved performance. Spooling is not necessary because disks are shared-access devices. Interrupt- driven I/O is best for devices such as disks that transfer data at slow rates.

--------------

> 13.2 What are the various kinds of performance overheads associated with servicing an interrupt?
<br>

The performance overheads include the cost of saving and restoring process state and the cost of flushing the instruction pipeline and restoring the instructions into the pipeline when the process is restarted.
