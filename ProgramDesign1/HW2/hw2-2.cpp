#include <iostream>
using namespace std;

int main(){
	
	int number,i;
	int a[8]={0,0,0,0,0,0,0,0}; //��}�C�k�s 
	int sum=0;
	
	cout << "enter a positive integer of at most 8 digits:";
	cin >> number;  
	cout << "The sum of all digits of " << number;
	
	for(i=0;i<=7;i++,number/=10){ //������� 
		a[i]=number%10;
		sum += a[i];
		if(number-10<0){    //�������� 
			break;
		}
	}
		
 	cout << " is " << sum << endl;
	
	system( "pause" );
}
