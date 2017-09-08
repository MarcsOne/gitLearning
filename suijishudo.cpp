#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<vector>
#include<fstream>
/*
9x9��������3x3������Դ��ϵ��´����ұ��Ϊ1,2,3,4,5,6,7,8,9�ž���
�������������ɷ��������������1,5,9�ž���Ȼ��ͨ�����ݷ��ֱ�ȥ����3,7,2,4,6,8�ž���
Ȼ���������ʵ���˺ܾã���δд�����ʵĴ��룬���´���ֻ��ʵ�ֵ�һ���֣����д�����Ҫ�޸�
*/

using namespace std;

const int SIZE = 9;
vector<vector <int> > num(SIZE, vector<int>(SIZE));
int temp[SIZE];


void generate1to9() {

	for (int k = 0; k < 9; k++) {
		temp[k] = 0;
	}//��ʼ������ 
	for (int i = 0; i<9; i++) {
		temp[i] = 1 + rand() % 9;                //�õ������(��Χ��1-9֮��)
		for (int j = 0; j<i; j++)                 //�жϺ�ǰ������Ƿ��ظ�
			if (temp[i] == temp[j]) { i--; break; }  //����ظ�,���²��������
	}//����9�������

}
// �������1-9���ظ�����������temp������ 

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
// �����ʼ�����Ϊ1,5,9���м�����3*3����
bool IsSuitable(int row, int col) {
	int n = num[row][col];
	for (int i = 0; i < row; i++) {
		if (num[i][col] == n) return false;
	}   												//�ж�n�Ƿ��Ѿ����������� 
	for (int i = 0; i < col; i++) {
		if (num[row][i] == n) return false;
	}  													//�ж�n�Ƿ��Ѿ����������� 
	int RowStart = row / 3;
	RowStart *= 3;
	int RowEnd = RowStart + 2;
	int ColStart = col / 3;
	ColStart *= 3;
	int ColEnd = ColStart + 2;
	int i = RowStart, j = ColStart;  					//RowStart,RowEnd,ColStart,ColEnd��־��λ�����ڵľŹ������ʼ	

	for (int k = 1; k <= 8; k++) {
		if (row != i || col != j) {
			if (num[i][j] == n) return false;
		}
		else  break;                                    //�б����������Ƿ���Ź����е����ִ��ڳ�ͻ 
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
}  																			//Ϊָ��3X3����ֵ 


void output() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %d", num[i][j]);
		}
		printf("\n");
	}

}  //��ӡ��� 
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

