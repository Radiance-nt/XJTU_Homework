#pragma once
#include <stdio.h>
#include <conio.h>
#include <cmath	>
#include <ctime>
#include <graphics.h>
#include <time.h>
#include "产生地形.h"
#include "地板属性.h"
#include "特殊情节.h"
#include "绘画函数.h"

extern void reCalculatexy();
extern void DrawSleep(int Sle);
extern ID Matrix[50][13][13];
extern int Knight_index, Knight_z, Knight_x, Knight_y, Knight_row, Knight_col, Knight_Value[3], Knight_Possessions[20],// 金钱  黄 蓝  红
flag[5],max_z;
extern void MonsterMove(int DepRow, int DepCol, int DesRow, int DesCol),shop();
extern bool talk();


void OpenDoor(ID* ptr) {
	if ((ptr->DoorType == 1) & (Knight_Possessions[1] > 0)) {
		Knight_Possessions[1]--; _sntprintf_s(info, sizeof(info), _T("消耗一把黄钥匙"));
		ptr->ChangeID(0);
	}
	if ((ptr->DoorType == 2) & (Knight_Possessions[2] > 0)) {
		Knight_Possessions[2]--; _sntprintf_s(info, sizeof(info), _T("消耗一把蓝钥匙"));
		ptr->ChangeID(0);
	}
	if ((ptr->DoorType == 3) & (Knight_Possessions[3] > 0)) {
		Knight_Possessions[3]--; _sntprintf_s(info, sizeof(info), _T("消耗一把红钥匙"));
		ptr->ChangeID(0);
	}
	if (ptr->DoorType == 8) {

		switch (Knight_z)
		{
		case 2:if (Matrix[2][7][2].FloorType != 0) {
			_sntprintf_s(ManyText, sizeof(ManyText), L"你清醒了吗？你到监狱时还处在昏迷中\n魔法警卫把你扔到我这个房间\n但你很幸运，我刚完成逃跑的暗道你就醒了\n我们一起越狱吧。"); break;
		}
			  else { _sntprintf_s(ManyText, sizeof(ManyText), L"我们终于逃出来了。你的剑和盾被警卫拿走了\n你必须先找到武器。我知道铁剑在5楼，铁盾在9楼\n你最好先取到它们。我现在有事要做没法帮你，再见。"); break; }

		case 10:_sntprintf_s(ManyText, sizeof(ManyText), L"多亏你打败了此区域的头领，我终于有办法上去了！"); break;
		case 0:_sntprintf_s(ManyText, sizeof(ManyText), L"恭喜你通关前10层\n本游戏做到这里就结束了\n喜欢的话可以去4399游玩哦"); talk(); exit(0);
		}
		talk();
		SpecialActionDoor(ptr->DoorType);
		ptr->ChangeID(0);
	}
	if (ptr->DoorType == 6) {

		switch (Knight_z)
		{
		case 2:
			Knight_Possessions[0] += 1000; _sntprintf_s(ManyText, sizeof(ManyText), L"谢谢你救了我，送你1000"); break;
		case 3:
			_sntprintf_s(ManyText, sizeof(ManyText), L"送你一本怪物笔记\n按H可以查看怪物数据，预测战斗情况"); Knight_Possessions[6] = 1; break;
		case 4:
			_sntprintf_s(ManyText, sizeof(ManyText), L"有些门不能用钥匙打开\n只有当你打败它的守卫后才会自动打开。"); break;
		case 6:
			_sntprintf_s(ManyText, sizeof(ManyText), L"你购买了礼物后再与商人对话\n他会告诉你一些重要的消息。"); break;
		}
		talk();
		ptr->ChangeID(0);
	}
	
	if ((ptr->DoorType == 7) && (ptr->health != 0))
	{

		switch (Knight_z)
		{
		case 6:	
			_sntprintf_s(ManyText, sizeof(ManyText), L"魔塔一共50层，每10层为一个区域。");
			talk();
			_sntprintf_s(ManyText, sizeof(ManyText), L"如果不打败此区域的头目就不能到更高的地方。");
			talk();
			ptr->ChangeID(0); break;
		case 7:
			_sntprintf_s(ManyText, sizeof(ManyText), L"在商店里你最好选择提升防御，只有在攻击力低于敌人的防御力时才提升攻击力");
			talk();
			ptr->ChangeID(0); break;
		}
	}
	if ((ptr->DoorType == 7) && (ptr->health == 0)) {
		switch (Knight_z)
		{
		case 2:
			_sntprintf_s(ManyText, sizeof(ManyText), L"谢谢你救了我，给你加100血，现在要吗");
			if (talk()) { Knight_Value[0] += 100; ptr->ChangeID(0); }
			break;

		case 6:

			_sntprintf_s(ManyText, sizeof(ManyText), L"我有一把蓝钥匙，你出50个金币就卖给你");
			if (talk()) {
				if (Knight_Possessions[0] >= 50) {
					Knight_Possessions[0] -= 50;  Knight_Possessions[2] ++; ptr->health = -1;
				}
				else
				{
					_sntprintf_s(info, sizeof(info), L"你的金币不够");
				}
			}
			break;
		case 7:
			_sntprintf_s(ManyText, sizeof(ManyText), L"我有五把黄钥匙，你出50个金币就卖给你");
			if (talk()) {
				if (Knight_Possessions[0] >= 50) {
					Knight_Possessions[0] -= 50;  Knight_Possessions[1] += 5; ptr->health = -1;
				}
				else
				{
					_sntprintf_s(info, sizeof(info), L"你的金币不够");
				}
			}
			break;
		}
	}

	if (ptr->DoorType == 9) { ptr->ChangeID(0); }
	if (ptr->DoorType == -5) { shop(); }
}

void GetObject(ID* ptr) {

	switch (ptr->ObjectType)
	{
	case -2:if (Knight_z != 10) { Knight_z++; if (Knight_z > max_z)max_z = Knight_z; break; }
		   else {
		Knight_z = 0; break;
	}
	case -3:Knight_z--; break;
	case 1:
		Knight_Possessions[1]++; _sntprintf_s(info, sizeof(info), _T("获得一把黄钥匙"));
		ptr->ChangeID(0);
		break;
	case 2:
		Knight_Possessions[2]++; _sntprintf_s(info, sizeof(info), _T("获得一把蓝钥匙"));
		ptr->ChangeID(0);
		break;
	case 3:
		Knight_Possessions[3]++; _sntprintf_s(info, sizeof(info), _T("获得一把红钥匙"));
		ptr->ChangeID(0);
		break;
	case 4:
		Knight_Value[0] += 50; _sntprintf_s(info, sizeof(info), _T("获得50点生命"));
		ptr->ChangeID(0);
		break;
	case 5:
		Knight_Value[0] += 200; _sntprintf_s(info, sizeof(info), _T("获得200点生命"));
		ptr->ChangeID(0);
		break;
	case 6:
		Knight_Value[1] += 1; _sntprintf_s(info, sizeof(info), _T("获得红宝石，增加1点攻击"));
		ptr->ChangeID(0);
		break;
	case 7:
		Knight_Value[2] += 1; _sntprintf_s(info, sizeof(info), _T("获得蓝宝石，增加1点防御"));
		ptr->ChangeID(0);
		break;
	case 8:
		Knight_Possessions[7] = 1; _sntprintf_s(info, sizeof(info), _T("获得飞行法杖，按下\"[\"或\"]\"即可在楼层间飞行"));
		ptr->ChangeID(0);
		break;
	case -11:
		Knight_Value[1] += 10;
		ptr->ChangeID(0);  _sntprintf_s(info, sizeof(info), _T("获得铁剑，增加10点攻击"));
		Knight_Possessions[4] = -11;
		break;
	case -12:
		Knight_Value[2] += 10;
		ptr->ChangeID(0); _sntprintf_s(info, sizeof(info), _T("获得铁盾，增加10点防御"));
		Knight_Possessions[5] = -12;
		break;
	}
}
