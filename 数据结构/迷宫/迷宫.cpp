#include<iostream>
#include<string>
#include <sstream>
#include <fstream>
using namespace std;
string oneline;
const int m = 10, n =10;
int start_x, start_y,i,j;
int matrix[m][n];
ifstream infile1("puzzle.txt");


bool findway(int x, int y) {
	if (matrix[x][y] == 6)return true;
	if (matrix[x][y] == 7)return true;
	else if (matrix[x][y] == 1)return false;
	else if (matrix[x][y] == 4)return false;
	else if (matrix[x][y] == 2)return false;
	else {
		matrix[x][y] = 2;
		if (findway(x, y + 1)) {
			matrix[x][y] = 6;
			return true;
		}
		if (findway(x + 1, y)) {
			matrix[x][y] =6;
			return true;
		}
		if (findway(x, y - 1)) {
			matrix[x][y] = 6;
			return true;
		}
		if (findway(x-1,y)) {
			matrix[x][y] = 6;
			return true;
		}
	}
	matrix[x][y] = 4;
	return false;

}

int main() {
	if (!infile1.is_open())
		cout << "没打开" << endl;

	for (i = 0; i < m; i++) {
		getline(infile1, oneline);
		stringstream ss1(oneline);
		for (j = 0; j < n; j++) {
			ss1 >> matrix[i][j];
			if (matrix[i][j] == 9) {
				start_y =i; start_x = j;
			}
		}
	}
	if (findway(start_y, start_x)) {
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				if (matrix[i][j] == 4)cout << "  " << "";
				else if (matrix[i][j] == 0)cout << "  " << "";
				else if (matrix[i][j] == 1)cout << "■" << "";
				else if (matrix[i][j] == 6)cout << "▲" << "";
				else if (matrix[i][j] == 9)cout << "★" << "";
				else if (matrix[i][j] == 7)cout << "☆" << "";
				else cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else
		cout << "不可达";
}
