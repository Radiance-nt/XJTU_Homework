#include<iostream>
#include<vector>
using namespace std;

template<typename Elem>
class node {
public:
	Elem data;
	bool on=1;
	int order;
	node* next;
	node() {
		data = 0;
		on = 1;
		order = 0;
		next = NULL;
	}
	node(Elem x,int index) {
		data = x;
		on = 1;
		order = index;
		next = NULL;
	}
};

template<typename Elem>
class CList {
private:
	node<Elem>* head=NULL;
	int length=0;
public:
	CList() {
		head = NULL;
		//head->next = head;
	}
	CList(Elem x) {
		head = new node<Elem>(x);
		head->next = head;
	}
	CList(vector<int> v) {
		vector<int>::iterator it = v.begin();
		addElem(*it);
		for (it = v.begin() + 1; it != v.end(); it++)
		{
			addElem(*it);
		}
	}

	void addElem(Elem e) {
		if (head == NULL) {
			head = new node<Elem>(e,length+1);
			head->next = head;
			length += 1;
		}
		else {
			node<Elem>* ptr;
			ptr = head;
			while (ptr->next != head) {
				ptr = ptr->next;
			}
			ptr->next = new node<Elem>(e, length+1);
			ptr->next->next = head;
			length += 1;
		}
	}


	void print() {     //遍历输出
		node<Elem>* ptr=head;
		while (ptr->next != head) {
			cout <<ptr->order<<"的密码是 "<< ptr->data <<endl;
			ptr = ptr->next;
		}
		cout << ptr->order << "的密码是 " << ptr->data << "  ";
		cout << endl;
	}



	void Jo(int m) {
		int pass = m, num = length;
		node<Elem>** p = &head, *ptr = head;
		while (num >0) {
			for (int i = 0; i < pass - 1; i++) {
				p = &(ptr->next);
				ptr = ptr->next;
			}
			num -= 1;
			pass = ptr->data;
			cout <<"第"<< length-num   <<"个出局的人是"<< ptr->order << endl;
			*p = ptr->next;
			delete[] ptr;
			ptr = *p;
			
		}
		return;

	}
};

int main() {
	CList<int> list;
	int m,n,password;
	cout <<"请输入初始密码值m和人数n" << endl;
	cin>>m>>n;
	for (int i = 0; i < n; i++) {
		cout <<"请输入第"<<i+1<< "人的密码 "  << endl;
		cin >> password;
		list.addElem(password);
	}
	cout << endl;
	cout << "###########" << endl;
	list.print();
	cout << endl;
	cout << "###########" << endl;
	list.Jo(m);
}