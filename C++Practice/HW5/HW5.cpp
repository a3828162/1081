#include <iostream>
using namespace std;

void  Recursive( int numcpy);

int main(){ //這是個把10進位轉成16進位的程式

	int number, sizes=0;

	char result[100];  //用一個字元陣列
    for( int i=0;; i++){
        cin >> number; //輸入一個數字
        if(number>32767 || number<0){ //輸入數字的條件
            cout << "Please input again:"; //重新輸入
        }else
            break;
    }
	for( int i=number; i>0; i/=16)  //轉成16進位的位數
        sizes++;
    int numcpy = number;


    for( int i=sizes-1; i>=0; i--,number/=16){
        if(number%16>=10)
            result[i] = number%16+55;  //大於10轉成字母
        else
            result[i] = number%16+48;
    }
    cout << "Iterative : ";
    for( int i=0; i<sizes; i++)
        cout << result[i];  //輸出
    cout << endl;

    cout << "Recursive : ";
    Recursive( numcpy);
    cout << endl;
    return 0;
}

void Recursive( int numcpy){

    if( numcpy>=16)
        Recursive( numcpy/16);
    if( numcpy%16>=10)
        cout << char(numcpy%16+55); //大於10轉成字母
    else
        cout << numcpy%16;
}
