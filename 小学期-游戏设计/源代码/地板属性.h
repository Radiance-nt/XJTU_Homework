#pragma once
#include <stdio.h>
#include <conio.h>
#include <cmath	>
#include <ctime>
#include <string>
using namespace std;
int MonsterInfo[31][4] = { {0,0,0,0},{35,18,1,1} ,{45,20,2,2},{130,60,3,8},{35, 38, 3, 3 },{ 60, 100, 8 ,12 },
{50, 42, 6 ,6 },{55, 52 ,12, 8 },{100 ,65, 15, 30 },{60, 32, 8, 5 },{100, 95, 30, 22},
{260, 85, 5 ,18 },{320, 120, 15, 30 },{ 20, 100, 68, 28},{0,0,0,0},{360, 310 ,20, 40 } ,
{220, 370 ,110, 80 },{200 ,380 ,130, 90 },{50,48 ,22 ,12 },{100 ,180 ,110 ,100} };
//MonsterInfo[1] = { 20,3,2,2 };

class ID
{
public:
	ID();
	void ChangeID(int GiveID);
	void SetMonster(int GiveID);
	void SetObject(int GiveID);
	int FloorType;       //0Ϊ�ذ�  1Ϊǽ�ڻ���  2Ϊ����
	int ObjectType;       //-2Ϊ��¥  -3Ϊ��¥   0Ϊ��   1Ϊ��Կ�� 2Ϊ��Կ�� 3Ϊ��Կ�� 4Ϊ��ҩˮ 5Ϊ��ҩˮ 6Ϊ�챦ʯ 7Ϊ����ʯ    
	int DoorType;	//0Ϊ��     1Ϊ��   2Ϊ��  3Ϊ��  4Ϊ��    -5Ϊ�̵�     6Ϊ����ү   7Ϊ����  8ΪС͵  9Ϊ��ǽ
	int MonsterType;  //0Ϊ��  1Ϊ��ɫʷ��ķ  2Ϊ��ɫʷ��ķ	 3Ϊ����ʷ��ķ  4ΪС����  5Ϊ������
							 //6Ϊ���ñ�  7Ϊ����սʿ 8Ϊ���öӳ�  9Ϊ��ʦ  10Ϊ�߼���ʦ
							 //29Ϊħ������ 30Ϊħ��	
	int Row, Column, shape;
	TCHAR name[30];
	int health = NULL;
	int offense = NULL;
	int defense = NULL;
	int money = NULL;
};

void SetValues(int FloorType ,int ObjectType,int DoorOrMonsterType,int Row ,int Column ,int  shape,ID *ptr) {
	ptr->FloorType = FloorType;
	ptr->ObjectType = ObjectType;
	if (FloorType == 1) {
		ptr->DoorType = DoorOrMonsterType;
	}
	if (FloorType == 2) {
		ptr->MonsterType = DoorOrMonsterType;
	}
	ptr->Row = Row;
	ptr->Column = Column;
	ptr->shape = shape;
}

void ID::ChangeID(int GiveID)  //��ʼ������ ��id�õ���������������Ϣ
{
	this->MonsterType = 0;
	switch (GiveID)
	{
	case -2:  //��¥
		SetValues(0, -2, 0, 17, 4, 1, this);
		break;
	case -3:   //��¥
		SetValues(0, -3, 0, 17, 3, 1, this);
		break;
	case 0:
		SetValues(0, 0, 0, 17, 10, 1, this);
		break;
	case -1:  //ǽ
		SetValues(1, 0, 0, 17, 1, 1, this);
		break;
	case 1: //����
		SetValues(1, 0, 1, 16, 7, 1, this);
		break;
	case 2:  //����
		SetValues(1, 0, 2, 16, 8, 1, this);
		break;
	case 3:  //����
		SetValues(1, 0, 3, 16, 9, 1, this);
		break;
	case 4:  //��ɫ��
		SetValues(1, 0, 4, 16, 6, 1, this);
		break;
	case 5:  //����
		SetValues(1, 0, 4, 16, 10, 1, this);
		break;
	case 6:  //����
		SetValues(1, 0, 6, 10, 10, 1, this);
		break;
	case 7:  //����
		SetValues(1, 0, 7, 11, 10, 1, this);
		break;
	case 8:  //С͵
		SetValues(1, 0, 8, 11, 8, 1, this);
		break;
	case 9:  //��ǽ
		SetValues(1, 0, 9, 17, 1, 1, this);
		break;
	case -4:  //�̵���
		SetValues(1, 0, -1, 12, 7, 1, this);
		break;
	case -5:  //�̵���
		SetValues(1, 0, -5, 0, 0, 1, this);
		break;
	case -6:  //�̵���
		SetValues(1, 0, -1, 12, 9, 1, this);
		break;

	}
};

void ID::SetMonster(int GiveID) {
	if (GiveID == 0) return;
	if (GiveID % 5 != 0)SetValues(2, 0, GiveID, GiveID / 5 + 1, 2 * (GiveID % 5), 1, this);
	else SetValues(2, 0, GiveID, GiveID / 5, 10, 1, this);
	health = MonsterInfo[GiveID][0];
	offense = MonsterInfo[GiveID][1];
	defense = MonsterInfo[GiveID][2];
	money = MonsterInfo[GiveID][3];
	
	switch (GiveID)
	{//0Ϊ��  1Ϊ��ɫʷ��ķ  2Ϊ��ɫʷ��ķ	 3Ϊ����ʷ��ķ  4ΪС����  5Ϊ������
	 //6Ϊ������  7Ϊ����սʿ 8Ϊ���öӳ�  9Ϊ��ʦ  10Ϊ�߼���ʦ
	 //29Ϊħ������ 30Ϊħ��	

	case 1:_tcscpy_s(name, _T("��ɫʷ��ķ")); break;
	case 2:_tcscpy_s(name, _T("��ɫʷ��ķ")); break;
	case 3:_tcscpy_s(name, _T("����ʷ��ķ")); break;
	case 4:_tcscpy_s(name, _T("С����")); break;
	case 5:_tcscpy_s(name, _T("������")); break;
	case 6:_tcscpy_s(name, _T("������")); break;
	case 7:_tcscpy_s(name, _T("����ʿ��")); break;
	case 8:_tcscpy_s(name, _T("���öӳ�")); break;
	case 9:_tcscpy_s(name, _T("������ʦ")); break;
	case 18:_tcscpy_s(name, _T("��������")); break;
	case 19:_tcscpy_s(name, _T("�м�����")); break;

	}
}

void ID::SetObject(int GiveID) {
	switch (GiveID)
	{
	case 0:
		//SetValues(0, 0, 0, 17, 10, 1, this);
		break;
	case 1: //��Կ��
		SetValues(0, 1, 0, 15, 4, 1, this);
		break;
	case 2: //��Կ��
		SetValues(0, 2, 0, 15, 5, 1, this);
		break;
	case 3:  //��Կ��
		SetValues(0, 3, 0, 15, 6, 1, this);
		break;
	case 4:  //��ҩˮ
		SetValues(0, 4, 0, 14, 4, 1, this);
		break;
	case 5:  //��ҩˮ
		SetValues(0, 5, 0, 14, 5, 1, this);
		break;
	case 6:  //����
		SetValues(0, 6, 0, 13, 4, 1, this);
		break;
	case 7:  //����
		SetValues(0, 7, 0, 13, 5, 1, this);
		break;

	case 8:  //���з���
		SetValues(0, 8, 0, 13, 1, 1, this);
		break;

	case -11:  //����
		SetValues(0, -11, 0, 13, 7, 1, this); break;
	case -12:  //����
		SetValues(0, -12, 0, 14, 7, 1, this); break;
	case -19:  //��ʥ��
		SetValues(0, -19, 0, 15, 8, 1, this); break;
	case -20:  //��ʥ��
		SetValues(0, -20, 0, 15, 9	, 1, this); break;
		break;
	}

}

ID::ID() { //��ʼ��Ϊ�յ�
	FloorType = 0;
	ObjectType = 0;
	Row = 17; Column = 10; shape = 1;
}

