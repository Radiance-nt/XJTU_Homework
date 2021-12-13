#pragma once
#include<iostream>
#include<string>
using namespace std;

extern string Haf_tab[256];
template<typename T>
class node {
public:
	T data;
	node* leftchild, * rightchild;
	int weight;
	node() {
		data = NULL;
		weight = 0;
		leftchild = NULL;
		rightchild = NULL;
	}
	node(const T x, int n) {
		data = x;
		weight = n;
		leftchild = NULL;
		rightchild = NULL;
	}
};

template<typename T>
class BT {
private:
	string str;
	void in_order_(node<T>* n) {
		if (n->leftchild) {
			str += '1';
			in_order_(n->leftchild);
			str.pop_back();
		}
		if (n->data) {
			Haf_tab[n->data] = str;
		}
		if (n->rightchild) {
			str += '0';
			in_order_(n->rightchild);
			str.pop_back();
		}
	}

public:
	node<T>* root,* haptr=root;
	int weight = 0;
	BT(node<T>* n) {
		createTree(n);
	}
	BT() {
		root = NULL;
	}
	void createTree(BT* tree1, BT* tree2) {
		root = new node<T>;
		root->leftchild = tree1->root;
		root->rightchild = tree2->root;
		root->weight = tree1->weight + tree2->weight;
		weight = root->weight	;
	}


	void createTree(node<T>* n) {
		root = n;
		weight = root->weight;
	};
	void in_order() {
		in_order_(root);
	}

	string findchar(const char* ptr) {
		return Haf_tab[*ptr];
	}

}



;