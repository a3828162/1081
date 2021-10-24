#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
   int number; // integer read from user

   cout << "Enter an integar: "; // prompt
   cin >> number;// read integer from user

	if(number%2==1)
		cout <<number<<" is odd\n";
	else
		cout <<number<<" is even\n";

   system( "pause" );
} // end main
