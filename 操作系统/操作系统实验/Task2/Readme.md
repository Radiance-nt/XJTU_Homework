# Experiment2
## Interupt:
##### Output:
    Child 1,my pid is:74188

    Child 2,my pid is:74189

    Signal Recieved

    Child 1 is killed

    Signal Recieved

    Child 2 is killed

    child processes has ended 

##### Illustration
> Signal Recieved

------
## Pipe:
##### Output:
    

    Child process 1 is sending message !


    Child process 2 is sending messagec !


##### Illustration
> None

------
## Replacement:

> 如果FIFO和LRU函数里报错了，去实验3里面复制过来删几行就行了

##### Output:

    Block num:
    3
    Page num:
    8
    Pages to visit?:
    1
    2
    3
    4
    2
    4
    3
    1
<br>FIFO：
  
    FIFO：
    1
    |1|
    2
    |1| |2|
    3
    |1| |2| |3|
    4
    |4| |2| |3|
    2
    4
    3
    1
    |4| |1| |3|
    Page fault:5   Page fault ratio:5/8
    Replacement:2  Hit ratio:0.38

 <br>LRU:
 
    3
    1
    |1|
    2
    |1| |2|
    3
    |1| |2| |3|
    4
    |4| |2| |3|
    2
    4
    3
    1
    |4| |1| |3|
    Page fault:5   Page fault ratio:5/8
    Replacement:2  Hit ratio:0.38
    
##### Illustration

