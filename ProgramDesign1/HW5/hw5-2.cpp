#include <iostream>
using namespace std;

int sum(int number);

int main(){
	
	int number;
	while(cin >> number && number!=0){
		cout << sum(number) << endl;
	}
	
	return 0;
}

int sum( int number){
	if(number<10){
		return number;
	}else{
		int total=0;
		while(number>0){
			total += number%10;
			number/=10;
		}
		return sum(total);
	}
	
}
