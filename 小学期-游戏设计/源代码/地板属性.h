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
	int FloorType;       //0为地板  1为墙壁或门  2为怪物
	int ObjectType;       //-2为上楼  -3为下楼   0为空   1为黄钥匙 2为蓝钥匙 3为红钥匙 4为红药水 5为蓝药水 6为红宝石 7为蓝宝石    
	int DoorType;	//0为空     1为黄   2为蓝  3为红  4为青    -5为商店     6为土地爷   7为商人  8为小偷  9为暗墙
	int MonsterType;  //0为空  1为绿色史莱姆  2为红色史莱姆	 3为巨型史莱姆  4为小蝙蝠  5为大蝙蝠
							 //6为骷髅兵  7为骷髅战士 8为骷髅队长  9为巫师  10为高级巫师
							 //29为魔法警卫 30为魔王	
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

void ID::ChangeID(int GiveID)  //初始化函数 由id得到行列其他名称信息
{
	this->MonsterType = 0;
	switch (GiveID)
	{
	case -2:  //上楼
		SetValues(0, -2, 0, 17, 4, 1, this);
		break;
	case -3:   //下楼
		SetValues(0, -3, 0, 17, 3, 1, this);
		break;
	case 0:
		SetValues(0, 0, 0, 17, 10, 1, this);
		break;
	case -1:  //墙
		SetValues(1, 0, 0, 17, 1, 1, this);
		break;
	case 1: //黄门
		SetValues(1, 0, 1, 16, 7, 1, this);
		break;
	case 2:  //蓝门
		SetValues(1, 0, 2, 16, 8, 1, this);
		break;
	case 3:  //红门
		SetValues(1, 0, 3, 16, 9, 1, this);
		break;
	case 4:  //青色门
		SetValues(1, 0, 4, 16, 6, 1, this);
		break;
	case 5:  //牢笼
		SetValues(1, 0, 4, 16, 10, 1, this);
		break;
	case 6:  //土地
		SetValues(1, 0, 6, 10, 10, 1, this);
		break;
	case 7:  //商人
		SetValues(1, 0, 7, 11, 10, 1, this);
		break;
	case 8:  //小偷
		SetValues(1, 0, 8, 11, 8, 1, this);
		break;
	case 9:  //暗墙
		SetValues(1, 0, 9, 17, 1, 1, this);
		break;
	case -4:  //商店左
		SetValues(1, 0, -1, 12, 7, 1, this);
		break;
	case -5:  //商店中
		SetValues(1, 0, -5, 0, 0, 1, this);
		break;
	case -6:  //商店右
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
	{//0为空  1为绿色史莱姆  2为红色史莱姆	 3为巨型史莱姆  4为小蝙蝠  5为大蝙蝠
	 //6为骷髅人  7为骷髅战士 8为骷髅队长  9为巫师  10为高级巫师
	 //29为魔法警卫 30为魔王	

	case 1:_tcscpy_s(name, _T("绿色史莱姆")); break;
	case 2:_tcscpy_s(name, _T("红色史莱姆")); break;
	case 3:_tcscpy_s(name, _T("巨型史莱姆")); break;
	case 4:_tcscpy_s(name, _T("小蝙蝠")); break;
	case 5:_tcscpy_s(name, _T("大蝙蝠")); break;
	case 6:_tcscpy_s(name, _T("骷髅人")); break;
	case 7:_tcscpy_s(name, _T("骷髅士兵")); break;
	case 8:_tcscpy_s(name, _T("骷髅队长")); break;
	case 9:_tcscpy_s(name, _T("初级巫师")); break;
	case 18:_tcscpy_s(name, _T("初级卫兵")); break;
	case 19:_tcscpy_s(name, _T("中级卫兵")); break;

	}
}

void ID::SetObject(int GiveID) {
	switch (GiveID)
	{
	case 0:
		//SetValues(0, 0, 0, 17, 10, 1, this);
		break;
	case 1: //黄钥匙
		SetValues(0, 1, 0, 15, 4, 1, this);
		break;
	case 2: //蓝钥匙
		SetValues(0, 2, 0, 15, 5, 1, this);
		break;
	case 3:  //红钥匙
		SetValues(0, 3, 0, 15, 6, 1, this);
		break;
	case 4:  //红药水
		SetValues(0, 4, 0, 14, 4, 1, this);
		break;
	case 5:  //蓝药水
		SetValues(0, 5, 0, 14, 5, 1, this);
		break;
	case 6:  //攻击
		SetValues(0, 6, 0, 13, 4, 1, this);
		break;
	case 7:  //防御
		SetValues(0, 7, 0, 13, 5, 1, this);
		break;

	case 8:  //飞行法杖
		SetValues(0, 8, 0, 13, 1, 1, this);
		break;

	case -11:  //铁剑
		SetValues(0, -11, 0, 13, 7, 1, this); break;
	case -12:  //铁盾
		SetValues(0, -12, 0, 14, 7, 1, this); break;
	case -19:  //神圣剑
		SetValues(0, -19, 0, 15, 8, 1, this); break;
	case -20:  //神圣盾
		SetValues(0, -20, 0, 15, 9	, 1, this); break;
		break;
	}

}

ID::ID() { //初始化为空地
	FloorType = 0;
	ObjectType = 0;
	Row = 17; Column = 10; shape = 1;
}

