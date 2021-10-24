#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(){

    int random1, random2; //給兩個變數 
    double dize[6][6]={};  
    double possible[11];
    srand(time(NULL));
    
    for(int i=0; i<36000; i++){ //執行次數 
        random1=(rand()%6+1);  //變數1給質 
		random2=(rand()%6+1);  //變數2給質 
		for(int j=0; j<6; j++){
			for(int k=0; k<6; k++){
				if(j+1==random1&&k+1==random2){
					dize[j][k]++;  //條件達成次數+1 
				}
			}	
			if(j+1==random1){
				break;
			}
		}
    }
	cout << " ";
	for(int i=1; i<=6; i++)
		cout << setw(6) << i;
	cout << endl;	
	
	for(int i=0; i<6; i++){
		cout << i+1;
		for(int j=0; j<6; j++){
			cout << setw(6) << dize[j][i];  //輸出 
		}
		cout << endl;
	}	
	cout << endl << endl << endl;
	
	for(int i=1; i<12; i++){
		
		int add=0;  
		cout << "P" << "(" << i+1 << ")";
		cout << " = ";
		for(int j=0; j<6; j++){
			for(int k=0; k<6; k++){
				if(i+1==(j+1)+(k+1)){
					if(add)
						cout << "+ "; //排版 
					cout << "P(" << j+1 << "," << k+1 << ")"; //照格式輸出 
					cout << " ";
					add++;
					possible[i-1] += dize[j][k]/36000; //加總 
				}
			}
		} 
		
		cout << "= ";
		add=0;
		for(int j=0; j<6; j++){
			for(int k=0; k<6; k++){
				if(i+1==(j+1)+(k+1)){
					if(add)
						cout << "+ ";
					cout << setprecision(6) << fixed << dize[j][k]/36000; //小數點加法 
					cout << " ";
					add++;
				}

			}
		}
		
		cout << "= ";
		cout << possible[i-1];
		cout << endl << endl;
	}

	return 0;
}
