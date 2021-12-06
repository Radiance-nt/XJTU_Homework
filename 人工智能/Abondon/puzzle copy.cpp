#include <stdio.h>
#include <string.h>

long int fac[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; //阶乘表

unsigned char step[363880] = {0}; // 9!=362880,所以数组要大点

char method[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; //4种移动方法

struct node_t
{
	unsigned char data[9];
	unsigned int step_p;
};

struct node_t save_step[363880]; //保存移动数据,最多有 9!个移动数据

unsigned char end_p[9]; //终点坐标

unsigned int end_index; //记录终点位置

int congtuo(unsigned char s[], int n)
{
	int i, j, temp, num;
	num = 0;
	for (i = 0; i < n; i++)
	{
		temp = 0;
		for (int j = i + 1; j < n; j++)
			if (s[j] < s[i]) //判断几个数小于它
				temp++;
		num += fac[n - i - 1] * temp;
	}
	return num;
}

/*处理0函数
 *返回值0:交换的位置非法,或被走过
 *返回值1:没被走过
 *返回值2:找到终点
 */
int handler_zero(int i, unsigned char data[])
{
	int x, y, temp, num;

	for (int j = 0; j < 9; j++)
		if (data[j] == 0)
		{
			/*[x,y]:需要交换的位置*/
			x = j % 3 + method[i][0];
			y = j / 3 + method[i][1];

			/*判断交换位置是否越界*/
			if (x < 0 || x > 2)
				return 0;
			else if (y < 0 || y > 2)
				return 0;

			/*判断交换后的位置是否已被走过*/
			data[j] = data[x + y * 3];
			data[x + y * 3] = 0;
			num = congtuo(data, 9);
			if (step[num] == 1) //已被走过
			{
				return 0;
			}

			if (memcmp(end_p, data, 9) == 0) //找到终点
			{
				return 2;
			}

			step[num] = 1;
			return 1;
		}
}

int start = 0, end = 0;
int bfs(void)
{
	int x, y;
	int next_end = end; //存放下次bfs的end标志位
	int err;
	unsigned char temp[9];
	if (start == end)
		return 9999;
	for (; start <= end; start++)
	{
		for (int i = 0; i < 4; i++) //4种走法
		{
			memcpy(temp, (unsigned char *)save_step[start].data, 9);

			err = handler_zero(i, temp); //处理数据里的0

			if (err) //保存数据
			{
				memcpy((unsigned char *)save_step[++next_end].data, temp, 9);

				save_step[next_end].step_p = start; //记录上次步数位置.

				if (err == 2) //找到终点
				{
					end_index = next_end; //记录终点步数位置.
					return 1;
				}
			}
		}
	}
	start = end + 1;
	end = next_end;
	return (1 + bfs());
}


int Astar(void)
{
	int x, y;
	int next_end = end; //存放下次bfs的end标志位
	int err;
	unsigned char temp[9];
	if (start == end)
		return 9999;
	for (; start <= end; start++)
	{
		for (int i = 0; i < 4; i++) //4种走法
		{
			memcpy(temp, (unsigned char *)save_step[start].data, 9);

			err = handler_zero(i, temp); //处理数据里的0

			if (err) //保存数据
			{
				memcpy((unsigned char *)save_step[++next_end].data, temp, 9);

				save_step[next_end].step_p = start; //记录上次步数位置.

				if (err == 2) //找到终点
				{
					end_index = next_end; //记录终点步数位置.
					return 1;
				}
			}
		}
	}
	start = end + 1;
	end = next_end;
	return (1 + bfs());
}

void print_Matrix()
{
	for (int i = 0; i < 3; i++)
	{
		printf("%d %d %d\n", save_step[end_index].data[i * 3],
			   save_step[end_index].data[i * 3 + 1],
			   save_step[end_index].data[i * 3 + 2]);
	}
}
int main()
{
	int step_num = 0; //步数
	unsigned char s[9];

	printf("please enter  start point:\r\n");
	for (int i = 0; i < 9; i++)
	{
		scanf("%1d", &save_step[0].data[i]);
	}

	printf("please enter  end point:\r\n");
	for (int i = 0; i < 9; i++)
	{
		scanf("%1d", &end_p[i]);
	}

	step_num = bfs();
	if (step_num > 999)
		printf("%d\n", step_num);
	else
	{
		printf("%d\n", step_num);

		/**打印步数具体内容**/
		for (; step_num >= 0; step_num--)
		{
			printf("**step %d********\n", step_num);
			print_Matrix();
			end_index = save_step[end_index].step_p;
			printf("\n");
		}
	}
}