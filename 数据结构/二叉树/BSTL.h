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
#include<string>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

template<typename T>
class BSTL {
private:
	const int length = 100;
	T * root;
	string str;
	bool is_empty(int ii) {
		if (ii > length - 1)
			return true;
		if (!root[ii])
			return true;
		return false;
	}
	void createTree(const T x) {
		root = new T[length];
		for (int i = 0; i < length; i++) {
			root[i]=0;
		}
		root[1]= x;
	};

	void in_order_(int ii) {

		if ((ii<length-1)&&root[2 * ii]) {
			str += '1';
			in_order_(2 * ii);
			str.pop_back();
		}
		if ((ii < length - 1) &&root[ii]) {
			cout << root[ii] << endl;	
		}
		if ((ii < length - 1) &&root[2 * ii+1]) {
			str += '0';
			in_order_(2 * ii + 1);
			str.pop_back();
		}
	}
	int left(int& ii) {
		ii = ii * 2;
		return ii;
	}
	int right(int& ii) {
		ii = ii * 2 + 1;
		return ii;
	}

	void jie_max(int ii) {
		int jj = 2 * ii;
		queue<int> q;
		q.push(jj);
		int k = log2(ii) + 1, kj;
		while (!q.empty())
		{
			jj = q.front();
			if (!is_empty(2 * jj))
				q.push(2 * jj);
			if (!is_empty(2 * jj + 1))
				q.push(2 * jj + 1);
			kj = log2(jj) + 1;
			cout<< root[int(jj - ii * pow(2, kj - k - 1))] <<"->>"<< root[jj]<<endl;
			root[int(jj - ii* pow(2, kj - k - 1))] = root[jj];
			q.pop();
		}
		for (jj = 0; jj < pow(2, kj - k); jj++) {
			if (ii * pow(2, kj - k) + jj > length) break;
			root[int(ii * pow(2, kj - k) + jj)] = 0;

		}
	}
	void jie_min(int ii) {
		int jj = 2 * ii + 1;
		queue<int> q;
		q.push(jj);
		int k = log2(ii) + 1, kj;  //kΪ����
		while (!q.empty())
		{
			jj = q.front();
		
			if (!is_empty(2 * jj))
				q.push(2 * jj);
			if (!is_empty(2 * jj + 1))
				q.push(2 * jj + 1);
			kj = log2(jj) + 1;
			root[int(jj - (ii + 1) * pow(2, kj - k - 1))] = root[jj];
			q.pop();
		}
		for (jj = 0; jj < pow(2, kj - k ); jj++) {
			if (ii * pow(2, kj - k) + jj > length) break;
			root[int(ii * pow(2, kj - k )+jj)] = 0;

		}
	}
public:

	BSTL() {
		root = NULL;
	}
	BSTL(const T x) {
		createTree(x);
	}

	BSTL(vector<int> v) {
		vector<int>::iterator it = v.begin();
		createTree(*it);
		for (it = v.begin() + 1; it != v.end(); it++)
		{
			insert(*it);
		}
	}
	void in_order() {
		in_order_(1);
	}
	void out_put() {
		int j = 1;
		for (int i =1; i < length; i++) {
			cout << root[i] << "  ";
			if (i == 2*j-1) {
				j *= 2;
				cout << endl;
			}
		}
	}

	void insert(T in) {
		int ii = 1;
		while (ii < length - 1) {
			if (!root[ii]) {
				root[ii] = in;
				return;
			}
			if (in > root[ii])
			{
				right(ii);
			}
			else if (in <root[ii]) {
				left(ii);
			}
			else {
				return;
			}
		}
	}
	
	double average_length() {
		double sum = 0,n=0;
		stack<pair<int, int> > stk;
		if (is_empty(1))
			return 0;
		stk.push(make_pair(1, 1));
		while (!stk.empty()) {
			pair<int, int> p = stk.top();
			stk.pop();
			n += 1;
			if (!is_empty(p.first * 2)) 
				stk.push(make_pair(p.first * 2, p.second + 1));
			if (!is_empty(p.first * 2 + 1)) 
				stk.push(make_pair(p.first * 2 + 1, p.second + 1));
			sum += p.second;
			
		}
		return  (sum / n);
	}


	void delete_node(T in) {
		int ii = 1,jj; T* ptr=&root[ii];
		while (ii < length - 1) {
			if (!root[ii]) {
				cout << "������" << in << endl;
				return;
			}
			if (in > root[ii])
			{
				right(ii);
			}
			else if (in < root[ii]) {
				left(ii);
			}
			else {  
				if (is_empty(2 * ii) && is_empty(2 * ii + 1)) {//Ҷ�ӽ��
					root[ii] = 0;
				}
				else {
					jj = ii;
					if (!is_empty(2 * ii)) {
						left(jj);
						while (!is_empty(2*jj+1)) {
							right(jj);
						}
						root[ii] = root[jj];
						root[jj] = 0;//����ȥ
						jie_max(jj);
					}
					else {
						right(jj);
						while (!is_empty(2 * jj)) {
							left(jj);
						}
						root[ii] = root[jj];
						root[jj] = 0;//����ȥ
						jie_min(jj);
					}
				}
				return;
			}
		}
		cout << "������" << in << endl;
		return;
	}
}
;



