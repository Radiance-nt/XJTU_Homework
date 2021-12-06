#include <iostream>
using namespace std;

#define MAXLISTSIZE 10000
#define MAXSTEPSIZE 100

/*
定义八数码节点结构体
status存储节点的状态（即八数码的排列），G存储走的是第几步，H存储不在位的将牌数，F存储总耗散值，Zero存储‘0’将牌所在位置，
step存储该节点是上一节点通过怎样的移动得到的（1左2右3上4下）
*/
struct ENode
{
    int status[9];
    int G;
    int H;
    int F;
    int Zero;
    int step;
    ENode *Parent;
};

//最终状态
int FinalStatus[9] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };

//定义OPEN表和CLOSE表,open和close是表中最后一个内容的下一位序号
ENode OPEN[MAXLISTSIZE];
ENode CLOSE[MAXLISTSIZE];
int open = 0;
int close = 0;

ENode *Node;

/*
计算不在位的将牌数H
返回 H
*/
int CountH(int *status)
{
    int H = 0;
    int i;
    for (i = 0; i <= 8; i++)
    {
        if (FinalStatus[i] != status[i])
        {
            H++;
        }
    }
    return H;
}

/*
判断新生成的节点是否已经存在于OPEN表或CLOSE表中
返回 表征是否存在于OPEN或CLOSE的值，值为0 均不在，值>0 只在OPEN表，值<0 只在CLOSE表，|值|-1表示所在列表中的位置
*/
int Exist(ENode *N)
{
    int i, j;
    int H = 0;                      //计算不在位的将牌数，如果为0，则证明给函数的节点在表中已存在
    int status[9];

    Node = new ENode;
    Node = N;

    for (i = 0; i <= 8; i++)
    {
        status[i] = Node->status[i];
    }

    for (i = 0; i <= open - 1; i++)     //判断是否在OPEN表
    {
        for (j = 0; j <= 8; j++)
        {
            if (status[j] != OPEN[i].status[j])
            {
                H++;
            }
        }

        if (H == 0)                 //H=0证明在表中找到该节点
        {
            return i + 1;           //如果在OPEN表中，返回i（节点在OPEN的位置）+ 1（在OPEN找到该节点）
        }
        H = 0;                      //扫描完一个节点后重置H
    }

    for (i = 0; i <= close - 1; i++)     //判断是否在CLOSE表
    {
        for (j = 0; j <= 8; j++)
        {
            if (status[j] != CLOSE[i].status[j])
            {
                H++;
            }
        }

        if (H == 0)                 //H=0证明在表中找到该节点
        {
            return (-i) - 1;        //如果在CLOSE表中，返回-i（i为节点在CLOSE的位置）- 1（在CLOSE找到该节点）
        }
        H = 0;                      //扫描完一个节点后重置H
    }

    return 0;
}

/*
初始化节点
返回 初始化后的节点Node
*/
ENode *ENodeInit(int *status, int zero, int g, ENode *parent, int step)
{
    int i;
    Node = new ENode;
    for (i = 0; i <= 8; i++)
    {
        Node->status[i] = status[i];
    }
    Node->Zero = zero;
    Node->G = g;
    Node->H = CountH(Node->status);
    Node->F = Node->G + Node->H;
    Node->Parent = parent;
    Node->step = step;
    return Node;
}

/*
左移后的变化
返回 左移后的状态
*/
int *Left(int *s, int z)
{
    int temp, i;
    static int status[9];
    for (i = 0; i <= 8; i++)
    {
        status[i] = s[i];
    }
    temp = status[z - 1];
    status[z - 1] = 0;
    status[z] = temp;
    return status;
}

/*
右移后的变化
返回 右移后的状态
*/
int *Right(int *s, int z)
{
    int temp, i;
    static int status[9];
    for (i = 0; i <= 8; i++)
    {
        status[i] = s[i];
    }
    temp = status[z + 1];
    status[z + 1] = 0;
    status[z] = temp;
    return status;
}

/*
上移后的变化
返回 上移后的状态
*/
int *Up(int *s, int z)
{
    int temp, i;
    static int status[9];
    for (i = 0; i <= 8; i++)
    {
        status[i] = s[i];
    }
    temp = status[z - 3];
    status[z - 3] = 0;
    status[z] = temp;
    return status;
}

/*
下移后的变化
返回 下移后的状态
*/
int *Down(int *s, int z)
{
    int temp, i;
    static int status[9];
    for (i = 0; i <= 8; i++)
    {
        status[i] = s[i];
    }
    temp = status[z + 3];
    status[z + 3] = 0;
    status[z] = temp;
    return status;
}

/*
判断子节点是否在OPEN或CLOSE中，并进行对应的操作
返回值 NULL
*/
void ExistAndOperate(ENode *N)
{
    int i;
    int inList;                 //定义表示新生成节点是否在OPEN表或CLOSE表中, 值为0 均不在，值>0 只在OPEN表，值<0 只在CLOSE表

    Node = new ENode;
    Node = N;

    if (Node->G == 1)           //如果是第一步的节点，直接加入OPEN中，返回
    {
        OPEN[open] = *Node;
        open++;
        return;
    }

    inList = Exist(Node);       //判断新节点是否在OPEN或CLOSE中

    if (inList == 0)            //如果均不在两个表中，将节点加入OPEN表中
    {
        OPEN[open] = *Node;      //将拓展出的新结点加入到OPEN表中
        open++;
    }

    else if (inList > 0)             //如果在OPEN中，说明从初始节点到该节点找到了两条路径，保留耗散值短的那条路径
    {
        if (OPEN[inList - 1].F > Node->F)    //如果表内节点F值大于新节点F值，用新节点代替表内节点
        {
            OPEN[inList - 1] = *Node;
        }
    }

    else if (inList < 0)             //如果在CLOSE中，说明初始节点到该节点有两条路径，如果新找到的路径耗散值大，什么都不做，如果较小，将其从CLOSE中取出放入OPEN中    
    {
        inList = -inList;
        if (CLOSE[inList - 1].F > Node->F)       //如果较小
        {
            OPEN[open] = *Node;       //将其取出放入OPEN
            open++;
        }
        for (i = inList - 1; i <= close - 1; i++)     //将其在CLOSE中释放
        {
            CLOSE[i] = CLOSE[i + 1];
        }
        close--;
    }
}

/*
寻找最佳路径函数
返回 最后的节点Node
*/
ENode *Search()
{
    int *status;
    int i, j;

    ENode *Temp;

    while (1)                   //一直循环知道找到解结束
    {
        Temp = new ENode;
       
        for (i = open - 1; i > 0; i--)    //用冒泡排序给OPEN表里面的节点按耗散值进行排序
        {
            for (j = 0; j < i; j++)
            {
                if (OPEN[j].F > OPEN[j + 1].F)
                {
                    *Temp = OPEN[j + 1];
                    OPEN[j + 1] = OPEN[j];
                    OPEN[j] = *Temp;
                }
            }
        }

        Node = new ENode;
        *Node = OPEN[0];                 //从OPEN表中取出第一个元素（F值最小）进行扩展

        if (!CountH(Node->status))      //判断该节点是否是目标节点，若是，则不在位的将牌数为0，算法结束
        {
            break;
        }

        Temp = Node;
        CLOSE[close] = *Node;            //将扩展过的节点放入CLOSE    
        close++;
        for (i = 0; i <= open - 1; i++) //将扩展的节点从OPEN中释放
        {
            OPEN[i] = OPEN[i + 1];
        }
        open--;

        if ((Temp->Zero) % 3 >= 1)        //如果能左移，则进行左移创造新结点    
        {
            Node = new ENode;                                           //创造新结点
            status = Left(Temp->status, Temp->Zero);                   //得到新的状态
            Node = ENodeInit(status, Temp->Zero - 1, (Temp->G) + 1, Temp, 1);    //初始化新结点
            ExistAndOperate(Node);      //判断子节点是否在OPEN或CLOSE中，并进行对应的操作
        }

        if ((Temp->Zero) % 3 <= 1)        //如果能右移，则进行右移创造新结点    
        {
            Node = new ENode;                                           //创造新结点
            status = Right(Temp->status, Temp->Zero);                   //得到新的状态
            Node = ENodeInit(status, Temp->Zero + 1, (Temp->G) + 1, Temp, 2);    //初始化新结点
            ExistAndOperate(Node);      //判断子节点是否在OPEN或CLOSE中，并进行对应的操作
        }

        if (Temp->Zero >= 3)            //如果能上移，则进行上移创造新结点    
        {
            Node = new ENode;                                           //创造新结点
            status = Up(Temp->status, Temp->Zero);                   //得到新的状态
            Node = ENodeInit(status, Temp->Zero - 3, (Temp->G) + 1, Temp, 3);    //初始化新结点
            ExistAndOperate(Node);      //判断子节点是否在OPEN或CLOSE中，并进行对应的操作
        }

        if (Temp->Zero <= 5)            //如果能下移，则进行下移创造新结点    
        {
            Node = new ENode;                                           //创造新结点
            status = Down(Temp->status, Temp->Zero);                   //得到新的状态
            Node = ENodeInit(status, Temp->Zero + 3, (Temp->G) + 1, Temp, 4);    //初始化新结点
            ExistAndOperate(Node);      //判断子节点是否在OPEN或CLOSE中，并进行对应的操作
        }

        if (open == 0)                  //如果open=0， 证明算法失败， 没有解
            return NULL;
    }
    return Node;
}

/*
展示具体步骤
返回 NULL
*/
void ShowStep(ENode *Node)
{
    int STEP[MAXSTEPSIZE];
    int STATUS[MAXSTEPSIZE][9];
    int step = 0;
    int i, j;
    int totalStep = Node->G;
    while (Node)
    {
        STEP[step] = Node->step;
        for (i = 0; i <= 8; i++)
        {
            STATUS[step][i] = Node->status[i];
        }
        step++;
        Node = Node->Parent;
    }
    cout << "----------------------" << endl;
    cout << totalStep << endl;
    cout << "----------------------" << endl;
    for (i = step - 1; i >= 0; i--)
    {
        if (STEP[i] == 1)
            cout << "left";
        else if (STEP[i] == 2)
            cout << "right";
        else if (STEP[i] == 3)
            cout << "up";
        else if (STEP[i] == 4)
            cout << "down";
        else if (STEP[i] == 0)
            cout << "START";
        cout << " ";
    }
    cout << endl << "----------------------" << endl;
    for (i = step - 1; i >= 0; i--)
    {
        for (j = 0; j <= 8; j++)
        {
            cout << STATUS[i][j];
            if (j == 2 || j == 5 || j == 8)
                cout << endl;
            else
                cout << " ";
        }
        cout << "----------------------" << endl;
    }
}

/*
主函数
返回 0
*/
int main()
{
    int fstatus[9];
    int i;
    ENode *FNode;
    ENode *EndNode;

    for (i = 0; i <= 8; i++)                    //输入初始状态
    {
        cin >> fstatus[i];
    }

    for (i = 0; i <= 8; i++)                    //判断0节点位置
    {
        if (fstatus[i] == 0)
            break;
    }

    FNode = ENodeInit(fstatus, i, 0, NULL, 0);  //获得初始节点

    OPEN[open] = *FNode;                         //将初始节点放入OPEN中
    open++;
    EndNode = Search();                         //寻找最佳路径

    if (!EndNode)
        cout << "无解" << endl;
    else
        ShowStep(EndNode);                      //展示步骤

    return 0;
}

