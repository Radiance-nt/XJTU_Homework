#include <stdio.h>
#include <string.h>

#define PAGE_NUM 25
#define PAGE_LENGTH 4

char second_memory[PAGE_NUM * PAGE_LENGTH];

int page_table[PAGE_NUM];

void init()
{
    for (int i = 0; i < PAGE_NUM; i++)
    {
        page_table[i] = -1;
        for (int j = 0; j < PAGE_LENGTH; j++)
        {
            second_memory[i * PAGE_LENGTH + j] = 'a' + i;
        }
    }
}

int Logic2Phy(int pageNum)
{
    int address = page_table[pageNum] * PAGE_LENGTH;
    return address;
}

void read(char primary_memory[], int logic, int phyNum)
{
    int address = Logic2Phy(logic);
    printf("Primary_memory[%d] :%c \n", address, primary_memory[address]);
    showList(primary_memory, PAGE_LENGTH * phyNum);
}

void readFromSecondMemory(char primary_memory[], int logic)
{
    int address = Logic2Phy(logic);
    memcpy(&primary_memory[address], &second_memory[logic * PAGE_LENGTH], PAGE_LENGTH);
}

void showList(char list[], int number)
{
    for (int i = 0; i < number; i++)
    {
        printf("%c", list[i]);
    }
    printf("\n");
}

void initializeList(int list[], int number)
{
    for (int i = 0; i < number; i++)
    {
        list[i] = -1;
    }
}

void showMemoryList(int list[], int phyBlockNum)
{
    for (int i = 0; i < phyBlockNum; i++)
    {
        if (list[i] == -1)
        {
            break;
        }
        printf(" |%d|", list[i]);
    }
    printf("\n");
}

void informationCount(int missingCount, int replaceCount, int pageNum)
{
    printf("Page fault:%d   Page fault ratio:%d/%d\n", missingCount, missingCount, pageNum);
    double result = (double)(pageNum - missingCount) / (double)pageNum;
    printf("Replacement:%d  Hit ratio:%.2f\n", replaceCount, result);
}

void replacePageByFIFO(int memoryList[], char primary_memory[], int phyNum, int strList[], int pageNum)
{

       int replaceCount = 0;
       int missingCount = 0;

       int pointer = 0;

       int isVisited = 0;
    for (int i = 0; i < pageNum; i++)
    {
        isVisited = 0;

               for (int j = 0; j < phyNum; j++)
        {
            if (memoryList[j] == strList[i])
            {
                                              isVisited = 1;
                                              printf("%d\n", strList[i]);
                break;
            }
            if (memoryList[j] == -1)
            {
                               memoryList[j] = strList[i];
                page_table[strList[i]] = j;
                readFromSecondMemory(primary_memory, memoryList[j]);

                               isVisited = 1;
                missingCount++;
                               printf("%d\n", strList[i]);
                showMemoryList(memoryList, phyNum);
                break;
            }
        }

        if (!isVisited)
        {
                                  memoryList[pointer] = strList[i];
            page_table[strList[i]] = pointer;
            readFromSecondMemory(primary_memory, memoryList[pointer]);

                       pointer++;

                       if (pointer > phyNum - 1)
            {
                pointer = 0;
            }

            missingCount++;
            replaceCount++;

                       printf("%d\n", strList[i]);
            showMemoryList(memoryList, phyNum);
        }
        read(primary_memory, strList[i], phyNum);
    }
    informationCount(missingCount, replaceCount, pageNum);
}

void replacePageByLRU(int memoryList[], char primary_memory[], int phyNum, int strList[], int pageNum)
{

       int replaceCount = 0;
       int missingCount = 0;

       int timeRecord[phyNum];
       initializeList(timeRecord, phyNum);

       int isVisited = 0;

       int pageCount = 0;
    for (int i = 0; i < pageNum; i++)
    {
        isVisited = 0;

               for (int p = 0; p < pageCount; p++)
        {
            if (memoryList[p] != -1)
            {
                timeRecord[p]++;
            }
        }

               for (int j = 0; j < phyNum; j++)
        {
            if (memoryList[j] == strList[i])
            {
                                              isVisited = 1;
                               timeRecord[j] = -1;
                               printf("%d\n", strList[i]);
                break;
            }
            if (memoryList[j] == -1)
            {
                               memoryList[j] = strList[i];
                page_table[strList[i]] = j;
                readFromSecondMemory(primary_memory, memoryList[j]);

                pageCount++;
                               isVisited = 1;
                               timeRecord[j]++;

                missingCount++;
                               printf("%d\n", strList[i]);
                showMemoryList(memoryList, phyNum);
                break;
            }
        }

        if (!isVisited)
        {
                                  int max = 0;
            for (int k = 0; k < phyNum; k++)
            {
                if (timeRecord[max] < timeRecord[k])
                {
                    max = k;
                }
            }

                       memoryList[max] = strList[i];
            page_table[strList[i]] = max;
            readFromSecondMemory(primary_memory, memoryList[max]);

            timeRecord[max] = -1;

            missingCount++;
            replaceCount++;

                       printf("%d\n", strList[i]);
            showMemoryList(memoryList, phyNum);
        }
        read(primary_memory, strList[i], phyNum);
    }
    informationCount(missingCount, replaceCount, pageNum);
}

int main(int argc, const char *argv[])
{

    int phyBlockNum;
    printf("Block num:\n");
    scanf("%d", &phyBlockNum);

    int memoryList[phyBlockNum];
    initializeList(memoryList, phyBlockNum);
   
    char primary_memory[phyBlockNum * PAGE_LENGTH];
    initializeList(primary_memory, phyBlockNum * PAGE_LENGTH);

    init();
    showMemoryList(page_table, PAGE_NUM);
    showList(second_memory, PAGE_NUM * PAGE_LENGTH);

    int pageNum;
    printf("Page num:\n");
    scanf("%d", &pageNum);

    int pageNumStrList[pageNum];
    printf("Pages to visit?:\n");
    for (int i = 0; i < pageNum; i++)
    {
        scanf("%d", &pageNumStrList[i]);
    }
    printf("\n");
    int chose;
    while (1)
    {
        printf("Choose your algorithm:\n");
        printf("1.FIFO 2.LRU 3.exit\n");
        scanf("%d", &chose);
        switch (chose)
        {
        case 1:
            replacePageByFIFO(memoryList, primary_memory, phyBlockNum, pageNumStrList, pageNum);
            initializeList(memoryList, phyBlockNum);
            printf("\n");

            break;
        case 2:
            replacePageByLRU(memoryList, primary_memory, phyBlockNum, pageNumStrList, pageNum);
            initializeList(memoryList, phyBlockNum);
            printf("\n");
            break;
        default:
            return 0;
            break;
        }
    }

    return 0;
}
