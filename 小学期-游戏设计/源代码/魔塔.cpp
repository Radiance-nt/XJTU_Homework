#include <stdio.h>
#include <conio.h>
#include <cmath	>
#include <ctime>
#include <graphics.h>
#include <time.h>
#include <windows.h>
#include "��������.h"
#include "�ذ�����.h"
#include "�������.h"
#include "�滭����.h"
#include "�������.h"
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")
#define WalkSpeed 8



// ��Ǯ  �� �� �� ��������ʥ�񣩽� ��  7����ʼ�
static int Knight_index = 21, Knight_x, Knight_y, Knight_row, Knight_col, max_z = 1, min_z = 1, buy_n = 1,
 Knight_Possessions[20], Knight_Value[3] , Knight_z = 1;

int flag[5] ;
int lou, hang, lie, textboxflag,shopboxflag, monsterguidflag, Opeflag;
ID Matrix[50][13][13];
clock_t clo1, clo2;
//����xy�����bug
TCHAR info[30];

void music() {
	mciSendString(_T("open \".\\audio\\music.mp3\" alias mymusic"), NULL, 0, NULL);
	mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);
}


int WhetherCanWinBattle(ID* ptr) {

	int K_health = Knight_Value[0];
	int K_offense = Knight_Value[1];
	int K_defense = Knight_Value[2];
	int M_health = ptr->health;
	int M_offense = ptr->offense;
	int M_defense = ptr->defense;
	while (1)
	{
		M_health = M_health - K_offense + M_defense;
		if (M_health <= 0) {return K_health;}    //Ϊ�˹����ֲ���ʾ��Ѫ���Ĺ���û���ò�����
		K_health = K_health - M_offense + K_defense;
		if (K_health <= 0) { return 0; }
	}
}
bool WhetherCanGo(ID* p) {
	if (p->FloorType == 0) {
		_sntprintf_s(info, sizeof(info), _T("����㿨���ˣ���r����������ϷŶ"));
		return true;
	}
		

	else if ((p->FloorType ==2) & (WhetherCanWinBattle(p)!=0))
	{
		_sntprintf_s(info, sizeof(info), _T("����㿨���ˣ���r����������ϷŶ"));
		return true;
	}
	else if ((p->FloorType == 2) & (WhetherCanWinBattle(p) == 0)) {
		_sntprintf_s(info, sizeof(info), _T("���Ѫ�����ͣ������������ᵼ��������"));
		return false;
	}
	else
		return false;
}
void Battle(ID *ptr) {
	if (ptr->FloorType == 2) {
		int K_health = Knight_Value[0];
		int K_offense = Knight_Value[1];
		int K_defense = Knight_Value[2];
		int M_health = ptr->health;
		int M_offense = ptr->offense;
		int M_defense = ptr->defense;
		while (1)
		{
			M_health = M_health - Knight_Value[1] + M_defense;
			if (M_health <= 0) {
				M_health = 0;
				Knight_Possessions[0] += ptr->money;
				_sntprintf_s(info, sizeof(info), _T("%s�������ˣ�������%d���"), ptr->name,ptr->money);//ptr->name

				ptr->ChangeID(0);
				break;
			}
			Knight_Value[0] = Knight_Value[0] - M_offense + Knight_Value[2];
			  if (Knight_Value[0] <= 0) { break; }
			  Draw();
			  if (((clo2 - clo1) % 800) < (200))  DrawKnight();
			  else if (((clo2 - clo1) % 800) > (600)) DrawOneSquare(15, 10, 1, Knight_x, Knight_y);
			   else if (((clo2 - clo1) % 800 > 200)& ((clo2 - clo1) % 800 <400))
			  DrawOneSquare(15, 10, 1, Knight_x, Knight_y);
			  else
			  { DrawOneSquare(ptr->Row, ptr->Column, ptr->shape, Knight_x, Knight_y); }
			  FlushBatchDraw();
			  Sleep(100);
		}
	}
}

bool talk() {
	char c2;
	textboxflag = 1;
	while (1) {
		if (_kbhit()) {
			c2 = _getch();
			if (c2 == 'y') { textboxflag = 0; textboxflag = 0; return true; }
			  //��draw:textbox��������
			if ((c2 == 'n') | (c2 == ' ')) {
				textboxflag = 0; return false;
			}
		}
		Draw();
	}
}

void OpenMonsterGuides() {
	char c2;
	textboxflag = 1;
	monsterguidflag = 1;
	_sntprintf_s(ManyText, sizeof(ManyText), L" ");
	while (1) {
		if (_kbhit()) {
			c2 = _getch();
			textboxflag = 0;
			monsterguidflag = 0;
			return ;
		}
		Draw();
	}
}

void shop() {
	char c2;
	shopboxflag = 1;
	while (1) {
		int UseMoney;
		UseMoney=10 * buy_n * (buy_n - 1) + 20;
		_sntprintf_s(ManyText, sizeof(ManyText), L"�̵�\n\n\n����%d�����\n\n��������1���200����\n\n��������2����2�㹥��\n\n��������3����2�����\n\n��������4�˳�", UseMoney);
		if (_kbhit()) {
			c2 = _getch();
			if (c2 == '1') { 
				if(Knight_Possessions[0]>=UseMoney){
				Knight_Possessions[0] -= UseMoney;
				 buy_n += 1;
				Knight_Value[0] += 200;
			}
				else
				{
					_sntprintf_s(info, sizeof(info), L"��Ľ�Ҳ���");
				}
				shopboxflag = 0;
				break;
			}
			if (c2 == '2') {
				if (Knight_Possessions[0] >= UseMoney) {
					Knight_Possessions[0] -= UseMoney;
					buy_n += 1;
					Knight_Value[1] += 2;
				}
				else
				{
					_sntprintf_s(info, sizeof(info), L"��Ľ�Ҳ���");
				}
				shopboxflag = 0;
				break;
			}
			if (c2 == '3') {
				if (Knight_Possessions[0] >= UseMoney) {
					Knight_Possessions[0] -= UseMoney;
					buy_n += 1;
					Knight_Value[2] += 2;
				}
				else
				{
					_sntprintf_s(info, sizeof(info), L"��Ľ�Ҳ���");
				}
				shopboxflag = 0;
				break;
			}
			if (c2 == '4') {
				shopboxflag = 0;
				break;
			}
		}
		Draw();
	}

}

void reCalculatexy() {
	Knight_x = (32 * (3 + Knight_col)) - 16;
	Knight_y = 32 * (Knight_row - 1);
}

void move(int operNum) {   //  8 4 6 2
	//�Ƿ���
	ID* ptr = Matrix[Knight_z][0];
	switch (operNum)
	{
	case 8:
		ptr = &Matrix[Knight_z][Knight_row - 2][Knight_col - 1];
		break;
	case 2:
		ptr = &Matrix[Knight_z][Knight_row][Knight_col - 1];
		break;
	case 4:
		ptr = &Matrix[Knight_z][Knight_row - 1][Knight_col - 2];
		break;
	case 6:
		ptr = &Matrix[Knight_z][Knight_row - 1][Knight_col];
		break;
	case 88:
		Knight_z++;
		for (hang = 0; hang < 13; hang++) {
			for (lie = 0; lie < 13; lie++) {
				if (Matrix[Knight_z][hang][lie].ObjectType == -3) {
					Knight_col = lie + 1; Knight_row = hang + 1;
					break;
				}
			}
		}
		reCalculatexy();
		break;
	case 22:
		Knight_z--;
		for (hang = 0; hang < 13; hang++) {
			for (lie = 0; lie < 13; lie++) {
				if (Matrix[Knight_z][hang][lie].ObjectType == -2) {
					Knight_col = lie + 1; Knight_row = hang + 1;
					break;
				}
			}
		}
		reCalculatexy();
		break;
	}
	BeginBatchDraw();
	switch (operNum)
	{
	case 8:
		if ((Knight_index / 10) != 8)Knight_index = 81;
		if (WhetherCanGo(ptr)) {
			Knight_row -= 1;
			for (int i = 0; i < 32; i += WalkSpeed) {
				Knight_y -= WalkSpeed;
				if ((Knight_index % 10) != 3)Knight_index += 1;
				else Knight_index -= 2;
				Draw();
				Sleep(10);
			}Battle(ptr);
		}
		else {
			OpenDoor(ptr);
		}
		break;
	case 2:
		if ((Knight_index / 10) != 2)Knight_index = 21;
		if (WhetherCanGo(ptr)) {

			Knight_row += 1;
			for (int i = 0; i < 32; i += WalkSpeed) {
				Knight_y += WalkSpeed;
				if ((Knight_index % 10) != 3)Knight_index += 1;
				else Knight_index -= 2;
				Draw();
				Sleep(10);
			}Battle(ptr);
		}
		else {
			OpenDoor(ptr);
		}
		break;
	case 4:
		if ((Knight_index / 10) != 4)Knight_index = 41;
		if (WhetherCanGo(ptr)) {
			Knight_col -= 1;
			for (int i = 0; i < 32; i += WalkSpeed) {
				Knight_x -= WalkSpeed;
				if ((Knight_index % 10) != 3)Knight_index += 1;
				else Knight_index -= 2;
				Draw();
				Sleep(10);
			}
			Battle(ptr);
		}
		else {
			OpenDoor(ptr);
		}
		break;
	case 6:
		if ((Knight_index / 10) != 6)Knight_index = 61;
		if (WhetherCanGo(ptr)) {
			Knight_col += 1;
			for (int i = 0; i < 32; i += WalkSpeed) {
				Knight_x += WalkSpeed;
				if ((Knight_index % 10) != 3)Knight_index += 1;
				else Knight_index -= 2;
				Draw();
				Sleep(10);
			}
			Battle(ptr);
		}
		else {
			OpenDoor(ptr);
		}
		break;
	}
	SpecialAction();
	GetObject(ptr);
	Draw();
	Sleep(10);

}

void KeyDown()
{
	void reboot();
	char c;
	while (1)
	{
		
		if (_kbhit())
		{
			c = _getch();
			switch (c)
			{
			case 'a':
			case 'A':
			case 75:
				move(4);
				break;
			case 'w':
			case 'W':
			case 72:
				move(8);
				break;
			case 'd':
			case 'D':
			case 77:
				move(6);
				break;
			case 's':
			case 'S':
			case 80:
				move(2);
				break;
			case ']':
				if (Knight_Possessions[7]==1){
					if ((Matrix[Knight_z][Knight_row - 1][Knight_col - 1].ObjectType != -3) && (Matrix[Knight_z][Knight_row - 1][Knight_col - 1].ObjectType != -2))
					{
						_sntprintf_s(info, sizeof(info), _T("�������¥����ʹ��")); break;
					}
				if (Knight_z < max_z )
					move(88);
				else
					_sntprintf_s(info, sizeof(info), _T("�����㵽������¥��"));
				}
				break;
			case '[':
				if (Knight_Possessions[7] == 1) {
					if ((Matrix[Knight_z][Knight_row - 1][Knight_col - 1].ObjectType != -3) && (Matrix[Knight_z][Knight_row - 1][Knight_col - 1].ObjectType != -2))
					{
						_sntprintf_s(info, sizeof(info), _T("�������¥����ʹ��"));
						break;
					}
					if (Knight_z > 1)
						move(22);
					else
						_sntprintf_s(info, sizeof(info), _T("���Ѿ�����ײ�"));
				}
				break;
			case 'h':
			//case 'H':
				if (Knight_Possessions[6]==1)
				OpenMonsterGuides();
				break;


			case 'r':
				reboot();
				_sntprintf_s(info, sizeof(info), _T("��Ϸ������"));
				break;
			}
		}
		move(0);
		
	}
}

void reboot() {SetMatrix();
	int temp_P[20] = { 0,0,0,0,-19,-20 ,0 }, temp_V[3] = { 1000,100,100 }, temp_F[5] = { 1,1,1,1,1 };
	Creat();
	Knight_row = 12;
	Knight_col = 7;
	reCalculatexy();
	SetMatrix();
	Creat();
	max_z = 1, min_z = 1, buy_n = 1; Knight_index = 21; Knight_z =1;
	memcpy(flag, temp_F, sizeof(temp_F)); memcpy(Knight_Possessions, temp_P, sizeof(temp_P)); memcpy(Knight_Value, temp_V, sizeof(temp_V));
	_sntprintf_s(info, sizeof(info), _T("����㿨���ˣ���r����������ϷŶ"));
}

int main() {
	initgraph(20*32, 13*32+24);
	SetWindowText(GetHWnd(), _T("ħ��"));
	music();
	initResource();
	clo1 = clock();
	InitText();
	InitRC();
	reboot();
	BeginBatchDraw();
	_sntprintf_s(ManyText, sizeof(ManyText), L"��ӭ����ħ����Ϸ\nħ����Ϸ���������������ڶ�\n�����ѶȲ��ͣ���������һ�μ�޵Ŀ���\n�����ϲ����ս����һ����Ҫ�����\n\n\n\n\n\n���ո����...");
	talk();
	FlushBatchDraw();
	KeyDown();
	_getch();
	closegraph();
	return 0;
}

