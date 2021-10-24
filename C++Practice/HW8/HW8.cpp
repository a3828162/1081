#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h> 
using namespace std;
const int row=3, col=3;

int createMatrixFromArray(int** &mat, int*sample){
	mat = new int*[row]();
	for(int i=0; i<row; i++){
		mat[i] = new int[col]();  //�s�y�G���}�C 
	}
	int k=0;

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			mat[i][j] = *(sample+k); //����ꪺ�ȩ�J�G���}�C 
			k++;
		}
	}
}
	
int** multiplicateMatrix(int** mat1, int** mat2){
	
	int **result = new int*[row](); //�w�@�ӷs���G���}�C 
	for(int i=0; i<col; i++){
		result[i] = new int[col]();
	}
	
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			for(int k=0; k<col; k++){
				result[i][j] += mat1[i][k]*mat2[k][j]; //�}�C�����k 
			}
		}
	}
	
	return result;	//�^�� 
}
	
int destroyMatrix(int** mat){
	for(int i=0; i<row; i++){
		delete []mat[i];  //�R���G���}�C 
	}
	delete []mat;	//�R���}�C 
}
	
int printMatrix(int** mat){
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			cout << mat[i][j] << "  "; //��X 
		}
		cout << endl;
	}		
} 

int main(){
	
	
	srand(time(NULL));
	int sample1[row*col] = {48,69,8,24,79,24,32,59,10};//������ 
	int sample2[row*col] = {18,26,47,90,31,36,2,47,98};	
	int **mat1 =NULL;
	int **mat2 =NULL;
	
	createMatrixFromArray( mat1, sample1);//�s�y�G���}�C 
	createMatrixFromArray( mat2, sample2);
	
	int **result = multiplicateMatrix( mat1, mat2); //���k���G 
	cout << "mat1" << endl; //��X 
	printMatrix(mat1);
	cout << endl << endl;
	cout << "mat2" << endl;
	printMatrix(mat2);
	cout << endl << endl;
	cout << "result" << endl;
	printMatrix(result);
	
	destroyMatrix(mat1); //�R�� 
	destroyMatrix(mat2);
	destroyMatrix(result);	

	/*for(int i=0; i<row; i++){
		delete []mat1[i];
	}
	for(int i=0; i<row; i++){
		delete []mat1[i];
	}		
	delete []mat1;
	delete []mat2;*/
	return 0;
}
