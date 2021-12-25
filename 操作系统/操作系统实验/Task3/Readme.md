# Experiment3

### User Input
PAGE_LENGTH, Block Num, Replacement algorithm (FIFO or LRU)

:
### Output
Memory status, page replacement order ...

### Example: 

Input:

    define PAGE_LENGTH 4
    Block num = 4
    Page num = 8
    Pages to visit:
    1 2 3 4 2 3 5 1

Output:

    Choose your algorithm:
    1.FIFO 2.LRU 3.exit
    1
    1
    |1|
    Primary_memory[0] :b 
    bbbbbbbbdddd
    2
    |1| |2|
    Primary_memory[4] :c 
    bbbbccccdddd
    3
    |1| |2| |3|
    Primary_memory[8] :d 
    bbbbccccdddd
    4
    |4| |2| |3|
    Primary_memory[0] :e 
    eeeeccccdddd
    2
    Primary_memory[4] :c 
    eeeeccccdddd
    3
    Primary_memory[8] :d 
    eeeeccccdddd
    5
    |4| |5| |3|
    Primary_memory[4] :f 
    eeeeffffdddd
    1
    |4| |5| |1|
    Primary_memory[8] :b 
    eeeeffffbbbb
    Page fault:6   Page fault ratio:6/8
    Replacement:3  Hit ratio:0.25

    Choose your algorithm:
    1.FIFO 2.LRU 3.exit
    2
    1
    |1|
    Primary_memory[0] :b 
    bbbbffffbbbb
    2
    |1| |2|
    Primary_memory[4] :c 
    bbbbccccbbbb
    3
    |1| |2| |3|
    Primary_memory[8] :d 
    bbbbccccdddd
    4
    |4| |2| |3|
    Primary_memory[0] :e 
    eeeeccccdddd
    2
    Primary_memory[4] :c 
    eeeeccccdddd
    3
    Primary_memory[8] :d 
    eeeeccccdddd
    5
    |5| |2| |3|
    Primary_memory[0] :f 
    ffffccccdddd
    1
    |5| |1| |3|
    Primary_memory[4] :b 
    ffffbbbbdddd
    Page fault:6   Page fault ratio:6/8
    Replacement:3  Hit ratio:0.25



------


