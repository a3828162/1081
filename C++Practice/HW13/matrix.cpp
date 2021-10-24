using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "matrix.h"

int **load(ifstream &data, int nm[]) {

	stringstream sn,sm;
	string input,output;
	data >> input;
	sn << input;
	int i = 0;
	while (getline(sn, output, ',')) { //��Ū�x�}��C��
		sm.str("");
		sm.clear();
		sm << output;
		sm >> nm[i];
		i++;
	}
	sn.str("");
	sn.clear();
	int** d = new int* [nm[0]](); //�ŧi�G���}�C
	for (int k = 0; k < nm[0]; k++) {
		d[k] = new int[nm[1]]();
	}
	/*while (data >> input) {
		sn.str("");
		sn.clear();
		sn << input;
		cout << input << endl;
	}*/
	//i = 0;
	int j = 0;
	int k;
	while (data >> input) { //��Ʀr��J�}�C
		i = 0;
		sn.str("");
		sn.clear();
		sn << input;
		//cout << input << endl;
		while (getline(sn, output, ',')) {
			sm.str("");
			sm.clear();
			//cout << output << endl;
			sm << output;
			sm >> k;
			//cout << k << endl;
			d[j][i] += k;
			i++;
		}
		j++;
	}


	//cout << d[0][0] << endl;


	return d;
}

int **matrix(int** mat1, int** mat2, int col1,int col2, int col3, int row1, int row2, int row3) {


	int** result = new int* [col3](); //�ŧi
	for (int i = 0; i < col3; i++) {
		result[i] = new int[row3]();
	}

	for (int i = 0; i < row3; i++) { //�p��
		for (int j = 0; j < col3; j++) {
			for (int k = 0; k < col2; k++) {
				result[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}

	return result;
}

int printMatrix(int** mat, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << mat[i][j] << "  "; //��X 
		}
		cout << endl;
	}

	return 0;
}