#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
using namespace std;

int main() {

	ifstream inFile("records.csv", ios::in); //讀檔
	stringstream sn; 
	if (!inFile) {
		cout << "File could not be opened" << endl;
		system("Pause");
		exit(1);
	}
	vector<string> data, change, name;
	vector<double> height, weight, average;
	int poin = 0;
	while (!inFile.eof()) {
		string num;
		getline(inFile, num); //輸入資料
		data.push_back(num);
		poin++;
	}

	for (int i = 0; i < poin; i++) {
		sn << data[i];
		string value;
		while (getline(sn, value, ',')) //分開存資料
			change.push_back(value); 
		sn.str("");
		sn.clear();
	}
	double averageheight = 0, averageweight = 0; //平均
	for (int i = 1; i <= change.size(); i++) { 
		int a = 0;
		string n;
		if (i % 4 == 3) {
			sn << change[i - 1]; //放體重
			sn >> a;
			weight.push_back(a);
			averageweight += a;
		}
		else if (i % 4 == 0) {
			sn << change[i - 1]; //放身高
			sn >> a;
			height.push_back(a);
			averageheight += a;
		}
		else if (i % 2 == 0) {
			sn << change[i - 1]; //放名字
			getline(sn, n);
			name.push_back(n);
		}
		sn.str("");
		sn.clear();
	}

	averageheight /= height.size(); //平均身高
	averageweight /= weight.size(); //平均體重
	cout << "The average of weight is " << averageweight << endl;
	cout << "The average of height is " << averageheight << endl << endl << endl;
	int maxheight = 0; 
	for (int time = 0; time < data.size() - 1; time++) { //找最高的
		maxheight = 0;
		int c;
		for (int i = 0; i < height.size(); i++) {
			if (maxheight < height[i]) {
				maxheight = height[i];
				c = i;
			}
		}
		cout << time + 1 << "," << name[c] << "," << weight[c] << "," << maxheight << endl; //排序
		height[c] = 0;
	}
	return 0;
}

