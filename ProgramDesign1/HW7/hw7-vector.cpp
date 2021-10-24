#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;
#include <string.h>
#include <stdlib.h>

const unsigned int numTestCases = 22;
const unsigned int arraySize = 200;

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, vector< int > &hugeInt1, vector< int > &hugeInt2,
                                vector< int > &hugeInt3, vector< int > &hugeInt4 );

// enable user to input a positive huge integer
void input( istream &inFile, vector< int > &hugeInt );

// outputs hugeInt[ hugeInt.size() - 1 .. 0 ]
void output( ostream &outFile, vector< int > &hugeInt );

// a recursive function that outputs hugeInt[ last .. 0 ]
void recursiveOutput( ostream &outFile, vector< int > &hugeInt, int last );

// returns true if and only if the specified huge integer is zero
bool isZero( vector< int > &hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( vector< int > &hugeInt1, vector< int > &hugeInt2 );

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] == hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveEqual( vector< int > &hugeInt1, vector< int > &hugeInt2, int last );

// return true if and only if hugeInt1 < hugeInt2
bool less( vector< int > &hugeInt1, vector< int > &hugeInt2 );

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] < hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveLess( vector< int > &hugeInt1, vector< int > &hugeInt2, int last );

// sum = addend + adder
void addition( vector< int > &addend, vector< int > &adder, vector< int > &sum );

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( vector< int > &minuend, vector< int > &subtrahend, vector< int > &difference );

// product = multiplicand * multiplier
void multiplication( vector< int > &multiplicand, vector< int > &multiplier, vector< int > &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( vector< int > &dividend, vector< int > &divisor, vector< int > &quotient, vector< int > &remainder );

// hugeInt /= 10
void divideByTen( vector< int > &hugeInt );

void reset( vector< int > &hugeInt );

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   vector< int > hugeInt1;
   vector< int > hugeInt2;
   vector< int > hugeInt3;
   vector< int > hugeInt4;

   for( int i = 0; i < numTestCases; i++ )
   {
      input( inFile, hugeInt1 );
      input( inFile, hugeInt2 );
      perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      reset( hugeInt1 );
      reset( hugeInt2 );
   }

   inFile.close();
   outFile.close();

   system( "pause" );
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, vector< int > &hugeInt1, vector< int > &hugeInt2,
                                vector< int > &hugeInt3, vector< int > &hugeInt4 )
{
   output( outFile, hugeInt1 );
   output( outFile, hugeInt2 );

   addition( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
   output( outFile, hugeInt3 );

   if( less( hugeInt1, hugeInt2 ) )
   {
      outFile << '-';
      subtraction( hugeInt2, hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
      output( outFile, hugeInt3 );
   }
   else
   {
      subtraction( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
      output( outFile, hugeInt3 );
   }

   multiplication( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
   output( outFile, hugeInt3 );

   if( isZero( hugeInt2 ) )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      // hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
      division( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      output( outFile, hugeInt3 );
      output( outFile, hugeInt4 );
   }

   outFile << endl;
}

// enable user to input a positive huge integer
void input( istream &inFile, vector< int > &hugeInt )
{
   char numericString[ arraySize ];

   inFile >> numericString;

   hugeInt.resize( strlen( numericString ) );
   for( unsigned int i = 0; i < hugeInt.size(); i++ )
      hugeInt[ hugeInt.size() - i - 1 ] = numericString[ i ] - '0';
}

// outputs hugeInt[ hugeInt.size() - 1 .. 0 ]
void output( ostream &outFile, vector< int > &hugeInt )
{
   recursiveOutput( outFile, hugeInt, hugeInt.size() - 1 );
   outFile << endl;
}

// a recursive function that outputs hugeInt[ last .. 0 ]
void recursiveOutput( ostream &outFile, vector< int > &hugeInt, int last )
{
	if(last>=0){
		outFile << hugeInt[last];
		return recursiveOutput( outFile, hugeInt, last-1);
	}
}

// returns true if and only if the specified huge integer is zero
bool isZero( vector< int > &hugeInt )
{
   for( unsigned int i = 0; i < hugeInt.size(); i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( vector< int > &hugeInt1, vector< int > &hugeInt2 )
{
   if( hugeInt1.size() != hugeInt2.size() )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, hugeInt1.size() - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] == hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveEqual( vector< int > &hugeInt1, vector< int > &hugeInt2, int last )
{
    if (last>=0){
        if (hugeInt1[last] != hugeInt2[last])
            return false;
    }
    else
        return true;

    return recursiveEqual(hugeInt1, hugeInt2, last-1);
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( vector< int > &hugeInt1, vector< int > &hugeInt2 )
{
   if( hugeInt1.size() < hugeInt2.size() )
      return true;
   if( hugeInt1.size() > hugeInt2.size() )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, hugeInt1.size() - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] < hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveLess( vector< int > &hugeInt1, vector< int > &hugeInt2, int last )
{
	if(hugeInt1[last]<hugeInt2[last])
		return true;
	else if(hugeInt1[last]>hugeInt2[last])
		return false;

	if(last>0){
        recursiveLess( hugeInt1, hugeInt2, last - 1);
	}else{
	    return false;
	}
}

// sum = addend + adder
void addition( vector< int > &addend, vector< int > &adder, vector< int > &sum )
{
   sum.resize( ( addend.size() >= adder.size() ) ? addend.size() + 1 : adder.size() + 1 );

   for( unsigned int i = 0; i < addend.size(); i++ )
      sum[ i ] = addend[ i ];

   for( unsigned int i = addend.size(); i < sum.size(); i++ )
      sum[ i ] = 0;

   for( unsigned int i = 0; i < adder.size(); i++ )
      sum[ i ] += adder[ i ];

   for( unsigned int i = 0; i < sum.size() - 1; i++ )
      if( sum[ i ] > 9 ) // determine whether to carry a 1
      {
         sum[ i ] -= 10; // reduce to 0-9
         sum[ i + 1 ]++;
      }

   if( sum[ sum.size() - 1 ] == 0 )
      sum.pop_back();
}

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( vector< int > &minuend, vector< int > &subtrahend, vector< int > &difference )
{
   difference.resize( ( minuend.size() >= subtrahend.size() ) ? minuend.size() + 1 : subtrahend.size() + 1 );


    for( int i = 0; i < minuend.size(); i++ )
    	difference[ i ] = minuend[ i ];


    for( int i = minuend.size(); i < difference.size(); i++ ){
    	difference[ i ] = 0;
    }


	for( int i = 0; i < subtrahend.size(); i++ )
    	difference[ i ] -= subtrahend[ i ];



    for( int i = 0; i < difference.size(); i++ ){
       if( difference[ i ] < 0 && i+1!=difference.size())
    	{
        	difference[ i ] += 10;
        	difference[ i + 1 ]--;
    	}

    }

	for(int i=difference.size(); difference[i-1]==0 && i-1>0;i--)
		difference.pop_back();

}

// product = multiplicand * multiplier
void multiplication( vector< int > &multiplicand, vector< int > &multiplier, vector< int > &product )
{
	product.resize(  multiplicand.size() + multiplier.size() );

    if(isZero( multiplicand )){
        product.resize(1);
        product[0] = 0;
        return;
    }
    if(isZero( multiplier )){
        product.resize(1);
        product[0] = 0;
        return;
    }

	for( int i=0; i<product.size(); i++)
		product[i] = 0;

	for( int i=0; i<multiplicand.size(); i++){
		for( int j=0; j<multiplier.size(); j++){
			product[i+j] += multiplicand[i]*multiplier[j];
		}
	}

	for( int i=0; i<product.size(); i++){
		int j;
		for( j=product[i]; j>9; j-=10){
			product[i+1]++;
		}
		product[i]=j;
	}

	for( int i=product.size(); product[i-1] == 0; i--)
		product.pop_back();
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( vector< int > &dividend, vector< int > &divisor, vector< int > &quotient, vector< int > &remainder )
{
    //delete [] quotient;
    //delete [] remainder;
    //quotient = new int[ 1 ]();
    //remainder = new int[ 1 ]();

   if( isZero( dividend ) )
   {
    	reset( quotient );
        reset( remainder );
        quotient.resize(1);
        remainder.resize(1);
        quotient[0] = 0;
        remainder[0] = 0;
        return;
   }else if(equal( dividend, divisor )){
        reset( quotient );
        reset( remainder );
        quotient.resize(1);
        quotient[0] = 1;
        remainder.resize(1);
        remainder[0] = 0;
        return;
   }else if(less( dividend, divisor )){
        quotient.resize(1);
        remainder.resize(dividend.size());
        //delete[] quotient;
        //delete[] remainder;
        quotient[0] = 0;
        for( int i=dividend.size()-1; i>=0; i--)
            remainder[i]=dividend[i];
        return;
   }else{
	    int n;
		n = dividend.size()-divisor.size();
        vector< int > buffer;
	    buffer.resize(divisor.size()+n) ;
	 	remainder.resize(dividend.size()) ;
	    //delete[] remainder;
	 	for(int i=0; i<remainder.size(); i++){
			remainder[i] = dividend[i];
		}

		for(int i=0; i<n; i++)
	        buffer[i] = 0;
		for(int i=divisor.size(); i>0; i--){
			buffer[n+i-1]=divisor[i-1];
		}
		quotient.resize(dividend.size()-divisor.size()) ;

		if(less( dividend, buffer )){
			divideByTen( buffer );
		}else{
			quotient.resize(quotient.size()+1);
		}
        quotient.assign(quotient.size(), 0);
        vector< int > temp;
        temp.resize(remainder.size());
		for( int k=quotient.size()-1; k>=0; k--){
			while(less( buffer, remainder ) || equal( buffer, remainder )){
		        subtraction( remainder, buffer, temp );
		        //delete[] remainder;
				remainder.resize(temp.size()) ;
	            for(int l=temp.size()-1; l>=0; l--)
	                remainder[l] = temp[l];
		        //if (remainderSize==0)
		            //reset(remainder, remainderSize);
				quotient[k]++;
		        if( isZero( remainder )){
		            return;
		        }
			}

			divideByTen( buffer );
		}
		return;
	}

}

// hugeInt /= 10
void divideByTen( vector< int > &hugeInt )
{
   if( hugeInt.size() == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( unsigned int i = 1; i < hugeInt.size(); i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];
      hugeInt[ hugeInt.size() - 1 ] = 0;
      hugeInt.pop_back();
   }
}

void reset( vector< int > &hugeInt )
{
   hugeInt.resize( 1 );
   hugeInt[ 0 ] = 0;
}

