#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

float findMedianScore(int *ptrScore, int amounts){
	int temp; //�]�@�ӼȦs 
	for( int i=0; i<amounts-1; i++){
		for( int j=0; j<amounts-1; j++){
			if( *(ptrScore+j) > *(ptrScore+j+1) ){  
				temp = *(ptrScore+j);  //�����j����J�Ȧs 
				*(ptrScore+j) = *(ptrScore+j+1); //�洫 
				*(ptrScore+j+1) = temp; //��Ȧs��Jj+1 
			}
		}
	}
	cout << "After:  "; //��X�Ƨǫ᪺ 
	for(int i=0; i<10; i++){
		cout << *(ptrScore+i) << setw(5) << right;
	}
	cout << endl;
	
	if(amounts%2==0){ //�P�_�_����  �^�Ǥ��P�� 
		return(*(ptrScore+amounts/2)+*(ptrScore+amounts/2-1));
	}else{
		return(*(ptrScore+(amounts-1)/2));
	}
}

int main(){
	
	srand(time(NULL));
	int studentScore[10]={};
	for(int i=0; i<10; i++){
		studentScore[i] = rand()%101; //�ܼƦs�J�}�C 
	}
	cout << "Before: ";
	for(int i=0; i<10; i++){ //�Ƨǫe 
		cout << studentScore[i] << "   ";
	}
	cout << endl;
	int size = sizeof(studentScore)/sizeof(studentScore[0]); //�j�p 
	float median = findMedianScore( studentScore, size); //���t�@��function 
	if(size%2==0){
		median/=2;
	}
	cout << "Median: " << median;
	return 0;
} 


