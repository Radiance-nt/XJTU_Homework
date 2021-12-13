/*	 
(1)�ö����������洢�ṹʵ�ֶ�����������
1)�Իس���(��\n��)Ϊ���������־����������L������һ�ö�������
��T��
2)�Զ���������T�������������������
3)�������������T���ҳɹ���ƽ�����ҳ��ȣ���������
4)����Ԫ��x�����Ҷ���������T�������ں�x�Ľ�㣬��ɾ���ý�
�㣬�����������(ִ�в���2)�����������Ϣ����x����
*/
#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include "Node.h"
using namespace std;

template<typename T>
class BST {
private:
	node<T>* root;
	int total = 0;
	int ceng = 0;
	void createTree(const T x) {
		root = new node<T>(x);
	};

	void in_order_(node<T>* n) {
		if (n->leftchild) {
			in_order_(n->leftchild);
		}
		if (n->data) {
			cout << n->data<<"  "<< endl;
		}
		if (n->rightchild) {
			in_order_(n->rightchild);
		}
	}

	int insert_(int in, node<T>*& ptr) {

		if (ptr == NULL) {
			ptr = new node<int>(in);
			return 0;
		}
		if (in == ptr->data)
			return 1;
		int k = insert_(in, (in > ptr->data ? ptr->rightchild : ptr->leftchild));
		return 0;
	}

	node<T>*  find_max(node<T>* n) {
		if (n == NULL)return n;
		if (n->rightchild == NULL) {
			return n;
		}
		return find_max(n->rightchild);
	}
	void cut_max(node<T>* n, node<T>* cut) {
		if (n->leftchild == NULL)return;

		if (n->leftchild == cut) {
			n->leftchild = cut->leftchild;
			return;
		}
		n = n->leftchild;
		while (n->rightchild) {
			if (n->rightchild == cut) {
				n->rightchild = cut->leftchild; break;
			}
			n = n->rightchild;
		}
	}

	node<T>* find_min(node<T>* n) {
		if (n== NULL)return n;
		if (n->leftchild == NULL)
			return n;
		return find_min(n->leftchild);
	}
	void cut_min(node<T>* n, node<T>* cut) {
		if (n->rightchild == NULL)return;
		if (n->rightchild == cut) {
			n->rightchild = cut->rightchild;
			return;
		}
		n = n->rightchild;
		while (n->leftchild) {
			if (n->leftchild == cut){
				n->leftchild = cut->rightchild; break;
			}
			n = n->leftchild;
		}
	}

public:
	
	BST() {
		root = NULL;
	}
	BST(const T x) {
		createTree(x);
	}
	BST (vector<int> v) {
		vector<int>::iterator it =v.begin();
		createTree(*it);
		for (it = v.begin()+1; it != v.end(); it++)
		{	
			insert(*it);
		}
	}
	void in_order() {
		in_order_(root);
	}


	void insert(int in) {
		int k = insert_(in, root);
	}
	double average_length() {
		double sum = 0, n = 0;
		stack<pair<node<int>*, int> > stk;
		if (!root)
			return 0;
		stk.push(make_pair(root, 1));
		while (!stk.empty()) {
			pair<node<int>*, int> p = stk.top();
			stk.pop();
			n += 1;
			if (p.first->leftchild)
				stk.push(make_pair(p.first->leftchild, p.second + 1));
			if (p.first->rightchild)
				stk.push(make_pair(p.first->rightchild, p.second + 1));
			sum += p.second;

		}
		return  (sum / n);

	}
	void delete_node(int x) {
		node<int>* ptr = root,*ptb,*temp,**motherptr =&root;
		while (ptr != NULL) {
			if (x == ptr->data) {            //temp������С�ڵ�
				if ((ptr->leftchild==nullptr)&& (ptr->rightchild == nullptr)) {   //����������Ϊ��
					delete[] ptr;
					*motherptr = nullptr;
					cout << "ɾ���ɹ�"<<endl; in_order();
					return;
				}
				temp = find_max(ptr->leftchild);
				if (temp!=NULL) {
					ptr->data = temp->data;
					//temp->rightchild = ptr->rightchild;
					cut_max(ptr, temp);
					
				} 
				else {
					
					temp = find_min(ptr->rightchild);
					ptr->data = temp->data;
					cut_min(ptr, temp);
				//	temp->leftchild = ptr->leftchild;
					
				}
				delete[] temp;
				//delete [] ptr;
				//*motherptr = temp;
				cout << "ɾ���ɹ�"<<endl; 
				return;
			}
			motherptr = x> ptr->data ? &(ptr->rightchild) : &(ptr->leftchild);
			ptr = *motherptr;
		}
		cout << "��x";
		return;
	}

}
;



