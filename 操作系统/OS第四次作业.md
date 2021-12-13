## OS第四次作业

> 1.Explain why spinlocks are not appropriate for single-processor systems yet are often used in multiprocessor systems.

Spinlocks  are  not  appropriate  for  single-processor  systems  because  the  condition 
that  would  break  a  process  out  of  the  spinlock  can  be  obtained  only  by  executing  a 
different process. If the process is not relinquishing the processor, other processes do 
not  get  the  opportunity  to  set  the  program  condition  required  for  the  first  process  to 
make progress. In a multiprocessor system, other processes execute on other 
processors and thereby modify the program state in order to release the first process 
from the spinlock. 

>2.Show that, if the wait() and signal() semaphore operations are not executed atomically, then mutual exclusion may be violated.

A wait operation atomically decrements the value associated with a semaphore. If two wait operations are executed on a semaphore when its value is 1, if the two operations are not performed atomically, then it is possible that both operations might proceed to decrement the semaphore value thereby violating mutual exclusion.

>3.A barbershop consists of a waiting room with n chairs and abarber room with one barber chair. If there are no customers to be served, the barber goes to sleep. If a customer enters the barbershop and all chairs are occupied, then the customer leaves the shop. If the barber is busy but chairs are available, the customer sits in one of the free chairs. If the barber is asleep, the customer wakes up the barber. Write a program to coordinate the barber and the customers.

	
	理发师:
	while(1){
	P（customer）// sleep
	P（mutex) // wake 
	V（barber)
	V（mutex)
	chair++
	}
	
	顾客:
    P（mutex)
    if(chair > 0)
    {
        chair--
        V(customer)
        V(mutex)
        P(barber) // waiting for barber
        /*理发*/
    }
    else
	{
        V(mutex)
		exit()
    ｝  

>4.有一个系统，定义P、V操作如下：
P(s):
s:=s-1;
if s<0 then
将本进程插入相应队列末尾等待；
V(s)：
s:=s+1;
if s<=0 then
从相应等待队列队尾唤醒一个进程，将其插入就绪队列；
>
(1)这样定义P、V操作是否有问题？
>
(2)用这样的P、V操作实现N个进程竞争使用某一共享变量的互斥机制。


(1)先入后出，相当于栈储存。当任务量非常多时，栈底任务可能会长时间得不到调用，导致饥饿。

(2)	见代码

	Semaphore S[N-1]

	for(int i=0 ; i<n-1 ; i++)
		P(S[i])
		for(int i=n-2 ; i>=0 ; i--)
			V(S[i])
	}

>5.第二类读者写者问题：写者优先
条件：
多个读者可以同时进行读
写者必须互斥（只允许一个写者写，也不能读者写者同时进行）
写者优先于读者（一旦有写者，则后续读者必须等待，唤醒时优先考虑写者）

	Semaphore: FileState
	
	读者:
	P(mutexWriteQ)
	while(WriteQ.length()!=0){
	/*忙等待*/
	}
	V(mutexWriteQ)
	P(mutex)
	readcount ++
	if (readcount==1)
		P(FileState)
	V(mutex)
	/*读操作*/
	P(mutex)
	readcount --
	
	写者:
	P(mutexWriteQ)
	WriterQ.push() //写者入队
	V(mutexWriteQ)
	P(FileState);
	P(mutexWriteQ)
	writer=WriterQ.pop()
	V(mutexWriteQ)
	/*写操作*/
	V(FileState)
	V(mutexWriteQ)

	


>6.把学生和监考老师都看作进程, 学生有N人, 教师1人. 考场门口每次只能进出一个人, 进考场原则是先来先进. 当N个学生都进入考场后, 教师才能发卷子. 学生交卷后可以离开考场. 教师要等收上来全部卷子并封装卷子后才能离开考场.
问题:
问共需设置几个进程?
试用P、V操作解决上述问题中的同步和互斥关系.

	Semaphore：door,ready(发完卷子可以做题)

	老师:
	P(door) // 进考场
	V(door)
	while(students<N){
		/*忙等待*/
	}
	for(i = 0;i<N;i++){
	/*给第i个学生发卷	*/
	}
	ready=True
	while(students》0){
		/*忙等待*/
	}
	P(door)	// 出考场
	V(door)

	学生:
	P(door)	// 进考场
	students++
	V(door)
	while(ready){
		/*忙等待*/
	}
	/*做题交卷*/
	P(door)	// 出考场
	students--
	V(door)
