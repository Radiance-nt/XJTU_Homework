## OS第七次作业

--------------
> 11.1 What are the advantages of the variation of linked allocation that uses a FAT to chain together the blocks of a file?<br>

The advantage is that while accessing a block that is stored at the middle of a file, its location can be determined by chasing the
pointers stored in the
FAT
as opposed to accessing all of the individual
blocks of the file in a sequential manner to find the pointer to the target
block. Typically, most of the
FAT
can be cached in memory and therefore
the pointers can be determined with just memory accesses instead of
having to access the disk blocks.

--------------

> 11.2 Some file systems allow disk storage to be allocated at different levels of granularity. For instance, a file system could allocate 4 KB of disk space as a single 4-KB block or as eight 512-byte blocks. How could we take advantage of this flexibility to improve performance? What modifications would have to be made to the free-space management scheme in order to support this feature?
<br>

Such a scheme would decrease internal fragmentation. If a file is 5KB
, then it could be allocated a 4 KB
block and two contiguous 512-byte blocks. In addition to maintaining a bitmap of free blocks, one would also have to maintain extra state regarding which of the
subblocks are currently being used inside a block. The allocator would then have to examine this extra state to allocate subblocks and coalesce the subblocks to obtain the larger block when all of the subblocks become free

--------------
>11.3 Fragmentation on a storage device could be eliminated by recompaction of the information. Typical disk devices do not have relocation or base registers (such as are used when memory is to be compacted), so how can we relocate files? Give two reasons why recompacting and relocation of files often are avoided.<br>


First, relocation of files on secondary storage involves considerable overhead. Data blocks have to be read into main memory and written back out to their new locations. 

Second, relocation registers apply only to sequential files, and many disk files are not sequential.

--------------
> 12.1 None of the disk-scheduling disciplines, except FCFS, is truly fair (starvation may occur).
<br>a. Explain why this assertion is true.
<br>b. Describe a way to modify algorithms such as SCAN to ensure fairness.
<br>c. Explain why fairness is an important goal in a time-sharing system.
<br>d. Give examples of circumstances in which it is important that the operating system be unfair in serving I/O requests.

a. New requests for the track over which the head currently resides can theoretically arrive as quickly as
these requests are being serviced.

b. All requests older than some predetermined age could be forced to the top of the queue, and an
associated bit for each could be set to indicate that no new request could be moved ahead of these requests.
For SSTF, the rest of the queue would have to be reorganized with respect to the last of these old requests.

c. To prevent unusually long response times.

d. Paging and swapping should take priority over user requests. It may be desirable for other kernelinitiated
I/O, such as the writing of ¯le system metadata, to take precedence over user I/O. If the kernel
supports real-time process priorities, the I/O requests of those processes should be favored.


--------------
>12.2 Suppose that a disk drive has 5000 cylinders, numbered 0 to 4999. The drive is currently serving a request at cylinder 143, and the previous request was at cylinder 125. The queue of pending requests, in FIFO order, is
<br><br>86, 1470, 913, 1774, 948, 1509, 1022, 1750, 130
<br><br>Starting from the current head position, what is the total distance (in cylinders) that the disk arm moves to satisfy all the pending requests, for each of the following disk-scheduling algorithms?
<br>a. FCFS 
<br>b. SSTF
<br>c. SCAN 
<br>d. LOOK
<br>e. C-SCAN



a. The FCFS schedule is 143, 86, 1470, 913, 1774, 948, 1509, 1022, 1750, 130. &nbsp;&nbsp;&nbsp; The total seek distance is
7081.

b. The SSTF schedule is 143, 130, 86, 913, 948, 1022, 1470, 1509, 1750, 1774. &nbsp;&nbsp;&nbsp; The total seek distance is
1745.

c. The SCAN schedule is 143, 913, 948, 1022, 1470, 1509, 1750, 1774, 130, 86.  &nbsp;&nbsp;&nbsp;The total seek distance
is 9769.

d. The LOOK schedule is 143, 913, 948, 1022, 1470, 1509, 1750, 1774, 130, 86. &nbsp;&nbsp;&nbsp; The total seek distance is
3319.

e. The C-SCAN schedule is 143, 913, 948, 1022, 1470, 1509, 1750, 1774, 86, 130.  &nbsp;&nbsp;&nbsp;The total seek
distance is 9813.
