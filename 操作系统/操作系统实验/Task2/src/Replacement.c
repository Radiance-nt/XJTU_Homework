#include <stdio.h>

void initializeList(int list[], int number)
{
    for (int i = 0; i < number; i++)
    {
        list[i] = -1;
    }
}

void showList(int list[], int number)
{
    for (int i = 0; i < number; i++)
    {
        printf("%2d", list[i]);
    }
    printf("\n");
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

int getNextPosition(int currentPage, int currentPosition, int strList[], int pageNum)
{

    for (int i = currentPosition + 1; i < pageNum; i++)
    {
        if (strList[i] == currentPage)
        {
            return i;
        }
    }

    return -1;
}

void replacePageByFIFO(int memoryList[], int phyNum, int strList[], int pageNum)
{

    //置换次数
    int replaceCount = 0;
    //缺页次数
    int missingCount = 0;

    //记录当前最早进入内存的下标
    int pointer = 0;

    //记录当前页面的访问情况: 0 未访问
    int isVisited = 0;
    for (int i = 0; i < pageNum; i++)
    {
        isVisited = 0;

        //判断是否需要置换->内存已满且需要访问的页面不在内存中
        for (int j = 0; j < phyNum; j++)
        {
            if (memoryList[j] == strList[i])
            {
                //该页面已经存在内存中
                //修改访问情况
                isVisited = 1;
                //修改访问时间
                //展示
                printf("%d\n", strList[i]);
                break;
            }
            if (memoryList[j] == -1)
            {
                //页面不在内存中且内存未满->直接存入
                memoryList[j] = strList[i];
                //修改访问情况
                isVisited = 1;
                missingCount++;
                //展示
                printf("%d\n", strList[i]);
                showMemoryList(memoryList, phyNum);
                break;
            }
        }

        if (!isVisited)
        {
            //当前页面还未被访问过->需要进行页面置换
            //直接把这个页面存到所记录的下标中
            memoryList[pointer] = strList[i];

            //下标指向下一个
            pointer++;

            //如果到了最后一个，将下标归零
            if (pointer > phyNum - 1)
            {
                pointer = 0;
            }

            missingCount++;
            replaceCount++;

            //展示
            printf("%d\n", strList[i]);
            showMemoryList(memoryList, phyNum);
        }
    }
    informationCount(missingCount, replaceCount, pageNum);
}

void replacePageByLRU(int memoryList[], int phyNum, int strList[], int pageNum)
{

    //置换次数
    int replaceCount = 0;
    //缺页次数
    int missingCount = 0;

    //记录内存中最近一次访问至今的时间
    int timeRecord[phyNum];
    //初始化
    initializeList(timeRecord, phyNum);

    //记录当前页面的访问情况: 0 未访问
    int isVisited = 0;

    //记录已经在内存中的页面数量
    int pageCount = 0;
    for (int i = 0; i < pageNum; i++)
    {
        isVisited = 0;

        //时间加一
        for (int p = 0; p < pageCount; p++)
        {
            if (memoryList[p] != -1)
            {
                timeRecord[p]++;
            }
        }

        //是否需要置换
        for (int j = 0; j < phyNum; j++)
        {
            if (memoryList[j] == strList[i])
            {
                //该页面已经存在内存中
                //修改访问情况
                isVisited = 1;
                //重置访问时间
                timeRecord[j] = -1;
                //展示
                printf("%d\n", strList[i]);
                break;
            }
            if (memoryList[j] == -1)
            {
                //页面不在内存中且内存未满->直接存入
                memoryList[j] = strList[i];
                pageCount++;
                //修改访问情况
                isVisited = 1;
                //修改访问时间
                timeRecord[j]++;

                missingCount++;
                //展示
                printf("%d\n", strList[i]);
                showMemoryList(memoryList, phyNum);
                break;
            }
        }

        if (!isVisited)
        {
            //需要置换
            //1.遍历时间记录表，寻找最久未访问的页面所在的内存下标
            int max = 0;
            for (int k = 0; k < phyNum; k++)
            {
                if (timeRecord[max] < timeRecord[k])
                {
                    max = k;
                }
            }

            //2.将该位置的页面换出
            memoryList[max] = strList[i];
            timeRecord[max] = -1;

            missingCount++;
            replaceCount++;

            //展示
            printf("%d\n", strList[i]);
            showMemoryList(memoryList, phyNum);
        }
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
            replacePageByFIFO(memoryList, phyBlockNum, pageNumStrList, pageNum);
            initializeList(memoryList, phyBlockNum);
            printf("\n");

            break;
        case 2:
            replacePageByLRU(memoryList, phyBlockNum, pageNumStrList, pageNum);
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
