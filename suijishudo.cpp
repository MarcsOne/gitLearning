#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<vector>
#include<fstream>
/*
9x9数独按照3x3矩阵可以从上到下从左到右编号为1,2,3,4,5,6,7,8,9号矩阵
这个随机数独生成方法是先随机生成1,5,9号矩阵，然后通过回溯法分别去生成3,7,2,4,6,8号矩阵
然而这个方法实践了很久，尚未写出合适的代码，以下代码只是实现的一部分，仍有错误需要修改
*/

using namespace std;

const int SIZE = 9;
vector<vector <int> > num(SIZE, vector<int>(SIZE));
int temp[SIZE];


void generate1to9() {

	for (int k = 0; k < 9; k++) {
		temp[k] = 0;
	}//初始化数组 
	for (int i = 0; i<9; i++) {
		temp[i] = 1 + rand() % 9;                //得到随机数(范围在1-9之间)
		for (int j = 0; j<i; j++)                 //判断和前面的数是否重复
			if (temp[i] == temp[j]) { i--; break; }  //如果重复,重新产生随机数
	}//产生9个随机数

}
// 随机产生1-9不重复的数，结果填到temp数组中 

void init() {
	generate1to9();
	for (int i = 0, k = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++, k++) {
			if (i == 0 && j == 0) num[i][j] = (3 + 2) % 9 + 1;
			else {

				if (temp[k] == 6) k++;
				num[i][j] = temp[k];
			}
		}
	}

	generate1to9();
	for (int i = 3, k = 0; i < 6; i++) {
		for (int j = 3; j < 6; j++, k++) {
			num[i][j] = temp[k];
		}
	}

	generate1to9();
	for (int i = 6, k = 0; i < 9; i++) {
		for (int j = 6; j < 9; j++, k++) {
			num[i][j] = temp[k];
		}
	}
}
// 随机初始化编号为1,5,9的中间三个3*3矩阵
bool IsSuitable(int row, int col) {
	int n = num[row][col];
	for (int i = 0; i < row; i++) {
		if (num[i][col] == n) return false;
	}   												//判断n是否已经存在所在列 
	for (int i = 0; i < col; i++) {
		if (num[row][i] == n) return false;
	}  													//判断n是否已经存在所在行 
	int RowStart = row / 3;
	RowStart *= 3;
	int RowEnd = RowStart + 2;
	int ColStart = col / 3;
	ColStart *= 3;
	int ColEnd = ColStart + 2;
	int i = RowStart, j = ColStart;  					//RowStart,RowEnd,ColStart,ColEnd标志该位置所在的九宫格的起始	

	for (int k = 1; k <= 8; k++) {
		if (row != i || col != j) {
			if (num[i][j] == n) return false;
		}
		else  break;                                    //判别所给数字是否与九宫格中的数字存在冲突 
		if (j == ColEnd) {
			j = ColStart;
			i++;
		}
		else {
			j++;
		}
	}  return true;
}

bool generate(int beginrow, int begincol, int endrow, int endcol) {
	int row = beginrow;
	int col = begincol;
	vector<int> number;
	for (int i = 1; i <= 9; i++)
		number.push_back(i);
	while (!number.empty()) {
		int randindex = rand() % number.size();
		int randnum = number[randindex];
		number.erase(number.begin() + randindex);
		num[row][col] = randnum;
		if (!IsSuitable(row, col))
			continue;
		if (row == endrow && col == endcol) {
			return true;
		}
		int nextrow, nextcol;
		if (col == endcol) {
			nextrow = row + 1;
			nextcol = col;
		}
		else {
			nextrow = row;
			nextcol = col + 1;
		}
		bool next = generate(nextrow, nextcol, endrow, endcol);
		if (next)  return true;
	}
	if (number.empty()) {
		num[row][col] = 0;
		return false;
	}
}  																			//为指定3X3矩阵赋值 


void output() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %d", num[i][j]);
		}
		printf("\n");
	}

}  //打印输出 
int main() {


	init();
	srand((unsigned)time(NULL));
	output();
	cout << "--------------------------" << endl;
	generate(0, 6, 2, 8);
	output();

	system("pause");
	return 0;
}

