#include <iostream>
using namespace std;

int GCD( int i, int j){
	if(i%j!=0)
		return GCD( j, i%j);
	else
		return j;
}

int main(){
	
	int N, G;
	while( cin >> N && N != 0){
		G = 0;
		for( int i=1; i<N; i++){
			for( int j=i+1; j<=N; j++){
				G += GCD(i,j);
			}
		}
		cout << G << endl;
	}
	
	return 0;
}
