#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<vector>
#include<fstream>
using namespace std;
/*
������һ����ʵ���˽���1�����磬��û�гɹ���������´����ʹ�û��ݷ������������������
*/
const int SIZE = 9;
vector<vector <int> > num(SIZE, vector<int>(SIZE));
int temp[SIZE];

ofstream ocout;//�����������һ������



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
}  																	//�б�������ڸ�λ���Ƿ���� 

bool generate(int row, int col) {
	int nextrow, nextcol;
	vector<int> number;
	if (row == 0 && col == 0) number.push_back((3 + 2) % 9 + 1);			//Ӧ��ҵҪ�󣬾����һ��λ�ù̶�Ϊ6 
	else
		for (int i = 1; i <= 9; i++)
			number.push_back(i);										//��1-9װ������ 
	while (!number.empty()) {
		int randindex = rand() % number.size();  				//�������1-9��� 1 �� ���� 
		int randnum = number[randindex];   						//���������Ϊnumber������һ������ָ�룬������λ�õ����ݱ�����randnum��
		number.erase(number.begin() + randindex);  				//ɾ������λ�õ����� 
		num[row][col] = randnum;  								//���������ڵ�row�У���col�� 
		if (!IsSuitable(row, col))
			continue;  											//��� randnum��������number[row][col]���λ�ã������ѭ����һ�����ʵ��� 
		if (row == SIZE - 1 && col == SIZE - 1) {
			return true;
		}  														//��������½ǵĿ�Ҳ�����ˣ�����ture���ɹ�������������  
		if (col == SIZE - 1) {
			nextrow = ++row;
			nextcol = 0;
		}  														//���̽�������һ�У����� 
		else {
			nextrow = row;
			nextcol = ++col;
		}  														//nextrow��nextcolָ����һ���ո� 
		bool next = generate(nextrow, nextcol);						//�ݹ����������������  
		if (next)  return true; 								 	//������tureʱ ����ɹ�����
	}
	if (number.empty()) {
		num[row][col] = 0;
		return false;
	} 															//���ɵ�ʱ��ס�˱������һ�� 

}

void outputTocmd() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %d", num[i][j]);
		}
		printf("\n");
	}
	printf("-------------------------------");
	printf("\n");
}
//��ӡ�������Ļ
void outputTotext() {


	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			ocout << num[i][j] << " ";
		}
		ocout << "\n";
	}
	ocout << "-------------------------------";
	ocout << "\n";
}
//��ӡ������ļ�

int main() {
	int N;
	ocout.open("data.txt");
	printf("��������Ҫ���ɵ������������:\n");
	int CharJduge = scanf_s("%d", &N);
	if (!CharJduge) {
		printf("����ֻ��Ϊ����,����������\n");
		system("pause");
		return 0;
	}
	srand((unsigned)time(NULL));

	ocout << "����������ɵ�" << N << "�����������������:" << endl;
	for (int i = 0; i<N; i++) {
		generate(0, 0); 													//��0,0λ�ÿ�ʼ������������������� 
		outputTotext();
		outputTocmd();
	}
	ocout.close();
	system("pause");
	return 0;
}