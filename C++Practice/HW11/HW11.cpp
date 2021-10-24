#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

struct record { 
	int id;
	unsigned char name[16];
	int weight;
	int height;
	float bmi;
};

int main() {

	ifstream inFile("records.csv", ios::in);
	stringstream sn, sm;
	if (!inFile) {
		cout << "File could not be opened!" << endl;
		system("Pause");
		exit(1);
	}
	vector<string> data,change;

	vector<record> datas, datas2; //宣告陣列

	string input,output;
	record in;
	while (inFile >> input) { //開檔
		sn.str("");
		sn.clear();
		sn << input;
		int point = 1;
		while (getline(sn, output, ',')) {
			sm.str("");
			sm.clear();
			sm << output;

			if (point == 1) {
				sm >> in.id; //存資料
			}
			else if (point == 2) {
				sm >> in.name;
			}
			else if (point == 3) {
				sm >> in.weight;
			}
			else if (point == 4) {
				sm >> in.height;
			}
			point++;
		}
		in.bmi = ((double)in.weight)/(((double)in.height/100)* ((double)in.height / 100)); //算bmi
		//in.bmi = 0.0;
		datas.push_back(in); //存資料到vector
	}
	inFile.close(); //關檔
	
	ofstream outFile("records.dat", ios::out | ios::binary); //存檔
	if (!outFile) {
		cout << "File could not be opened!" << endl;
		system("Pause");
		exit(1);
	}
	for (int i = 0; i < datas.size(); i++) {
		outFile.write((char*)& datas[i], sizeof(record));
	}
	outFile.close();

	ifstream inFile2("records.dat", ios::in | ios::binary); //再開檔
	if (!inFile2) {
		cout << "File could not be opened!" << endl;
		system("Pause");
		exit(1);
	}
	while (!inFile2.eof()) {
		inFile2.read((char*)& in, sizeof(record));
		datas2.push_back(in);
	}
	inFile2.close();


	for (int i = 0; i < datas2.size()-1; i++) {  //判斷bmi
		cout << datas2[i].id << ", " << datas2[i].name << ", " << datas2[i].weight << "," << datas2[i].height << "  " ;
		if (datas2[i].bmi < 18.5) {
			cout << " Underweight";
		}
		else if (datas2[i].bmi < 24) {
			cout << "Normal";
		}
		else if (datas2[i].bmi < 27) {
			cout << "Overweight";
		}
		else if (datas2[i].bmi < 30) {
			cout << "Moderately obese";
		}
		else if (datas2[i].bmi < 35) {
			cout << "severely obese";
		}
		else {
			cout << "Very severely obese";
		}
		cout << endl;
	}
	cout << endl << endl << endl;  //獨立顯示
	for (int i = 0; i < datas2.size() - 1; i++) {
		if (datas2[i].bmi < 18.5) {
			cout << datas2[i].id << ", " << datas2[i].name << ", " << datas2[i].weight << "," << datas2[i].height << " is underweight" << endl;
		}
	}
	return 0;
}
