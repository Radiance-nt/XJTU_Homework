## OS第六次作业

--------------
>1 A certain computer provides its users with a virtual-memory space of 2<sup>32</sup> bytes. The computer has 2<sup>18</sup> bytes of physical memory. The virtual memory is implemented by paging, and the page size is 4096 bytes. A user process generates the virtual address 11123456. Explain how the system establishes the corresponding physical location. Distinguish between software and hardware operations..<br>

The virtual address in binary form is

0001 0001 0001 0010 0011 0100 0101 0110

Since the page size is 2<sup>12</sup>, the page table size is <sup>20</sup>. Therefore, The page-table entry at index 69923 will give us the 6-bit physical frame number. 

|Index |Offset | 
| :-----:| :----: |
|0001 0001 0001   | 0010 0011 0100 0101 0110 |


--------------

>2 Consider a demand-paging system with the following time-measured utilizations: 
<br>CPU utilization 20% 
<br>Paging disk 97.7% 
<br>Other I/O devices 5% <br>
<br>Which (if any) of the following will (probably) improve CPU utilization? Explain your answer.
<br>a. Install a faster CPU.
<br>b. Install a bigger paging disk.
<br>c. Increasxe the degree of multiprogramming.
<br>d. Decrease the degree of multiprogramming.
<br>e. Install more main memory.
<br>f. Install a faster hard disk or multiple controllers with multiple hard disks.
<br>g. Add prepaging to the page fetch algorithms.
<br>h. Increase the page size.

--------------
a. No.
The CPU utilization is low,hence the system is spending most of its time in paging. Thus over-allocation ofmemory is taking place. The purpose is to improve CPU utilization.

b. No, A bigger paging disk can store a larger number of pages in the secondary storage disk which will increase thepaging disk utilization. Hence it will not improve CPU utilization

c. No, When the Degree of multiprogramming increases, more number of processes share the same amount ofmemory. Hence it will not improve CPU utilization

d. No, When the Degree of multiprogramming decrease, then the running processes will have more memory. Hence,no process will wait for the memory which will improve CPU utilization

e. Yes. When the main memory increases more pages can remain resident The CPU will depend less on the secondarystorage for swapping and executes programs in a faster and efficient manner. Therefore, increased main memory will show improvement of CPU utilization.

f. Yes. Whenever the page fault occurs and requested page is not available in the main memory, CPU access the harddisk for the data.
lf a faster hard disk or multiple hard disks with multiple controllers are installed, then the CPU can access alarge number of pages from the disk in smaller time. This will definitely improve the CPU utilization.

g. Yes. In a prepaging scheme, pages are brought into main memory before as they are requested by the CPu.So CPU waiting time reduces in the swapping process and it is able to execute pages quickly leading toincreased CPU utilization.

h. No. When page size is increased, number of page faults are also increased when the data are being accessedsequentially. However lf the data is being accessed randomly, then the paging action needed by the CPU isincreased as due to large page size, fewer pages are kept in the memory. Which results in more data needed tobe transferred per every page fault This increasing page size does not increase CPU utilization



--------------
>3 A page-replacement algorithm should minimize the number of page faults. We can do this minimization by distributing heavily used pages evenly over all of memory, rather than having them compete for a small number of page frames. We can associate with each page frame a counter of the number of pages that are associated with that frame. Then, to replace a page, we search for the page frame with the smallest counter.<br>
>a.	Define a page-replacement algorithm using this basic idea. Specif- ically address the problems of (1) what the initial value of the counters is, (2) when counters are increased, (3) when counters are decreased, and (4) how the page to be replaced is selected.<br>
>b. How many page faults occur for your algorithm for the following reference string, for four page frames?<br>
1, 2, 3, 4, 5, 3, 4, 1, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4, 2.<br>
c. What is the minimum number of page faults for an optimal page- replacement strategy for the reference string in part b with four page frames?
<br>
<br>

a. Define a page-replacement algorithm addressing the problems of:
1. Initial value of the counters = 0.
2. Increase the counters by 1 whenever a new page is associated with that frame. 
3. Decrease the counters by 1 whenever one of the associated pages is no longer required. 
4. Find a frame with the smallest counter and replace it.

b. 13 page faults

c. 11 page faults
