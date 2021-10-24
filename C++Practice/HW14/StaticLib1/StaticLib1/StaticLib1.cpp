// StaticLib1.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "hello.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>
#include <iomanip>
#include <string.h>
#include <string>

bool change(dictionary a, dictionary b)
{
	return a.count > b.count;
}

// TODO: This is an example of a library function
void countnumber()
{
	ifstream text("IHaveADream.txt", ios::in);

	if (!text) {
		cerr << "File could not be opened!";
		exit(1);
	}
	int a = 0, b = 0, c = 0;
	dictionary in, in2;
	in.count = 1;
	vector <dictionary> dic, dic2;
	while (text >> in.word)        //讀檔
		dic.push_back(in);
	text.close();

	for (a = 0; a < dic.size(); a++) {
		for (b = 0; b < strlen(dic[a].word); b++) {
			if (dic[a].word[b] >= 'A' && dic[a].word[b] <= 'Z')   //將大寫轉小寫
				dic[a].word[b] += 32;

			/*if (isdigit(dic[a].word[b]) || !(isalpha(dic[a].word[b]))) {   //把不是字母的刪除 
				if (b == strlen(dic[a].word) - 1)
					dic[a].word[b] = '\0';
				else {
					for (c = b; c < strlen(dic[a].word); c++)
						dic[a].word[c] = dic[a].word[c + 1];
					dic[a].word[c - 1] = '\0';
				}
				b--;
			}*/
			if ((dic[a].word[b] >= '0' && dic[a].word[b] <= '9') || (!(dic[a].word[b] >= 'a' && dic[a].word[b] <= 'z'))) {   //把不是字母的刪除 
				if (b == strlen(dic[a].word) - 1)
					dic[a].word[b] = '\0';
				else {
					for (c = b; c < strlen(dic[a].word); c++)
						dic[a].word[c] = dic[a].word[c + 1];
					dic[a].word[c - 1] = '\0';
				}
				b--;
			}
		}
	}
	

	for (a = 0; a < dic.size() - 1; a++) {
		for (b = a + 1; b < dic.size(); b++) {
			if (!strcmp(dic[a].word, dic[b].word)) {   //將重複字串刪除
				dic[a].count += dic[b].count;
				dic.erase(dic.begin() + b);
				b--;
			}
		}
	}

	sort(dic.begin(), dic.end(), change); //排序 

	ifstream inFIle("prepositions.txt", ios::in);
	while (inFIle >> in2.word)        //讀檔
		dic2.push_back(in2);

	for (int i = 0; i < dic.size(); i++) {
		for (int j = 0; j < dic2.size(); j++) {
			if (strcmp(dic[i].word, dic2[j].word)==0)
				dic.erase(dic.begin() + i);//刪除特定字
		}
	}

	for (a = 0; a < dic.size(); a++) { //輸出
		cout << setw(7) << dic[a].count << " " << dic[a].word << endl;
	}
	return;
}
