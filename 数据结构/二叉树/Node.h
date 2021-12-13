#pragma once

template<typename T>
class node {
public:
	T data;
	node* leftchild, * rightchild;
	int height;
	node() {
		data = NULL;
		leftchild = NULL;
		rightchild = NULL;
		height = 1;
	}
	node(const T x) {
		data = x;
		leftchild = NULL;
		rightchild = NULL;
		height = 1;
	}
};