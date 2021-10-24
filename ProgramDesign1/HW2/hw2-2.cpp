#include <iostream>
using namespace std;

int main(){
	
	int number,i;
	int a[8]={0,0,0,0,0,0,0,0}; //把陣列歸零 
	int sum=0;
	
	cout << "enter a positive integer of at most 8 digits:";
	cin >> number;  
	cout << "The sum of all digits of " << number;
	
	for(i=0;i<=7;i++,number/=10){ //執行條件 
		a[i]=number%10;
		sum += a[i];
		if(number-10<0){    //結束條件 
			break;
		}
	}
		
 	cout << " is " << sum << endl;
	
	system( "pause" );
}
