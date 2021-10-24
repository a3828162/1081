#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;
#define MAXWORDLENGTH 255

struct dictionary {
    char word[MAXWORDLENGTH];
    unsigned int count;
};

bool change(dictionary a, dictionary b)
{
    return a.count>b.count;
}

int main()
{
    ofstream outFile("dict.dat", ios::binary | ios::app);
    outFile.close(); //���� 

    ifstream inFile("dict.dat", ios::binary | ios::in);
    ifstream test1("test2.txt", ios::in);
    if (!inFile) cout << "no dict.dat";
    else if (!test1) cout << "no test1.txt";

    dictionary in;
    in.count = 1;
    vector<dictionary> dic;
    int a, b, c;

    while(test1 >> in.word)        //Ū��
        dic.push_back(in);
    test1.close();

    for(a=0; a<dic.size(); a++){
        for(b=0; b<strlen(dic[a].word) ;b++){
            if (dic[a].word[b]>='A' && dic[a].word[b]<='Z')   //�N�j�g��p�g
                dic[a].word[b] += 32;

            if (isdigit(dic[a].word[b]) || !(isalpha(dic[a].word[b]))){   //�⤣�O�r�����R�� 
                if(b == strlen(dic[a].word)-1)
                    dic[a].word[b] = '\0';
                else{
                    for(c=b; c<strlen(dic[a].word); c++)
                        dic[a].word[c] = dic[a].word[c+1];
                    dic[a].word[c-1] = '\0';
                }
                b--;
            }
        }
    }

    dictionary in2;
    while(inFile.read((char*)(&in2), sizeof(dictionary))) //Ū�즳���� 
        dic.push_back(in2);

   inFile.close(); //���� 
   ofstream outFile2("dict.dat", ios::binary | ios::out);

    for(a=0; a<dic.size()-1; a++){
        for(b=a+1; b<dic.size(); b++){
            if (!strcmp(dic[a].word, dic[b].word)){   //�N���Ʀr��R��
                dic[a].count += dic[b].count;
                dic.erase(dic.begin()+b);
            }
        }
    }

    sort(dic.begin(), dic.end(), change); //�Ƨ� 

    for(a=0; a<dic.size(); a++){ //�g�� 
        outFile2.write(reinterpret_cast<const char*>(&dic[a]), sizeof(dictionary));
        cout << dic[a].word << " " << dic[a].count << endl;
    }
    outFile2.close();

    return 0;
}
