#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

vector<string> b;

bool same(int len,int q){
	for(int i=0;i<=len;i++){
		if(b[0][b[0].size()-(len-i)-1]!=b[q][i]){
			return false;
		}
	}
	return true;
}

int main(){
	
	int a=0;
	
	cin >> a;
	
	for(int i=0;i<a;i++){
		string c;
		cin >> c;
		b.push_back(c);
	}
	
	for(int i=1;i<b.size();i++){
		int len=b[i].size();
		for(int j=len-1;j>=0;j--){
			if(same(j,i)){
				for(int w=j+1;w<len;w++){
					b[0] += b[i][w];
				}
				break;
			}else if((!same(j,i))&&(j==0)){
				for(int w=0;w<len;w++){
					b[0] += b[i][w];
				}
				break;
			}
		}
	}
	
	cout << b[0] << endl;
	
	return 0;
}
