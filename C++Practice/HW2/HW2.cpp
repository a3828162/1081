#include <iostream>
using namespace std;

int main(){
	
	int pencils[4]={},ball[4]={};
	int a[4] = {};
	int x=0;	
	cout << "Please input the daily sales of pencils for the first four days( use a space to separate each character )";
	for( int i=0; i<4; i++)
		cin >> pencils[i];
	cout << "Please input the daily sales of ballpoint pens for the first four days( use a space to separateeach character )";
	for( int i=0; i<4; i++)
		cin >> ball[i];
	
	for( int k=0; k<5; k++){
		for(int i=0; i<4; i++){
			if( pencils[i]+ball[i]<=5){
				if( pencils[i]+ball[i]==5-k){
					if(pencils[i]>0){
						cout << "* " ;
						pencils[i]--;
					}else if(ball[i]>0){
						cout << "+ " ;
						ball[i]--;
					}
				}else{
					cout << "  ";
				}
			}else{
				x =1;
				goto  stop;
			}
		}

		cout << endl;	
	}
	
	for( int i = 0; i<4;i ++)
		a[i] +=i;	
	for( int i=0; i<4; i++)
		cout << a[i] << " ";
		
	
	stop:
		if(x==1)
			cout<< "Wrong  number" << endl;
	return 0;
} 




