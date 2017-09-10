#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<vector>
#include<fstream>

using namespace std;

int temp[9];
int num[9][9];

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

char model[9][9] = {
	{ 'i','g','h','c','a','b','f','d','e' },{ 'c','a','b','f','d','e','i','g','h' },{ 'f','d','e','i','g','h','c','a','b' },{ 'g','h','i','a','b','c','d','e','f' },{ 'a','b','c','d','e','f','g','h','i' },{ 'd','e','f','g','h','i','a','b','c' },{ 'h','i','g','b','c','a','e','f','d' },
	{ 'b','c','a','e','f','d','h','i','g' },{ 'e','f','d','h','i','g','b','c','a' }
};


void init()
{
	generate1to9();
	for (int i = 0; i<9; i++) {
		if (temp[i] == 6) {
			temp[i] = temp[8];
			temp[8] = 6;
		}
	}

}

void generator()
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			if (model[i][j] == 'a') num[i][j] = temp[0];
			else if (model[i][j] == 'b') num[i][j] = temp[1];
			else if (model[i][j] == 'c') num[i][j] = temp[2];
			else if (model[i][j] == 'd') num[i][j] = temp[3];
			else if (model[i][j] == 'e') num[i][j] = temp[4];
			else if (model[i][j] == 'f') num[i][j] = temp[5];
			else if (model[i][j] == 'g') num[i][j] = temp[6];
			else if (model[i][j] == 'h') num[i][j] = temp[7];
			else if (model[i][j] == 'i') num[i][j] = temp[8];
		}
	}
}

void output()
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			printf(" %d", num[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	clock_t start, finish;

	double totaltime;

	start = clock();
	int n;
	printf("请输入您要生成的数独矩阵个数:\n");
	int CharJduge = scanf_s("%d", &n);
	for (int i = 0; i<n; i++)
	{
		init();
		generator();
		output();
		printf("\n");
	}
	finish = clock();

	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;

	cout << "\n此程序的运行时间为" << totaltime << endl;
	system("pause");
	return 0;
}