#pragma once
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include "�ذ�����.h"
#include "�滭����.h"
#define MonsterWalkSpeed 2	

extern void reCalculatexy(); 
extern void DrawSleep(int Sle);
extern ID Matrix[50][13][13];
extern int Knight_index , Knight_z , Knight_x, Knight_y, Knight_row, Knight_col, Knight_Value[3], Knight_Possessions[20];// ��Ǯ  �� ��  ��
extern int flag[5];
//extern void MonsterMove(int DepRow, int DepCol, int DesRow, int DesCol);
extern bool talk();


void MonsterMove(int DepRow, int DepCol, int DesRow, int DesCol) {
	ID* ptr = &Matrix[Knight_z][DepRow - 1][DepCol - 1];
	int DepX = (32 * (3 + DepCol)) - 16, DesX = (32 * (3 + DesCol)) - 16;
	int DesY = 32 * (DesRow - 1), DepY = 32 * (DepRow - 1);
	int tmpM = ptr->MonsterType, tmpR = ptr->Row, tmpC = ptr->Column;
	ptr->ChangeID(0);
	if (DepCol == DesCol) {
		while (DepY != DesY) {
			DepY += abs(DesRow - DepRow) / (DesRow - DepRow) * MonsterWalkSpeed;
			Draw();
			DrawTwoSquare(tmpR, tmpC, 1, DepX, DepY);
			FlushBatchDraw();
			Sleep(10);
		}
	}
	else if (DepRow == DesRow) {
		while (DepX != DesX) {
			DepX += abs(DesCol - DepCol) / (DesCol - DepCol) * MonsterWalkSpeed;
			Draw();
			DrawTwoSquare(tmpR, tmpC, 1, DepX, DepY);
			FlushBatchDraw();
			Sleep(10);
		}
	}
	Matrix[Knight_z][DesRow - 1][DesCol - 1].SetMonster(tmpM);


}

void SpecialAction() {
	if ((Knight_z == 3) & (Knight_row == 9) & (Knight_col == 6) & (flag[0] == 1)) {  //����ħ��
		flag[0] = 0;
		Matrix[3][6][5].SetMonster(30);
		DrawSleep(500);
		_sntprintf_s(ManyText, sizeof(ManyText), L"ħ�� Zeno ˵������ӭ����ħ�������ǵ�һ��λ��ս�ߡ�\n�����ܴ�������е����£��Ҿ�����һ��һ�ľ�����\n�������������ҵİ��š�");
		talk();
		Matrix[3][9][5].SetMonster(29);
		Matrix[3][7][5].SetMonster(29);
		Matrix[3][8][4].SetMonster(29);
		Matrix[3][8][6].SetMonster(29);
		DrawSleep(500);
		_sntprintf_s(ManyText, sizeof(ManyText), L"ʲô��");
		talk();
		DrawSleep(200);
		flag[0] = 2;
		DrawSleep(2000);
		Knight_Value[0] -= 600; Knight_Value[1] -= 90; Knight_Value[2] -= 90;
		Knight_Possessions[4] = 0; Knight_Possessions[5] = 0;
		Knight_z = 2; Knight_row = 9; Knight_col = 4;
		reCalculatexy();
		_sntprintf_s(ManyText, sizeof(ManyText), L"��������");
		talk();
		_sntprintf_s(ManyText, sizeof(ManyText), L"������������ι��");
		talk();
		_sntprintf_s(ManyText, sizeof(ManyText), L"������������ι���������ѣ�");
		talk();
		flag[0] = 0;
		Matrix[3][6][5].ChangeID(0);
		Matrix[3][9][5].ChangeID(0);
		Matrix[3][7][5].ChangeID(0);
		Matrix[3][8][4].ChangeID(0);
		Matrix[3][8][6].ChangeID(0);
	}
	if ((Knight_z == 2) && (Matrix[2][2][6].FloorType == 0) && (Matrix[2][2][8].FloorType == 0)) { //2¥����
		Matrix[2][5][5].ChangeID(0);
		Matrix[2][8][5].ChangeID(0);
		Matrix[2][11][5].ChangeID(0);
		Matrix[2][5][9].ChangeID(0);
		Matrix[2][8][9].ChangeID(0);
		Matrix[2][11][9].ChangeID(0);
	}
	if ((Knight_z == 8) && (Matrix[8][5][9].FloorType == 0) && (Matrix[8][5][11].FloorType == 0)) {  //��Կ��
		Matrix[8][4][10].ChangeID(0);
	}

	if ((Knight_z == 10) && (Knight_row == 6) && (Knight_col == 7) && (flag[1] == 1)) {
		flag[1] = 0;
		MonsterMove( 5, 7, 3, 7);
		Matrix[10][4][4].ChangeID(0);
		Matrix[10][4][8].ChangeID(0);
		Matrix[10][6][5].ChangeID(0);
		Matrix[10][6][7].ChangeID(0);
		Matrix[10][3][6].ChangeID(4);
		Matrix[10][7][6].ChangeID(4);
		_sntprintf_s(ManyText, sizeof(ManyText), L"������, ������˵������ܰ�ȫ�������\n�����ں��������ȥ�ˣ���������ˣ������Ǹ����ϡ�"); 
		talk();
		DrawSleep(500);
		MonsterMove(4, 10, 5, 10);
		MonsterMove(5, 10, 5, 8);
		MonsterMove(5, 8, 7, 8);
		MonsterMove(7, 8, 7, 7);//#####
		MonsterMove( 4, 4, 5, 4);
		MonsterMove(5, 4, 5, 6);
		MonsterMove(5, 6, 7, 6);//#####
		MonsterMove(4, 11, 4, 10);
		MonsterMove(4, 10, 5, 10);
		MonsterMove( 5, 10, 5, 8);
		MonsterMove( 5, 8, 7, 8);//#####
		MonsterMove(5, 3, 5, 6);
		MonsterMove(5, 6, 6, 6);//#####
		MonsterMove(5, 11, 5, 8);
		MonsterMove(5, 8, 6, 8);//#####
		MonsterMove(4, 3, 5, 3);
		MonsterMove(5, 3, 5, 7);
		MonsterMove(4, 12, 5, 12);
		MonsterMove(5, 12, 5, 8);
		MonsterMove(4, 2, 5, 2);
		MonsterMove(5, 2, 5, 6);
		Matrix[10][4][4].ChangeID(4);
		Matrix[10][4][8].ChangeID(4);
	
		//MonsterMove(&Matrix[10][4][6], 6, 7, 3, 7);
		
	}
	if ((Knight_z == 10) && (flag[1] == 0) &&
		(Matrix[10][5][5].FloorType == 0) &&
		(Matrix[10][5][7].FloorType == 0) &&
		(Matrix[10][4][5].FloorType == 0) &&
		(Matrix[10][4][6].FloorType == 0) &&
		(Matrix[10][4][7].FloorType == 0) &&
		(Matrix[10][6][5].FloorType == 0) &&
		(Matrix[10][6][6].FloorType == 0) &&
		(Matrix[10][6][7].FloorType == 0)) {
		flag[1] =2;
		_sntprintf_s(ManyText, sizeof(ManyText), L"������ɱ����Χ�����Ǿ���������ͨ����\n���ɣ���Ҫ�������!");
		talk();
		Matrix[10][3][6].ChangeID(0);

	}
	if ((Knight_z == 10) && (flag[1] == 2)&& (Matrix[10][2][6].FloorType == 0)) {
		flag[1] = 3;
		_sntprintf_s(ManyText, sizeof(ManyText), L"��,���ǲ����ܵģ� ���������ң�\n���̫���⣬���滹�����ǿ��Ķ��ֺͻ��ش���!\n����������ͱ������ɡ�");
		Matrix[10][4][4].ChangeID(0);
		Matrix[10][3][1].SetObject(6);
		Matrix[10][3][2].SetObject(6);
		Matrix[10][3][3].SetObject(6);
		Matrix[10][4][1].SetObject(5);
		Matrix[10][4][2].SetObject(5);
		Matrix[10][4][3].SetObject(5);
		Matrix[10][3][9].SetObject(7);
		Matrix[10][3][10].SetObject(7);
		Matrix[10][3][11].SetObject(7);
		Matrix[10][4][9].SetObject(1);
		Matrix[10][4][10].SetObject(1);
		Matrix[10][4][11].SetObject(1);
		Matrix[10][4][8].ChangeID(0);
		Matrix[10][3][6].ChangeID(0);
		Matrix[10][7][6].ChangeID(0);
		Matrix[10][11][6].ChangeID(-2);
		talk();
	}
	if ((Knight_z == 10) && (Knight_row == 10) && (Knight_col == 7) && (flag[1] == 3)) {
		flag[1] = 4;
		Matrix[10][10][1].ChangeID(8);
		MonsterMove(11, 2, 9, 2);
		Matrix[10][8][1].ChangeID(8);
		MonsterMove(9, 2, 9, 4);
		Matrix[10][8][3].ChangeID(8);
		MonsterMove(9, 4, 12, 4);
		Matrix[10][11][3].ChangeID(8);
		MonsterMove(12, 4, 12, 6);
		Matrix[10][11][5].ChangeID(8);
		MonsterMove(12, 6, 11, 6);
		Matrix[10][10][5].ChangeID(8);
		MonsterMove(11, 6, 11, 7);
		Matrix[10][10][6].ChangeID(8);
	}
}

void SpecialActionDoor(int f) {
	if (f == 8) {
		if ((Knight_z == 2) && (Matrix[2][7][2].FloorType != 0)) {//Խ��
			Matrix[2][7][2].ChangeID(0);
			MonsterMove(8, 4, 8, 2);
			Matrix[2][7][1].ChangeID(8);
			MonsterMove(8, 2, 10, 2);
			Matrix[2][9][1].ChangeID(8);
			return;
		}
		if ((Knight_z == 2) && (Matrix[2][7][2].FloorType == 0)) {
			MonsterMove(10, 2, 12, 2);
		}
		if (Knight_z == 10) {
			MonsterMove(11, 7, 12, 7);
		}

	}
}



