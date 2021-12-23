#pragma once
#include <stdio.h>
#include <conio.h>
#include <cmath	>
#include <ctime>
#include <graphics.h>
#include <time.h>
#include "��������.h"
#include "�ذ�����.h"
#include "�������.h"
#include "�滭����.h"

extern void reCalculatexy();
extern void DrawSleep(int Sle);
extern ID Matrix[50][13][13];
extern int Knight_index, Knight_z, Knight_x, Knight_y, Knight_row, Knight_col, Knight_Value[3], Knight_Possessions[20],// ��Ǯ  �� ��  ��
flag[5],max_z;
extern void MonsterMove(int DepRow, int DepCol, int DesRow, int DesCol),shop();
extern bool talk();


void OpenDoor(ID* ptr) {
	if ((ptr->DoorType == 1) & (Knight_Possessions[1] > 0)) {
		Knight_Possessions[1]--; _sntprintf_s(info, sizeof(info), _T("����һ�ѻ�Կ��"));
		ptr->ChangeID(0);
	}
	if ((ptr->DoorType == 2) & (Knight_Possessions[2] > 0)) {
		Knight_Possessions[2]--; _sntprintf_s(info, sizeof(info), _T("����һ����Կ��"));
		ptr->ChangeID(0);
	}
	if ((ptr->DoorType == 3) & (Knight_Possessions[3] > 0)) {
		Knight_Possessions[3]--; _sntprintf_s(info, sizeof(info), _T("����һ�Ѻ�Կ��"));
		ptr->ChangeID(0);
	}
	if (ptr->DoorType == 8) {

		switch (Knight_z)
		{
		case 2:if (Matrix[2][7][2].FloorType != 0) {
			_sntprintf_s(ManyText, sizeof(ManyText), L"�����������㵽����ʱ�����ڻ�����\nħ�����������ӵ����������\n��������ˣ��Ҹ�������ܵİ����������\n����һ��Խ���ɡ�"); break;
		}
			  else { _sntprintf_s(ManyText, sizeof(ManyText), L"���������ӳ����ˡ���Ľ��Ͷܱ�����������\n��������ҵ���������֪��������5¥��������9¥\n�������ȡ�����ǡ�����������Ҫ��û�����㣬�ټ���"); break; }

		case 10:_sntprintf_s(ManyText, sizeof(ManyText), L"��������˴������ͷ�죬�������а취��ȥ�ˣ�"); break;
		case 0:_sntprintf_s(ManyText, sizeof(ManyText), L"��ϲ��ͨ��ǰ10��\n����Ϸ��������ͽ�����\nϲ���Ļ�����ȥ4399����Ŷ"); talk(); exit(0);
		}
		talk();
		SpecialActionDoor(ptr->DoorType);
		ptr->ChangeID(0);
	}
	if (ptr->DoorType == 6) {

		switch (Knight_z)
		{
		case 2:
			Knight_Possessions[0] += 1000; _sntprintf_s(ManyText, sizeof(ManyText), L"лл������ң�����1000"); break;
		case 3:
			_sntprintf_s(ManyText, sizeof(ManyText), L"����һ������ʼ�\n��H���Բ鿴�������ݣ�Ԥ��ս�����"); Knight_Possessions[6] = 1; break;
		case 4:
			_sntprintf_s(ManyText, sizeof(ManyText), L"��Щ�Ų�����Կ�״�\nֻ�е���������������Ż��Զ��򿪡�"); break;
		case 6:
			_sntprintf_s(ManyText, sizeof(ManyText), L"�㹺����������������˶Ի�\n���������һЩ��Ҫ����Ϣ��"); break;
		}
		talk();
		ptr->ChangeID(0);
	}
	
	if ((ptr->DoorType == 7) && (ptr->health != 0))
	{

		switch (Knight_z)
		{
		case 6:	
			_sntprintf_s(ManyText, sizeof(ManyText), L"ħ��һ��50�㣬ÿ10��Ϊһ������");
			talk();
			_sntprintf_s(ManyText, sizeof(ManyText), L"�������ܴ������ͷĿ�Ͳ��ܵ����ߵĵط���");
			talk();
			ptr->ChangeID(0); break;
		case 7:
			_sntprintf_s(ManyText, sizeof(ManyText), L"���̵��������ѡ������������ֻ���ڹ��������ڵ��˵ķ�����ʱ������������");
			talk();
			ptr->ChangeID(0); break;
		}
	}
	if ((ptr->DoorType == 7) && (ptr->health == 0)) {
		switch (Knight_z)
		{
		case 2:
			_sntprintf_s(ManyText, sizeof(ManyText), L"лл������ң������100Ѫ������Ҫ��");
			if (talk()) { Knight_Value[0] += 100; ptr->ChangeID(0); }
			break;

		case 6:

			_sntprintf_s(ManyText, sizeof(ManyText), L"����һ����Կ�ף����50����Ҿ�������");
			if (talk()) {
				if (Knight_Possessions[0] >= 50) {
					Knight_Possessions[0] -= 50;  Knight_Possessions[2] ++; ptr->health = -1;
				}
				else
				{
					_sntprintf_s(info, sizeof(info), L"��Ľ�Ҳ���");
				}
			}
			break;
		case 7:
			_sntprintf_s(ManyText, sizeof(ManyText), L"������ѻ�Կ�ף����50����Ҿ�������");
			if (talk()) {
				if (Knight_Possessions[0] >= 50) {
					Knight_Possessions[0] -= 50;  Knight_Possessions[1] += 5; ptr->health = -1;
				}
				else
				{
					_sntprintf_s(info, sizeof(info), L"��Ľ�Ҳ���");
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
		Knight_Possessions[1]++; _sntprintf_s(info, sizeof(info), _T("���һ�ѻ�Կ��"));
		ptr->ChangeID(0);
		break;
	case 2:
		Knight_Possessions[2]++; _sntprintf_s(info, sizeof(info), _T("���һ����Կ��"));
		ptr->ChangeID(0);
		break;
	case 3:
		Knight_Possessions[3]++; _sntprintf_s(info, sizeof(info), _T("���һ�Ѻ�Կ��"));
		ptr->ChangeID(0);
		break;
	case 4:
		Knight_Value[0] += 50; _sntprintf_s(info, sizeof(info), _T("���50������"));
		ptr->ChangeID(0);
		break;
	case 5:
		Knight_Value[0] += 200; _sntprintf_s(info, sizeof(info), _T("���200������"));
		ptr->ChangeID(0);
		break;
	case 6:
		Knight_Value[1] += 1; _sntprintf_s(info, sizeof(info), _T("��ú챦ʯ������1�㹥��"));
		ptr->ChangeID(0);
		break;
	case 7:
		Knight_Value[2] += 1; _sntprintf_s(info, sizeof(info), _T("�������ʯ������1�����"));
		ptr->ChangeID(0);
		break;
	case 8:
		Knight_Possessions[7] = 1; _sntprintf_s(info, sizeof(info), _T("��÷��з��ȣ�����\"[\"��\"]\"������¥������"));
		ptr->ChangeID(0);
		break;
	case -11:
		Knight_Value[1] += 10;
		ptr->ChangeID(0);  _sntprintf_s(info, sizeof(info), _T("�������������10�㹥��"));
		Knight_Possessions[4] = -11;
		break;
	case -12:
		Knight_Value[2] += 10;
		ptr->ChangeID(0); _sntprintf_s(info, sizeof(info), _T("������ܣ�����10�����"));
		Knight_Possessions[5] = -12;
		break;
	}
}
