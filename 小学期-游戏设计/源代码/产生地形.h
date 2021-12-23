#pragma once
#include "地板属性.h"
#include<string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <algorithm>
#define FloorNumbers 50

using namespace std;

extern int lou, hang, lie;
extern ID Matrix[50][13][13];
int CI, SM, SO,temp;
int Floors[FloorNumbers+1][11][12][3];

string oneline;

void Creat() {
	ifstream infile1("ChangeID");
	ifstream infile2("Monster");
	ifstream infile("Object");
	if ((infile.is_open() == 0) | (infile1.is_open() == 0) | (infile2.is_open() == 0)) {
		MessageBox(NULL, _T("找不到必备文件"), _T("错误"), MB_ICONHAND);
		exit(0);
	}
	for (lou = 0; lou < FloorNumbers; lou++) {
		getline(infile1, oneline);
		for (hang = 0; hang < 11; hang++) {
			getline(infile1, oneline);
			stringstream ss1(oneline);
			for (lie = 0; lie < 12; lie++) {
				ss1 >> Floors[lou][hang][lie][0];
			}
		}
		getline(infile1, oneline);
	}
	
	for (lou = 0; lou < FloorNumbers; lou++) {
		getline(infile2, oneline);
		for (hang = 0; hang < 11; hang++) {
			getline(infile2, oneline);
			stringstream ss2(oneline);
			for (lie = 0; lie < 12; lie++) {
				ss2 >> Floors[lou][hang][lie][1];
			}
		}
		getline(infile2, oneline);
	}
	
	for (lou = 0; lou < FloorNumbers; lou++) {
		getline(infile, oneline);
		for (hang = 0; hang < 11; hang++) {
			getline(infile, oneline);
			stringstream ss3(oneline);
			for (lie = 0; lie < 12; lie++) {
				ss3 >> Floors[lou][hang][lie][2];
			}
		}
		getline(infile, oneline);
	}

	for (lou = 0; lou < FloorNumbers; lou++) {
		for (hang = 1; hang < 12; hang++) {
			for (lie = 1; lie < 12; lie++) {
				CI = Floors[lou][hang - 1][lie][0];
				SM = Floors[lou][hang - 1][lie][1];
				SO = Floors[lou][hang - 1][lie][2];
				Matrix[lou][hang][lie].ChangeID(CI);  //行列是真是的 
				Matrix[lou][hang][lie].SetMonster(SM);
				Matrix[lou][hang][lie].SetObject(SO);
			}
		}
	}
}

void SetMatrix() {

	for (lou = 0; lou < 50; lou++) {
		for (hang = 0; hang < 13; hang++) {
			for (lie = 0; lie < 13; lie++) {
				if ((hang == 0) | (hang == 12) | (lie == 0) | (lie == 12)) {
					Matrix[lou][hang][lie].ChangeID(-1);
				}
			}
		}
	}/*****************************  四周墙壁边框  *************************************/
}
