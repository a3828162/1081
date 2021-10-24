#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int main(){
	
	int a=0, b=0, c=0, height=0, weight=0;
	
	cin >> a >> b >> c;
	
	char* q;
	q = new char [c]();
	
	for(int i=0;i<c;i++){
		cin >> q[i];
	}
	
	for(int i=0;i<c;i++){
		
		if(q[i]=='U')
			height++;
		else if(q[i]=='D')
			height--;
		else if(q[i]=='L')
			weight--;
		else if(q[i]=='R')
			weight++;
			
		if((height<0||height>a-1)||(weight<0||weight>b-1)){
			cout << "invalid" << endl;
			break;
		}else if(i==c-1){
			cout << "valid" << endl;
		}
	}
	
	delete []q;
	
	return 0;
}
