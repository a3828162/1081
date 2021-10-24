#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int main() {
	
	while(1){
		int p1=0, p2=0;
		char num1[11] = {}, num2[11] = {}; //輸入數字 
		int n1[11] = {}, n2[11] = {}, sum[11] = {};
		cin >> num1 >> num2;
		for (int i = strlen(num1)-1; i>=0; i--) {
			n1[p1] = num1[i]-'0'; //放數字 
			p1++;
		}
		for (int i = strlen(num2)-1; i>=0; i--) {
			n2[p2] = num2[i]-'0';
			p2++;
		}

		int size;
		if (strlen(num1) > strlen(num2)) {
			size = strlen(num1);
		}
		else {
			size = strlen(num2);
		}
		if(size==1&&n1[0]==0&&n2[0]==0){ //結束條件 
			break;
		}	
		for(int i = 0; i < size; i++) {
			sum[i] = n1[i] + n2[i]; //加起來 
		}

		int carry=0;

		for (int i = 0; i < size; i++){
			if (sum[i] >= 10) {
				sum[i] -= 10;
				sum[i + 1]++; //進位 
				carry++;
			}
		}
		if(carry==1){
			cout << carry << " carry operation." << endl; //輸出有幾個進位 
		}else if(carry==0){
			cout << "No carry operation." << endl;
		}else{
			cout << carry << " carry operations." << endl;
		}
	}
	return 0;
}
