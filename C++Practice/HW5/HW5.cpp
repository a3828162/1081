#include <iostream>
using namespace std;

void  Recursive( int numcpy);

int main(){ //�o�O�ӧ�10�i���ন16�i�쪺�{��

	int number, sizes=0;

	char result[100];  //�Τ@�Ӧr���}�C
    for( int i=0;; i++){
        cin >> number; //��J�@�ӼƦr
        if(number>32767 || number<0){ //��J�Ʀr������
            cout << "Please input again:"; //���s��J
        }else
            break;
    }
	for( int i=number; i>0; i/=16)  //�ন16�i�쪺���
        sizes++;
    int numcpy = number;


    for( int i=sizes-1; i>=0; i--,number/=16){
        if(number%16>=10)
            result[i] = number%16+55;  //�j��10�ন�r��
        else
            result[i] = number%16+48;
    }
    cout << "Iterative : ";
    for( int i=0; i<sizes; i++)
        cout << result[i];  //��X
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
        cout << char(numcpy%16+55); //�j��10�ন�r��
    else
        cout << numcpy%16;
}
