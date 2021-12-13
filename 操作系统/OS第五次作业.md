##  OS第五次作业

> 1 Consider the traffic deadlock depicted in Figure 7.9.

>a. Show that the four necessary conditons for deadlock indeed hold in this example.
      
>b. State a simple rule for avoiding deadlocks in this system.

 a. The four necessary conditions for a deadlock are (1) mutual exclusion; (2) hold-and-wait; (3) no preemption; and (4) circular wait

The mutual exclusion condition holds since only one car can occupy a space in the roadway. Hold-and-wait occurs where a car holds onto its place in the roadway while it waits to advance in the roadway. A car cannot be removed (i.e. preempted) from its position in the roadway. Lastly, there is indeed a circular wait as each car is waiting for a subsequent car to advance. The circular wait condition is also easily observed from the graphic. 


b. A simple rule that would avoid this traffic deadlock is that a car may not advance

--------------
>2 Answer the following questions using the banker’s algorithm:

>a. What is the content of the matrix Need?

>b. Is the system in a safe state?

>c. If a request from process P1 arrives for (0,4,2,0), can the request be granted immediately?


| |Allocation | Max | Available |
| :-----| :----: | :----: | :----: |
|P0 |0012 |0012 |1520|
|P1	|1000 |1750 |    |
|P2	|1354 |2356 |    |
|P3	|0632 |0652 |    |
|P4	|0014 |0656 |    |

Answer

--------------
>3 Explain the difference between internal and external fragmentation.
	
Whenever a method request for the memory, the mounted sized block is allotted to the method. just in case the memory allotted to the method is somewhat larger than the memory requested, then the distinction between allotted and requested memory is that the Internal fragmentation. 

External fragmentation happens when there’s a sufficient quantity of area within the memory to satisfy the memory request of a method. however the process’s memory request cannot be fulfilled because the memory offered is during a non-contiguous manner. 

--------------
>4 Given five memory partitions of 100 KB, 500 KB, 200 KB, 300 KB, and 600 KB (in order), how would each of the first-fit, best-fit, and worst-fit algorithms place processes of 212 KB, 417 KB, 112 KB, and 426 KB (in order)? Which algorithm makes the most efficient use of memory?

First-fit: 


| Partition | Allocation |  |
| :-----| ----: | :----: |
| 100KB |   |   |
| 500KB | 212KB | 112KB |
| 200KB |   |   |
| 300KB |   |   |
| 600KB | 417KB |   |
| Failed | 426KB |   |

Best-fit:

| Partition | Allocation | |
| :-----| ----: | :----: |
| 100KB |   |   |
| 500KB | 417KB  |   |
| 200KB | 112KB  |   |
| 300KB | 212KB  |   |
| 600KB |  426KB |   |


Worst-fit:

| Partition | Allocation |  |
| :-----| ----: | :----: |
| 100KB | 417KB  |   |
| 500KB |   |   |
| 200KB |   |   |
| 300KB |   |   |
| 600KB |  212KB | 112KB  |
| Failed | 426KB |   |

Above all, best-fit algorithm makes the most efficient use of memory

--------------
> 5 Consider a paging system with the page table stored in memory.
  a. If a memory reference takes 200 nanoseconds, how long does a paged memory reference take?
  b. If we add TLBs, and 75 percent of all page-table reference are found in the TLBs, what is the effective memory reference time?(Assume that finding a page-table entry in the TLBs takes zero time, if the entry is there)

a: OS has to take 200 nanoseconds to look into paged memory and take another 200 nanoseconds to look into the memory. Thus the total time will be 400 nanoseconds.

b: Time taken = 0.75*200 +(1-0.75)*200*2 = 250 nanoseconds

--------------
>6 Consider the following segment table:
>What are the physical addresses for the following logical addresses?

| Segment | Base | Length |
| :-----| ----: |  ----: |
|0  |219  |600 |
|1	|2300 |14  |
|2	|90   |100 |
|3	|1327 |580 |
|4	|1952 |96  |


a. 219+430=649

b. 2300+10=2310

c. Illegal

d. Illegal

e. Illegal
