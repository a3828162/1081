#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

float findMedianScore(int *ptrScore, int amounts){
	int temp; //設一個暫存 
	for( int i=0; i<amounts-1; i++){
		for( int j=0; j<amounts-1; j++){
			if( *(ptrScore+j) > *(ptrScore+j+1) ){  
				temp = *(ptrScore+j);  //把比較大的放入暫存 
				*(ptrScore+j) = *(ptrScore+j+1); //交換 
				*(ptrScore+j+1) = temp; //把暫存放入j+1 
			}
		}
	}
	cout << "After:  "; //輸出排序後的 
	for(int i=0; i<10; i++){
		cout << *(ptrScore+i) << setw(5) << right;
	}
	cout << endl;
	
	if(amounts%2==0){ //判斷奇偶數  回傳不同值 
		return(*(ptrScore+amounts/2)+*(ptrScore+amounts/2-1));
	}else{
		return(*(ptrScore+(amounts-1)/2));
	}
}

int main(){
	
	srand(time(NULL));
	int studentScore[10]={};
	for(int i=0; i<10; i++){
		studentScore[i] = rand()%101; //變數存入陣列 
	}
	cout << "Before: ";
	for(int i=0; i<10; i++){ //排序前 
		cout << studentScore[i] << "   ";
	}
	cout << endl;
	int size = sizeof(studentScore)/sizeof(studentScore[0]); //大小 
	float median = findMedianScore( studentScore, size); //丟到另一個function 
	if(size%2==0){
		median/=2;
	}
	cout << "Median: " << median;
	return 0;
} 


