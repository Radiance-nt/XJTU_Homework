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
	cout << "输入种类" << endl;
	cin >> str;

	cout << "输入个数" << endl;
	cin >> num;

	
	if (str == "AVL") {

		AVL<int>  tree;
		for (int i = 0; i < num; i++) {
			cout << "输入第" << i + 1 << "个元素" << endl;
			cin >> j;
			tree.insert(j); 
			cout << "中序遍历" << endl << endl;
			tree.in_order();
		}
		cout << "建树成功、进行中序遍历" << endl;
		//tree.in_order();
		cout << "平均查找长度" << endl;
		cout << tree.average_length() << endl;
		cout << endl << endl;
		cout << "中序遍历" << endl;
		tree.in_order();
	}
	else if (str == "BST") {
		for (int i = 0; i < num; i++) {
			cout << "输入第" << i + 1 << "个元素" << endl;
			cin >> j;
			s.push_back(j);
		}	
		BST<int>tree(s);
		cout << "建树成功、进行中序遍历" << endl;
		tree.in_order();
		cout << "平均查找长度" << endl;
		cout << tree.average_length()<<endl;
		cout << "输入要删除的元素" << endl;
		cin >> num;
		tree.delete_node(num);
		cout << endl << endl;
		cout << "中序遍历" << endl;
		tree.in_order();
	}
	else if (str == "BSTL") {
		for (int i = 0; i < num; i++) {
			cout << "输入第" << i + 1 << "个元素" << endl;
			cin >> j;
			s.push_back(j);
		}
		BSTL<int>tree(s);
		cout << "建树成功、进行中序遍历" << endl;
		tree.in_order();
		cout << tree.average_length() << endl;
		cout << tree.average_length();;
		cout << "输入要删除的元素" << endl;
		cin >> num;
		tree.delete_node(num);
		cout << endl << endl;
		cout << "中序遍历" << endl;
		tree.in_order();
	}
		
	else
		return -1;
	
	cout << endl << endl;
	
}