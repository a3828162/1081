#include <iostream>
using namespace std;

int main(){
	
	int h,t,s; //�]�T���ܼ� 
	cout << "all Armstrong numbers of three digits:" << endl;
	
	for(h=1;h<=9;h++){   //h�ʦ�� t�Q��� s�Ӧ�� 
		for(t=0;t<=9;t++){
			for(s=0;s<=9;s++){
				int sum=h*100+t*10+s;
				if(sum==h*h*h+t*t*t+s*s*s) // �ŦX���󪺿�X 
					cout << sum << "   ";
			}
		}
	}
	cout << endl;
	system( "pause" );			
}
