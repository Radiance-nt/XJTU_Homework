#include"AVL.h"
#include"BST.h"
#include"BSTL.h"
#include<iostream>
#include<vector>
using namespace std;
int num;
int j,flag;
string str;

int main() {
	vector<int> s;
	cout << "��������" << endl;
	cin >> str;

	cout << "�������" << endl;
	cin >> num;

	
	if (str == "AVL") {

		AVL<int>  tree;
		for (int i = 0; i < num; i++) {
			cout << "�����" << i + 1 << "��Ԫ��" << endl;
			cin >> j;
			tree.insert(j); 
			cout << "�������" << endl << endl;
			tree.in_order();
		}
		cout << "�����ɹ��������������" << endl;
		//tree.in_order();
		cout << "ƽ�����ҳ���" << endl;
		cout << tree.average_length() << endl;
		cout << endl << endl;
		cout << "�������" << endl;
		tree.in_order();
	}
	else if (str == "BST") {
		for (int i = 0; i < num; i++) {
			cout << "�����" << i + 1 << "��Ԫ��" << endl;
			cin >> j;
			s.push_back(j);
		}	
		BST<int>tree(s);
		cout << "�����ɹ��������������" << endl;
		tree.in_order();
		cout << "ƽ�����ҳ���" << endl;
		cout << tree.average_length()<<endl;
		cout << "����Ҫɾ����Ԫ��" << endl;
		cin >> num;
		tree.delete_node(num);
		cout << endl << endl;
		cout << "�������" << endl;
		tree.in_order();
	}
	else if (str == "BSTL") {
		for (int i = 0; i < num; i++) {
			cout << "�����" << i + 1 << "��Ԫ��" << endl;
			cin >> j;
			s.push_back(j);
		}
		BSTL<int>tree(s);
		cout << "�����ɹ��������������" << endl;
		tree.in_order();
		cout << tree.average_length() << endl;
		cout << tree.average_length();;
		cout << "����Ҫɾ����Ԫ��" << endl;
		cin >> num;
		tree.delete_node(num);
		cout << endl << endl;
		cout << "�������" << endl;
		tree.in_order();
	}
		
	else
		return -1;
	
	cout << endl << endl;
	
}