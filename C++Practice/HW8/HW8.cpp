#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h> 
using namespace std;
const int row=3, col=3;

int createMatrixFromArray(int** &mat, int*sample){
	mat = new int*[row]();
	for(int i=0; i<row; i++){
		mat[i] = new int[col]();  //製造二元陣列 
	}
	int k=0;

	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			mat[i][j] = *(sample+k); //把測資的值放入二元陣列 
			k++;
		}
	}
}
	
int** multiplicateMatrix(int** mat1, int** mat2){
	
	int **result = new int*[row](); //定一個新的二元陣列 
	for(int i=0; i<col; i++){
		result[i] = new int[col]();
	}
	
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			for(int k=0; k<col; k++){
				result[i][j] += mat1[i][k]*mat2[k][j]; //陣列的乘法 
			}
		}
	}
	
	return result;	//回傳 
}
	
int destroyMatrix(int** mat){
	for(int i=0; i<row; i++){
		delete []mat[i];  //刪除二元陣列 
	}
	delete []mat;	//刪除陣列 
}
	
int printMatrix(int** mat){
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			cout << mat[i][j] << "  "; //輸出 
		}
		cout << endl;
	}		
} 

int main(){
	
	
	srand(time(NULL));
	int sample1[row*col] = {48,69,8,24,79,24,32,59,10};//給測資 
	int sample2[row*col] = {18,26,47,90,31,36,2,47,98};	
	int **mat1 =NULL;
	int **mat2 =NULL;
	
	createMatrixFromArray( mat1, sample1);//製造二元陣列 
	createMatrixFromArray( mat2, sample2);
	
	int **result = multiplicateMatrix( mat1, mat2); //乘法結果 
	cout << "mat1" << endl; //輸出 
	printMatrix(mat1);
	cout << endl << endl;
	cout << "mat2" << endl;
	printMatrix(mat2);
	cout << endl << endl;
	cout << "result" << endl;
	printMatrix(result);
	
	destroyMatrix(mat1); //刪除 
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
