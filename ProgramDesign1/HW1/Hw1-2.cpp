#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
   int number;
   int a,c[5]; // integer read from user

   cout << "Enter an integar: "; 
   cin >> number;

	for(a=4;a>=0;a--,number/=10)
		c[a] = number%10;
	
	for(a=0;a<5;a++){
		cout << c[a];
		if(a!=4)
		cout << "    ";
		
	}

	cout << endl;
   system( "pause" );
} // end main
