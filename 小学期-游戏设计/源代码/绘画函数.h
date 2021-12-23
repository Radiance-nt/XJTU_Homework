#pragma once
#include<vector>
#include<algorithm>
#include <stdio.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <graphics.h>
#include <time.h>
#include "产生地形.h"
#include "地板属性.h"
#include "特殊情节.h"

#define FlashSpeed 500
#define Left 12
#define Right 116 
using namespace std;
vector<int> Vec;
IMAGE resource_tran;
IMAGE resource_mask;
extern ID Matrix[50][13][13];
extern int flag[5],Knight_index, Knight_z, Knight_x, Knight_y, Knight_row, Knight_col, Knight_Value[3], Knight_Possessions[20], monsterguidflag, textboxflag, shopboxflag;// 金钱  黄 蓝  红
LOGFONT font1; extern TCHAR info[30]; TCHAR WhichFloor[50],WeaponInfo[20],ArmourInfo[20]; TCHAR ManyText[100],MonsterText[50];
LOGFONT font2;

RECT mota, health, offense, deffense, object, money, ShopBox,TextBox, KeyBox,WeaponBox,Weapon,Armour;

extern clock_t clo1, clo2;

void UpText(int H) {//const wchar_t string[30]
	settextcolor(RGB(255, 255, 255));
	gettextstyle(&font2);
	font2.lfHeight = H;
	settextstyle(&font2);
}

void initResource()
{
	ifstream infile1("images\\魔塔透明.png");
	ifstream infile2("images\\魔塔掩码.png");
	if ( (infile1.is_open() == 0) | (infile2.is_open() == 0)) {
		MessageBox(NULL, _T("找不到必备图片文件"), _T("错误"), MB_ICONHAND);
		exit(0);
	}
	loadimage(&resource_tran, _T("images\\魔塔透明.png"));
	loadimage(&resource_mask, _T("images\\魔塔掩码.png"));
}

void DrawOneSquare(int Row, int Column, int shape, int x, int y) {  //根据x y 坐标画

	putimage(x, y, 32 * shape, 32 * shape, &resource_mask, 32 * (Column - 1), 32 * (Row - 1), SRCAND);
	putimage(x, y, 32 * shape, 32 * shape, &resource_tran, 32 * (Column - 1), 32 * (Row - 1), SRCPAINT);
}
void DrawTwoSquare(int Row, int Column, int shape, int x, int y) {  //根据x y 坐标画
	if (((clo2 - clo1) % FlashSpeed) < (FlashSpeed / 2)) {
		putimage(x, y, 32 * shape, 32 * shape, &resource_mask, 32 * (Column - 1), 32 * (Row - 1), SRCAND);
		putimage(x, y, 32 * shape, 32 * shape, &resource_tran, 32 * (Column - 1), 32 * (Row - 1), SRCPAINT);
	}
	else {
		putimage(x, y, 32 * shape, 32 * shape, &resource_mask, 32 * (Column - 2), 32 * (Row - 1), SRCAND);
		putimage(x, y, 32 * shape, 32 * shape, &resource_tran, 32 * (Column - 2), 32 * (Row - 1), SRCPAINT);
	}
}
void DrawRCSquare(int r, int c, ID sq) { //用行r 列c   ID  画
	if ((sq.FloorType == 2)|((sq.DoorType >5)& (sq.DoorType < 9))) {
		DrawTwoSquare(sq.Row, sq.Column, sq.shape, (32 * (3 + c)) - 16, (r - 1) * 32);
		
	}
	else if (sq.DoorType==-5)
		if (((clo2 - clo1) % FlashSpeed) < (FlashSpeed / 2)) {
			putimage((32 * (3 + c)) - 16, (r - 1) * 32, 32 , 32, &resource_mask, 32* 9, 32 * 11, SRCAND);
			putimage((32 * (3 + c)) - 16, (r - 1) * 32, 32 , 32, &resource_tran, 32 *9 , 32 * 11, SRCPAINT);
		}
		else {
			putimage((32 * (3 + c)) - 16, (r - 1) * 32, 32 , 32, &resource_mask, 32 * 7, 32 * 11, SRCAND);
			putimage((32 * (3 + c)) - 16, (r - 1) * 32, 32 , 32, &resource_tran, 32 * 7, 32 * 11, SRCPAINT);
		}
	else { 
		DrawOneSquare(sq.Row, sq.Column, sq.shape, (32 * (3 + c)) - 16, (r - 1) * 32);
	}
}

void OutputWAInfo() {
	switch (Knight_Possessions[4])
	{
	case 0:_sntprintf_s(WeaponInfo, sizeof(WeaponInfo), _T("武器:\n无")); break;
	case -11:
		_sntprintf_s(WeaponInfo, sizeof(WeaponInfo), _T("武器:\n铁剑"));
		DrawOneSquare(13, 7, 1, 32 * 16 + 70, 34);
		break;
	case -19:
		_sntprintf_s(WeaponInfo, sizeof(WeaponInfo), _T("武器:\n神圣剑"));
		DrawOneSquare(15, 8, 1, 32 * 16 + 70, 34);
		break;
	}
	switch (Knight_Possessions[5])
	{
	case 0:_sntprintf_s(ArmourInfo, sizeof(ArmourInfo), _T("防具:\n无")); break;
	case -12:
		_sntprintf_s(ArmourInfo, sizeof(ArmourInfo), _T("防具:\n铁盾"));
		DrawOneSquare(14, 7, 1, 32 * 16 + 70, 76);
		break;
	case -20:
		_sntprintf_s(ArmourInfo, sizeof(ArmourInfo), _T("防具:\n神圣盾"));
		DrawOneSquare(15, 9, 1, 32 * 16 + 70, 76);
		break;
	}

	UpText(20);
	drawtext(WeaponInfo, &Weapon, (DT_CENTER));
	drawtext(ArmourInfo, &Armour, (DT_CENTER));

}



void DrawBK() {
	for (int x = 0; x < (32 * 4); x += 32) {        //画左边
		for (int y = 0; y < (32 * 13); y += 32) {
			DrawOneSquare(17, 2, 1, x, y);
		}
	}
	for (int x = (32 * 16); x < (32 * 21); x += 32) {   //画右边
		for (int y = 0; y < (32 * 13); y += 32) {
			DrawOneSquare(17, 2, 1, x, y);
		}
	}
	setfillcolor(0xFFF8F0);
	solidrectangle(0, 32 * 13, 21 * 32, 32 * 13 + 24);
	setfillcolor(0x908070);
	solidrectangle(mota.left,mota.top,mota.right,mota.bottom);
	solidrectangle(health.left, health.top, health.right, health.bottom);
	solidrectangle(offense.left, offense.top, offense.right, offense.bottom);
	solidrectangle(deffense.left, deffense.top, deffense.right, deffense.bottom);
	solidrectangle(money.left, money.top, money.right, money.bottom);
	solidrectangle(object.left, object.top, object.right, object.bottom);
	if (Knight_Possessions[7] == 1)DrawOneSquare(13, 1, 1, object.left+2, object.top+2);
	solidrectangle(KeyBox.left, KeyBox.top, KeyBox.right, KeyBox.bottom);
	solidrectangle(WeaponBox.left, WeaponBox.top, WeaponBox.right, WeaponBox.bottom);
	UpText(25);
	_sntprintf_s(WhichFloor, sizeof(WhichFloor), L"魔塔  第%d层", Knight_z);
	drawtext(WhichFloor, &mota,( DT_VCENTER, DT_CENTER));
	UpText(25);
	_sntprintf_s(WhichFloor, sizeof(WhichFloor), L" 生命  %4d", Knight_Value[0]);
	drawtext(WhichFloor, &health, (DT_VCENTER));
	_sntprintf_s(WhichFloor, sizeof(WhichFloor), L" 攻击  %4d", Knight_Value[1]);
	drawtext(WhichFloor, &offense, (DT_VCENTER));
	_sntprintf_s(WhichFloor, sizeof(WhichFloor), L" 防御  %4d", Knight_Value[2]);
	drawtext(WhichFloor, &deffense, (DT_VCENTER));
	_sntprintf_s(WhichFloor, sizeof(WhichFloor), L" 金币  %4d", Knight_Possessions[0]);
	drawtext(WhichFloor, &money, (DT_VCENTER));
	UpText(28);
	_sntprintf_s(WhichFloor, sizeof(WhichFloor), _T(" 黄钥匙%3d\n 蓝钥匙%3d\n 红钥匙%3d"), Knight_Possessions[1], Knight_Possessions[2], Knight_Possessions[3]);
	drawtext(WhichFloor, &KeyBox, (DT_VCENTER));

		
	OutputWAInfo();
	
}
void DrawKnight() {
	switch (Knight_index)
	{
	case 21:
		DrawOneSquare(7, 7, 1, Knight_x, Knight_y);
		break;
	case 22:
		DrawOneSquare(7, 8, 1, Knight_x, Knight_y);
		break;
	case 23:
		DrawOneSquare(7, 9, 1, Knight_x, Knight_y);
		break;
	case 81:
		DrawOneSquare(7, 10, 1, Knight_x, Knight_y);
		break;
	case 82:
		DrawOneSquare(8, 7, 1, Knight_x, Knight_y);
		break;
	case 83:
		DrawOneSquare(8, 8, 1, Knight_x, Knight_y);
		break;
	case 41:
		DrawOneSquare(8, 9, 1, Knight_x, Knight_y);
		break;
	case 42:
		DrawOneSquare(8, 10, 1, Knight_x, Knight_y);
		break;
	case 43:
		DrawOneSquare(9, 7, 1, Knight_x, Knight_y);
		break;
	case 61:
		DrawOneSquare(9, 8, 1, Knight_x, Knight_y);
		break;
	case 62:
		DrawOneSquare(9, 9, 1, Knight_x, Knight_y);
		break;
	case 63:
		DrawOneSquare(9, 10, 1, Knight_x, Knight_y);
		break;
	}
}
void DrawTextBox() {
	setfillcolor(BLUE);
	solidrectangle(TextBox.left, TextBox.top, TextBox.right, TextBox.bottom);
	UpText(20);
	drawtext(ManyText, &TextBox, (DT_VCENTER));
	//写文字
}
void DrawShopBox() {
	setfillcolor(BLUE);
	solidrectangle(ShopBox.left, ShopBox.top, ShopBox.right, ShopBox.bottom);
	UpText(20);
	drawtext(ManyText, &ShopBox, (DT_VCENTER));
	//写文字
}

void BottomText()
{
	settextcolor(RGB(105, 105, 108));
	
	settextstyle(&font1);
}

void DrawText() {
	BottomText();
	outtextxy(6, 32 * 13+2, info);
}
	

void DrawMonsterGuides() {
	Vec.clear();
	int  location=90, GiveID=0, health, offense, defense, money,row,col;
	for (hang = 0; hang < 13; hang++) {
		for (lie = 0; lie < 13; lie++) {
			if (Matrix[Knight_z][hang][lie].MonsterType != 0)  Vec.push_back(Matrix[Knight_z][hang][lie].MonsterType);
		}
	}
	sort(Vec.begin(), Vec.end());
	for (auto it : Vec)
	{
		if(GiveID!= it)

			{
			GiveID = it;//GiveID = Vec[i];
			if (GiveID % 5 != 0){
				row = GiveID / 5 + 1;
				col=2 * (GiveID % 5);
			}
			else {
				row = GiveID / 5;
				col = 10;
			}
			DrawTwoSquare(row, col, 1, 32 * 4 + 32, location);

			health = MonsterInfo[GiveID][0];
			offense = MonsterInfo[GiveID][1];
			defense = MonsterInfo[GiveID][2];
			money = MonsterInfo[GiveID][3];
			int K_health = Knight_Value[0];
			int K_offense = Knight_Value[1];
			int K_defense = Knight_Value[2];
			int M_health = health;
			int M_offense = offense;
			int M_defense = defense;
			settextcolor(RGB(255, 255, 255));
			_sntprintf_s(MonsterText, sizeof(MonsterText), L"血量%d，攻击%d，防御%d，获得金币%d", health, offense, defense, money);
			outtextxy(32 * 4 + 68, location -2, MonsterText);
			settextcolor(RGB(255, 0, 0));
			while (1)
			{
				M_health = M_health - K_offense + M_defense;
				if ((M_health <= 0)&&(Knight_Value[0]==K_health)) {
					_sntprintf_s(MonsterText, sizeof(MonsterText), L"无危险");
					outtextxy(32 * 4 + 68, location + 14, MonsterText);
					break;
				}
				if (M_health <= 0) {
					_sntprintf_s(MonsterText, sizeof(MonsterText), L"你的血量将会减少%d", Knight_Value[0] - K_health);
					outtextxy(32 * 4 + 68, location + 14, MonsterText);
					break; }
				K_health = K_health - M_offense + K_defense;
				if (K_health <= 0) { 
					
					_sntprintf_s(MonsterText, sizeof(MonsterText), L"不可攻击");
					outtextxy(32 * 4 + 68, location +14, MonsterText);
				
				break;
				}
			}
			location += 40;
			}
	}

}


void Draw() {
	cleardevice(); clo2 = clock();
	for (int x = (32 * 4) - 16; x < (32 * 17) - 16; x += 32) {    	//先全部画上地板 13*13
		for (int y = 0; y < (32 * 13); y += 32) {
			DrawOneSquare(17, 10, 1, x, y);
		}
	}
	for (hang = 1; hang < 14; hang++) {   //画每个格子的东西
		for (lie = 1; lie < 14; lie++) {
			DrawRCSquare(hang, lie, Matrix[Knight_z][hang - 1][lie - 1]);
		}
	}	

	
	DrawKnight();
	if (flag[0] == 2) { setfillcolor(RED); solidrectangle(0, 0, 999, 999); }
	if (textboxflag==1)
	DrawTextBox();
	if (shopboxflag == 1)
	DrawShopBox();
	if (monsterguidflag == 1)
	DrawMonsterGuides();
	DrawBK();
	DrawText();
	FlushBatchDraw();
	
}
void DrawSleep(int Sle) {
	for (int i = 0; i < Sle; i += 10) {
		Draw();
		Sleep(10);
	}

}

void InitText() {
	gettextstyle(&font1); _tcscpy_s(font1.lfFaceName, _T("微软雅黑")); font1.lfHeight = 22;
	gettextstyle(&font2);_tcscpy_s(font2.lfFaceName, _T("宋体"));
	setbkmode(TRANSPARENT);
}
void InitRC() {
	mota.left = Left; mota.top = 48-20; mota.right =Right; mota.bottom = 80-20;
	health.left = Left; health.top = 120-25; health.right = Right; health.bottom = 145 - 25;
	offense.left = Left; offense.top = 155 - 25; offense.right = Right; offense.bottom =180 - 25;
	deffense.left = Left; deffense.top = 190 - 25; deffense.right = Right; deffense.bottom = 215 - 25;
	money.left = Left; money.top = 225 - 25; money.right = Right; money.bottom = 250 - 25;
	object.left = Left; object.top = 250 ; object.right = Right; object.bottom = 400;
	TextBox.left = 32*4+16; TextBox.top = 80; TextBox.right = 32 * 16- 16; TextBox.bottom =32*13-80;
	ShopBox.left = 32 * 4 + 96; ShopBox.top = 80; ShopBox.right = 32 * 16 - 96; ShopBox.bottom = 32 * 13 - 80;
	KeyBox.left = 32 * 16+ Left; KeyBox.top = 140; KeyBox.right = 32 * 16 +Right; KeyBox.bottom = 230;
	WeaponBox.left = 32 * 16 + Left; WeaponBox.top = 28; WeaponBox.right = 32 * 16 + Right; WeaponBox.bottom = 120;
	Weapon.left = 32 * 16 + Left; Weapon.top = 30; Weapon.right = 32 * 16 + 60; Weapon.bottom = 78;
	Armour.left = 32 * 16 + Left; Armour.top = 75; Armour.right = 32 * 16 + 60; Armour.bottom = 112;
	
	
}



