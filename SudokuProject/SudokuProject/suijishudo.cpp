#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<vector>
#include<fstream>
#include"text.h"
using namespace std;

/*
利用回溯法构造数独
修改了num[0][0]的赋值，只需在开始遍历时赋值，而不是在遍历的时候判断是否该位置为[0][0]，提高效率，减少运行时间
*/

const int SIZE = 9;
vector<vector <int> > num(SIZE, vector<int>(SIZE));

IsS IsSu;
Gen Gene;
ofstream ocout;//定义输出流的一个对象


bool IsS::IsSuitable(int row, int col) {
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
}  																	//判别该数填在该位置是否合适 

bool Gen::generate(int row, int col) {
	int nextrow, nextcol;
	vector<int> number;
	//if (row == 0 && col == 0) 
	//	number.push_back((3 + 2) % 9 + 1);			//应作业要求，矩阵第一个位置固定为6 
	//else
		for (int i = 1; i <= 9; i++)
			number.push_back(i);										//将1-9装入容器 
	while (!number.empty()) {
		int randindex = rand() % number.size();  				//随机产生1-9里的 1 个 数字num
		int randnum = number[randindex];
		number.erase(number.begin() + randindex);  				//删除索引位置的数据 
		num[row][col] = randnum;  								//将数据填在第row行，第col列 
		if (!IsSu.IsSuitable(row, col))
			continue;  											//如果 randnum不能填在number[row][col]这个位置，则继续循环找一个合适的数 
		if (row == SIZE - 1 && col == SIZE - 1) {
			return true;
		}  														//如果最右下角的空也填上了，返回ture，成功生成数独矩阵  
		if (col == SIZE - 1) {
			nextrow = ++row;
			nextcol = 0;
		}  														//如果探索到最后一列，则换行 
		else {
			nextrow = row;
			nextcol = ++col;
		}  														//nextrow，nextcol指向下一个空格 
		bool next = generate(nextrow, nextcol);						//递归遍历整个数独矩阵  
		if (next)  return true; 								 	//当返回ture时 矩阵成功生成
	}
	if (number.empty()) {
		
		return false;
	} 															//生成的时候卡住了便回溯上一层 

}

/*
void outputTocmd() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %d", num[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}*/
//打印输出到屏幕
void outputTotext() {


	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			ocout << num[i][j] << " ";
		}
		ocout << "\n";
	}
	ocout << "\n";
	
}
//打印输出到文件

int main() {

	//clock_t start, finish;

	//double totaltime;

	//start = clock();

	int N;
	ocout.open("sudotext.txt");
	printf("请输入您要生成的数独矩阵个数:\n");
	int CharJduge = scanf_s("%d", &N);
	if (!CharJduge) {
		printf("输入只能为数字,请重新输入\n");
		system("pause");
		return 0;
	}
	//srand((unsigned)time(NULL));

	ocout << "您请求的生成的" << N << "个随机数独矩阵如下:" << endl;
	for (int i = 0; i<N; i++) {
		num[0][0] = 6;
		Gene.generate(0, 1); 													//从0,0位置开始遍历生成随机数独矩阵 
		outputTotext();
	//	outputTocmd();
	}
	ocout.close();

	//finish = clock();

	//totaltime = (double)(finish - start) / CLOCKS_PER_SEC;

	//cout << "\n此程序的运行时间为" << totaltime<<endl;

	system("pause");

	return 0;
}
