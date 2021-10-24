#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;

vector<char> result;
vector<bool> inspect;
vector<int> data1, data2;

int find( int n){
    unsigned int a;

    for(a=0; a<inspect.size(); a++){
        if (inspect[a]==false)
            break;
    }
    if (a==inspect.size())    
        return 0;

    for(a=0; a<data1.size(); a++){
        if (inspect[a]==false && data1[a]==n){
            result.push_back(n+'A');
            inspect[a]=true;  
            return find(data2[a]);
        }
        else if (inspect[a]==false && data2[a]==n){
            result.push_back(n+'A');
            inspect[a]=true;
            return find(data1[a]);
        }
    }
    return 0;	
}

int main(){
	int node, side;
	char start, x, y, h;
	vector<int> count, other;
	cin >> node >> side >> start;
    data1.assign(side, -1);
    data2.assign(side, -1);
    count.assign(node, 0);
	for(int i=0; i<side; i++){
		cin >> x >> y;
		data1[i] = x - 'A';
		data2[i] = y - 'A';
		count[x-'A']++;
		if(count[x-'A']>2)
			other.push_back(x-'A');
        count[y-'A']++;
		if(count[y-'A']>2)
			other.push_back(y-'A'); 
	}
	for(int i=0; i<side; i++){
		if( data1[i]==other[0] && data2[i]==other[1]){
			//data1[i] = -1;
			//data2[i] = -1;
			data1.erase(data1.begin()+i);
			data2.erase(data2.begin()+i);
			side--;
		}else if( data1[i]==other[1] && data2[i]==other[0]){
			//data1[i] = -1;
			//data2[i] = -1;
			data1.erase(data1.begin()+i);
			data2.erase(data2.begin()+i);
			side--;
		}
	}
	for(int i=0; i<side; i++){
		if( data1[i]==other[0] && data2[i]==other[2]){
			//data1[i] = -1;
			//data2[i] = -1;
			data1.erase(data1.begin()+i);
			data2.erase(data2.begin()+i);
			side--;
		}else if( data1[i]==other[2] && data2[i]==other[0]){
			//data1[i] = -1;
			//data2[i] = -1;
			data1.erase(data1.begin()+i);
			data2.erase(data2.begin()+i);
			side--;
		}
	}
	for(int i=0; i<side; i++){
		if( data1[i]==other[0] && data2[i]==other[3]){
			//data1[i] = -1;
			//data2[i] = -1;
			data1.erase(data1.begin()+i);
			data2.erase(data2.begin()+i);
			side--;
		}else if( data1[i]==other[3] && data2[i]==other[0]){
			//data1[i] = -1;
			//data2[i] = -1;
			data1.erase(data1.begin()+i);
			data2.erase(data2.begin()+i);
			side--;
		}
	}
	
	inspect.assign(node, false);
	result.push_back(start);
    for(int i=0; i<node; i++){
        if (start-'A'==data1[i]){
            inspect[i]=true;
            find(data2[i]);
            break;
        }
        else if (start-'A'==data2[i]){
            inspect[i]=true;
            find(data1[i]);
            break;
        }
    }
	result.push_back(start);
    for(int i=0; i<result.size(); i++){
    	cout << result[i];
	}
	cout << endl;
	for(int i=result.size()-1; i>=0; i--){
		cout << result[i];
	}
	
	/*
	cout << other.size() << endl;
	for(int i=0; i<other.size(); i++){
		cout << other[i] << "   "; 
	}
	cout << endl;
	cout << "------" << endl; 
	for(int i=0; i<data1.size(); i++){
		cout << data1[i] << "   " << data2[i] << endl;
	}
	cout<< "¤À¹j½u" << endl;
	for(int i=0; i<node; i++){
		cout << count[i] << endl; 
	} */
	return 0;
}
