#include <iostream>
#include <math.h>
using namespace std;

int main(){
	int k,kcpy;
	int num,i,s,c; //�]�w�ܼ� 
	int icpy,scpy,ccpy;
	cout << "Enter a positive decimal integer of at most 8 digits:";
	cin  >> num;
	cout << "The binary equivalent of " << num;
	cout << " is ";

	int numcpy=num;

	for(c=0;;c++){ //�Φ�Ʒ�}�C����� 
		k=num / pow(2,c);  
		if(k==0){
			s = c-1;
			break;
		}		
	}
	
	int n[s];
	
	for(i=0;i<=s;i++,num/=2){ // ������� 
		n[i]=num%2; //��Ʀr���}�C 
	}
	
	for(i=s;i>=0;i--){
		cout << n[i]; //�Ͽ�X 
	}
	cout << endl;
	
	cout << "The octal equivalent of " << numcpy;
	cout << " is ";
	
	for(ccpy=0;;ccpy++){
		kcpy=numcpy / pow(8,ccpy);
		if(kcpy==0){
			scpy = ccpy-1;
			break;
		}		
	}

	int ncpy[scpy];
	
	for(icpy=0;icpy<=scpy;icpy++,numcpy/=8){
		ncpy[icpy]=numcpy%8;
	}

	for(icpy=scpy;icpy>=0;icpy--){
		cout << ncpy[icpy];
	}
	
	cout << endl;	
			
	system( "pause" );		
}
