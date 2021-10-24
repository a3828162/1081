#include <iostream>
using namespace std;

int c( int a, int b);

int main(){
	
	int T=0;
	int sum=0;
	int a=0,b=0;
	int cases[101];
	cin >>  T;
	
	for( int i=1; i<=T; i++ ){
		cin >> a >> b;
		if(b%2==1){
			sum = c( a, b);
		}else if(b%2==0){
			b--;
			sum = c( a,b);
		}
		cases[i] = sum;
	}
	
	for( int i=1; i<=T; i++){
		cout << "Case " << i << ": " << cases[i] << endl;
	}
	
	return 0;
}

int c( int a, int b){
	if(b<a)
		return 0;
	else
		return c( a, b-2) + b;
}
