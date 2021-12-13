#include<iostream>
#include <queue>
#include<string>
#include "ha.h"
#include<fstream>
#include<sstream>
#define GET_BYTE(vbyte, index) (((vbyte) & (1 << ((index) ^ 7))) != 0)
#define SET_BYTE(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
#define CLR_BYTE(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))
#define HEAD_SIZE 12
typedef unsigned char cap_type;
using namespace std;
typedef node<cap_type> nodechar;
cap_type ch;
BT<cap_type> tree, tree2;
short int char_num[256];
string Haf_tab[256];



int getlastValidBit() {
	int sum = 0;
	for (int i = 0; i < 256; i++) {
		sum += Haf_tab[i].size() * char_num[i];
	}

	if (sum % 16==0)
		return 8;
	else
		return sum % 16;
};

struct CompareFun		//优先队列比较函数
{
	bool operator() (BT<cap_type> a, BT<cap_type> b)
	{
		return a.root->weight > b.root->weight;
	}
};


void create_tab(FILE* fp_i) {
	int i;
	fseek(fp_i, 0, SEEK_SET);
	for (i = 0; i < 256; i++) {
		char_num[i] = 0;
	}
	ch = fgetc(fp_i);
	while (!feof(fp_i)) {
		char_num[ch] += 1;
		ch = fgetc(fp_i);
	}
	fseek(fp_i, 0, SEEK_SET);
}

BT<cap_type> build_tree(priority_queue<BT<cap_type>, deque<BT<cap_type>>, CompareFun > queue1) {

	BT<cap_type>tree10, tree20, tree30;
	while (queue1.size() > 1) {
		tree10 = queue1.top();
		queue1.pop();
		tree20 = queue1.top();
		queue1.pop();
		tree30.createTree(&tree10, &tree20);
		queue1.push(tree30);
	}

	if (!queue1.empty())
		return queue1.top();
	else
		return 0;
}

void capsule(const char* filename1, const char* filename2) {   //一个字符建不了树
	FILE* fp_i, * fp_o;
	errno_t e; string haf_code, sum;
	priority_queue<BT<cap_type>, deque<BT<cap_type>>, CompareFun >queue1, queue2;
	int i; short int var, trash; long curLocation;
	if (e = fopen_s(&fp_i, filename1, "r") != 0) { cout << "error"; return; }
	if (e = fopen_s(&fp_o, filename2, "wb") != 0) { cout << "error"; return; }

	create_tab(fp_i);
	cout << "↑字符频率统计↑" << endl << endl;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (i = 0; i < 256; i++) {
		if (char_num[i]) {
			nodechar* s = new nodechar(i, char_num[i]);
			queue1.push(BT<cap_type>(s));
		}
	}
	tree = build_tree(queue1);
	tree.in_order();
	var = queue1.size();
	trash = getlastValidBit();
	cout << "var= " << var << endl;
	cout << "trash= " << trash << endl;
	fwrite(&var, sizeof(short int), 1, fp_o);                                       //写个数
	fwrite(&trash, sizeof(short int), 1, fp_o);
	cout << "↑头文件写入↑" << endl << endl;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fseek(fp_o, HEAD_SIZE, SEEK_SET);
	curLocation = ftell(fp_i);
	queue2 = queue1;
	for (int i = 0; i < var; i++) {
		fwrite(&queue2.top().root->data, sizeof(cap_type), 1, fp_o);							//这里可以删减
		fwrite(&char_num[queue2.top().root->data], sizeof(short int), 1, fp_o);
		cout << queue2.top().root->data << char_num[queue2.top().root->data] << endl;
		queue2.pop();
	}
	cout << "↑字符频率写入↑" << endl << endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fread(&ch, sizeof(cap_type), 1, fp_i);
	while (!feof(fp_i)) {
		sum += Haf_tab[ch];
		fread(&ch, sizeof(cap_type), 1, fp_i);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	fseek(fp_o, HEAD_SIZE + var * (sizeof(cap_type) + sizeof(short int)) + 2, SEEK_SET);
	curLocation = ftell(fp_o);
	const char* ptr = sum.c_str();
	unsigned short int bitIndex = 0, value = 0;
	while (*ptr != '\0') {
		if (*ptr == '1') {
			SET_BYTE(value, bitIndex);
		}
		else if (*ptr == '0') {
			CLR_BYTE(value, bitIndex);//移位0
		}
		bitIndex++;
		if (bitIndex >= 16) {
			bitIndex = 0;
			fwrite(&value, sizeof(unsigned short int), 1, fp_o);
			//cout << value << "  capsule_value" << endl;
			curLocation = ftell(fp_i);
			value = 0;
		}
		ptr++;
	}
	if (bitIndex > 0) {
		fwrite(&value, sizeof(unsigned short int), 1, fp_o);
	}
	cout << "↑压缩成功！↑" << endl << endl;
	cout << endl;
	_fcloseall();
}





void incapsule(const char* filename1, const char* filename2) {
	priority_queue<BT<cap_type>, deque<BT<cap_type>>, CompareFun > queue1, queue2;
	errno_t e;
	FILE* fp_i, * fp_o;
	if (e = fopen_s(&fp_i, filename1, "rb") != 0) { cout << "error"; return; }
	if (e = fopen_s(&fp_o, filename2, "w") != 0) { cout << "error"; return; }
	string  sum = "";
	long fileSize;
	long curLocation;
	unsigned short int value, index = 0, i;
	short int weight;
	short int var, trash;

	fseek(fp_i, 0, SEEK_END);
	fileSize = ftell(fp_i);
	cout << "filesize= " << fileSize << endl;
	fseek(fp_i, 0, SEEK_SET);
	fread(&var, sizeof(short int), 1, fp_i);							//写个数
	fread(&trash, sizeof(short int), 1, fp_i);
	cout << "var= " << var << endl;
	cout << "trash= " << trash << endl;
	cout << "↑头文件读取↑" << endl << endl;

	fseek(fp_i, HEAD_SIZE, SEEK_SET);
	for (int i = 0; i < var; i++) {
		fread(&ch, sizeof(cap_type), 1, fp_i);					                     //写字符
		fread(&weight, sizeof(short int), 1, fp_i);
		char_num[ch] = weight;
		cout << ch << weight << endl;

	}
	cout << "↑字符频率读取↑" << endl << endl;
	for (i = 0; i < 256; i++) {
		if (char_num[i]) {
			nodechar* s = new nodechar(i, char_num[i]);
			queue1.push(BT<cap_type>(s));
		}
	}
	tree = build_tree(queue1);

	fseek(fp_i, HEAD_SIZE + var * (sizeof(cap_type) + sizeof(short int)) + 2, SEEK_SET);
	curLocation = ftell(fp_i);

	fread(&value, sizeof(unsigned short int), 1, fp_i);
	curLocation = ftell(fp_i);
	tree.haptr = tree.root;
	while (1) {
		if (curLocation>=fileSize) {
			break;
		}
		
		if (GET_BYTE(value, index)) {
			tree.haptr = tree.haptr->leftchild;
		}
		else {
			tree.haptr = tree.haptr->rightchild;
		}
		if (!tree.haptr) {
			cout << "BUG";
			return;
		}
		if (tree.haptr->data) {
			sum += tree.haptr->data;
			fwrite(&tree.haptr->data, sizeof(cap_type), 1, fp_o);
			tree.haptr = tree.root;
		}
		index++;
		if (index >= 16) {
			index = 0;
			fread(&value, sizeof(unsigned short int), 1, fp_i); 
			curLocation = ftell(fp_i);
			//cout << value << "  INcapsule_value" << endl;

		}
	}
	cout << index << "  trash" << trash << "  value" << value << endl;
	
	for (index; index < trash; index++) {

		if (GET_BYTE(value, index)) {
			tree.haptr = tree.haptr->leftchild;
		}
		else {
			tree.haptr = tree.haptr->rightchild;
		}		if (!tree.haptr) {
			cout << "BUG";
			return;
		}
		if (tree.haptr->data) {
			sum += tree.haptr->data;
			fwrite(&tree.haptr->data, sizeof(cap_type), 1, fp_o);
			tree.haptr = tree.root;
		}
	}
	cout << "解压数据: " << sum << endl<< endl<< endl;
}

int main() {

	string filename1,filename2;
	string order;
	cin >> order;
	if (order=="压缩") {
		cout << "输入需要压缩的文件名";
		cin >> filename1;
		cout << "输入压缩后的文件名";
		cin >> filename2;
		capsule(filename1.c_str(), filename2.c_str());
	}
	else if (order == "解压") {
		cout << "输入需要解压的文件名";
		cin >> filename1;
		cout << "输入解压后的文件名";
		cin >> filename2;
		incapsule(filename1.c_str(), filename2.c_str());
	}

}